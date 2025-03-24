// 王乐用于学习Gas的项目，仅供参考

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UE_LearnGas/Kernel/WlHead.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;			// 多人游戏可复制
}

// 开始运行
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

WL_DEBUG_END