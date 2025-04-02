// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UStaticMeshComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove,
};


UCLASS(Blueprintable)
class UE_LEARNGAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") TSubclassOf<UGameplayEffect>	InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") EEffectApplicationPolicy		InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") TSubclassOf<UGameplayEffect>	DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") EEffectApplicationPolicy		DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") TSubclassOf<UGameplayEffect>	InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") EEffectApplicationPolicy		InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") EEffectRemovePolicy				InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") double							ActorLevel = 1.f;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
public:
	// 构造函数
	AAuraEffectActor();
protected:
	// 开始运行
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)	// 应用效果到目标
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)	// 开始重叠时
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)	// 当结束重叠时
	void OnEndOverlap(AActor* TargetActor);
};
