// 王乐用于学习Gas的项目，仅供参考

#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"
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


	// This is Required to use Target Data! 问题出在P115, 使用技能后，服务器和客户端都丢失了对方，执行后解决该问题，
	// 但是我不加这句话也没有遇到这个问题 我的问题是，客户端似乎没有收到服务器传来的数据
	UAbilitySystemGlobals::Get().InitGlobalData();
}

WL_DEBUG_END
