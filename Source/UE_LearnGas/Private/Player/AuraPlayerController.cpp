// 王乐用于学习Gas的项目，仅供参考

#include "Player/AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

class AAuraPlayerState;
WL_DEBUG_BEGIN

// 构造函数
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;			// 多人游戏可复制

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// 进行一次命中
	CursorTrace();
	// 自动移动
	AutoRun();
}

// 开始运行
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(m_AuraContext);
	
	// 向增强输入系统添加默认映射
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	SAFE_FUN(Subsystem, AddMappingContext(m_AuraContext, 0));

	// 显示 默认鼠标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// 输入模式设置 1、不会将鼠标限制在窗口内， 2、截图时不显示鼠标
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}


// 设置自定义输入绑定
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputC = CastChecked<UAuraInputComponent>(InputComponent);
	// 绑定移动输入回调
	AuraInputC->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputC->BindAction(m_ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputC->BindAction(m_ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
	
	// 绑定其他操作
	AuraInputC->BindAbilityActions(m_InputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

	// 默认输入方式
	{
		// UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
		// // 绑定输入回调
		// EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if ( !m_AuraASC )
	{
		m_AuraASC = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return m_AuraASC;
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if ( InputTag.MatchesTag(FAuraGameplayTags::Get().InputTag_LMB) )
	{
		bTargeting = ThisActor != nullptr;
		bAutoRunning = false;
	}
	
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("%s"), *InputTag.ToString()));
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if ( !GetASC() ) { return; }

	if ( !InputTag.MatchesTag(FAuraGameplayTags::Get().InputTag_LMB) )
	{
		GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	GetASC()->AbilityInputTagReleased(InputTag);
	
	if ( !bTargeting && !bShiftKeyDown )
	{
		APawn* ControllerPawn = GetPawn();
		if ( FollowTime <= ShortPressThreshold && ControllerPawn )
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this, ControllerPawn->GetActorLocation(), CachedDestination);
			if ( NavPath && !NavPath->PathPoints.IsEmpty() )
			{
				Spline->ClearSplinePoints();
				for ( const FVector& PointLoc : NavPath->PathPoints )
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					// Debug
					// DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}

				// 终点设置为目的地，防止Actor一直无法到达终点
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}

		FollowTime = 0.f;
		bTargeting = false;
	}
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Blue, FString::Printf(TEXT("%s"), *InputTag.ToString()));
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if ( !GetASC() ) { return; }
	
	if ( !InputTag.MatchesTag(FAuraGameplayTags::Get().InputTag_LMB) )
	{
		GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	
	if ( bTargeting || bShiftKeyDown )
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		// 更新目的地
		if ( CursorHit.bBlockingHit ) { CachedDestination = CursorHit.ImpactPoint; }

		// 按住移动时，一直更新Pawn的移动方向
		if ( APawn* ControllerPawn = GetPawn() )
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, FString::Printf(TEXT("%s"), *InputTag.ToString()));
}

// 移动
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 获取XY轴输入值
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotator = GetControlRotation();
	const FRotator YawRotator(0, Rotator.Yaw, 0);

	// 前进单位矢量 和 右移单位矢量
	const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	// 添加移动量
	if ( APawn* ControlledPawn = GetPawn<APawn>() )
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

// 自动寻路
void AAuraPlayerController::AutoRun()
{
	if ( !bAutoRunning ) { return; }
	if ( APawn* ControlledPawn = GetPawn() )
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if ( DistanceToDestination <= AutoRunAcceptanceRadius )
		{
			bAutoRunning = false;
		}
	}
}


// 鼠标射线检测
void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if ( !CursorHit.bBlockingHit ) { return; }

	// 高亮敌人Actor 
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	if ( LastActor != ThisActor )
	{
		if ( LastActor ) { LastActor->UnHighlightActor(); }
		if ( ThisActor ) { ThisActor->HighlightActor(); }
	}

	// 高亮敌人Actor 教育版
	{
		/*
		 * 鼠标射线检测的几种结果
		 *	A、LastActor is null && ThisActor is null
		 *		- Do nothing
		 *	B、LastActor is null && ThisActor is Valid
		 *		- Highlight ThisActor
		 *	C、LastActor is valid && ThisActor is null
		 *		- UnHighlight LastActor
		 *	D、2个Actor都有效，但是 LastActor != ThisActor
		 *		- UnHighlight LastActor, Highlight ThisActor
		 *	E、2个Actor都有效，但是 LastActor == ThisActor
		 *		- Do nothing
		 */

		// if ( LastActor == nullptr )
		// {
		// 	if ( ThisActor == nullptr )
		// 	{
		// 		// Case A: Do nothing
		// 	}
		// 	else
		// 	{
		// 		// Case B:
		// 		ThisActor->HighlightActor();
		// 	}
		// }
		// else	// LastActor is Valid
		// {
		// 	if ( ThisActor == nullptr )
		// 	{
		// 		// Case C
		// 		LastActor->UnHighlightActor();
		// 	}
		// 	else // Both actors are Valid
		// 	{
		// 		if ( LastActor != ThisActor )
		// 		{
		// 			// Cast D
		// 			LastActor->UnHighlightActor();
		// 			ThisActor->HighlightActor();
		// 		}
		// 		else
		// 		{
		// 			// Case E: Do nothing
		// 		}
		// 	}
		// }
	}
}
WL_DEBUG_END
