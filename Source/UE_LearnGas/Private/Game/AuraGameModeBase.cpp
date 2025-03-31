// 王乐用于学习Gas的项目，仅供参考


#include "Game/AuraGameModeBase.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	auto p = HUDClass;

	// 打印调用来源
	UE_LOG(LogTemp, Warning, TEXT("GameMode BeginPlay called on: %s"), *GetName());
}

WL_DEBUG_END