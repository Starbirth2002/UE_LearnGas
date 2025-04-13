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
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if ( !IsValid(TargetASC) ) { return;	}

	check(GameplayEffectClass)
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
		*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if ( bIsInfinite && EEffectRemovePolicy::RemoveOnEndOverlap == InfiniteEffectRemovePolicy )
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

// 开始重叠时
void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if ( EEffectApplicationPolicy::ApplyOnOverlap == InstantEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if ( EEffectApplicationPolicy::ApplyOnOverlap == DurationEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if ( EEffectApplicationPolicy::ApplyOnOverlap == InfiniteEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

// 当结束重叠时
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{

	if ( EEffectApplicationPolicy::ApplyOnEndOverlap == InstantEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if ( EEffectApplicationPolicy::ApplyOnEndOverlap == DurationEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if ( EEffectApplicationPolicy::ApplyOnEndOverlap == InfiniteEffectApplicationPolicy )
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if ( EEffectRemovePolicy::RemoveOnEndOverlap == InfiniteEffectRemovePolicy )
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if ( !IsValid(TargetASC) ) { return;	}

		// 使用迭代器安全移除
		for (auto Iter = ActiveEffectHandles.CreateIterator(); Iter; ++Iter)
		{
			if ( TargetASC == Iter.Value() )
			{
				TargetASC->RemoveActiveGameplayEffect(Iter.Key(), 1);
				Iter.RemoveCurrent();
			}
		}
		// TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		// for ( const auto& HandlePair : ActiveEffectHandles )
		// {
		// 	if ( TargetASC == HandlePair.Value )
		// 	{
		// 		TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
		// 		HandlesToRemove.Add(HandlePair.Key);
		// 	}
		// }
		// for ( const auto& Handle : HandlesToRemove )
		// {
		// 	ActiveEffectHandles.Remove(Handle);
		// }
	}
}


WL_DEBUG_END
