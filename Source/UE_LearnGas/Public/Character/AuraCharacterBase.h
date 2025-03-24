// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class UE_LEARNGAS_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent>			m_Weapon;
	
public:
	// 构造函数
	AAuraCharacterBase();

protected:
	// 开始运行
	virtual void BeginPlay() override;

	 
};
