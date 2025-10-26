// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;
class USoundBase;

// 投掷物对象
UCLASS()
class UE_LEARNGAS_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TObjectPtr<UProjectileMovementComponent>	ProjectileMovement;	// 投掷物运动组件

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))		FGameplayEffectSpecHandle DamageEffectSpecHandle;	// 伤害效果句柄
private:
	UPROPERTY(EditDefaultsOnly) double									LifeSpan = 15.0;	// 寿命
	
	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent>				Sphere;				// 碰撞体
	UPROPERTY(EditAnywhere) TObjectPtr<UNiagaraSystem>					ImpactEffect;		// 特效
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase>						ImpactSound;		// 声音
	
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase>						LoopingSound;		// 循环持续的声音

	
	UPROPERTY(VisibleAnywhere) TObjectPtr<UAudioComponent>				AC_LoopingSound;	// 控制 LoopingSound的播放
	bool bHit = false;	// 客户端标记已命中
public:
	// 构造函数
	AAuraProjectile();

//~Begin --- Actor -----
protected:
	// 开始运行
	virtual void BeginPlay() override;
	// 已销毁 被销毁时，服务器和客户端都会调用
	virtual void Destroyed() override;

	UFUNCTION()	// 开始重叠
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

//~End --- Actor -----
};
