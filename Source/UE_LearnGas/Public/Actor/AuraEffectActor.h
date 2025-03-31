// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UStaticMeshComponent;
class USphereComponent;

UCLASS(Blueprintable)
class UE_LEARNGAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "应用效果") TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
public:
	// 构造函数
	AAuraEffectActor();
protected:
	// 开始运行
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)	// 应用效果到目标
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
