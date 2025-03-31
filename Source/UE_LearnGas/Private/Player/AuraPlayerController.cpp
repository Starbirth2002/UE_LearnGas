// 王乐用于学习Gas的项目，仅供参考

#include "Player/AuraPlayerController.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

class AAuraPlayerState;
WL_DEBUG_BEGIN

// 构造函数
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;			// 多人游戏可复制
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
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
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	// 绑定输入回调
	EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
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

// 鼠标射线检测
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if ( !CursorHit.bBlockingHit ) { return; }
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

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

	if ( LastActor == nullptr )
	{
		if ( ThisActor == nullptr )
		{
			// Case A: Do nothing
		}
		else
		{
			// Case B:
			ThisActor->HighlightActor();
		}
	}
	else	// LastActor is Valid
	{
		if ( ThisActor == nullptr )
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // Both actors are Valid
		{
			if ( LastActor != ThisActor )
			{
				// Cast D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E: Do nothing
			}
		}
	}
	
}
WL_DEBUG_END
