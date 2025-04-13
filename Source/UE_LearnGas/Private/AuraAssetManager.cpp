// 王乐用于学习Gas的项目，仅供参考

#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN
UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// 加载标签
	FAuraGameplayTags::InitializeNativeGameplayTags();
}

WL_DEBUG_END
