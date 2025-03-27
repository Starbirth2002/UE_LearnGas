// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS(Blueprintable)
class UE_LEARNGAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere) TObjectPtr<USphereComponent> Sphere;
public:
	// 构造函数
	AAuraEffectActor();
protected:
	// 开始运行
	virtual void BeginPlay() override;

public:
	UFUNCTION()	// 当重叠时
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() // 结束重叠
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
