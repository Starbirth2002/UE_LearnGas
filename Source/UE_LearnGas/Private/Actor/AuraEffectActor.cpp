// 王乐用于学习Gas的项目，仅供参考

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/StaticMeshComponent.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

// 开始运行
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

// 应用效果到目标
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if ( auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) )
	{
		check(GameplayEffectClass)
		auto EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}


WL_DEBUG_END
