// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class UE_LEARNGAS_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TObjectPtr<UProjectileMovementComponent>	ProjectileMovement;
private:
	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent>				Sphere;
public:
	// 构造函数
	AAuraProjectile();

protected:
	// 开始运行
	virtual void BeginPlay() override;

	UFUNCTION()	// 开始重叠
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
