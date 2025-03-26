// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class UE_LEARNGAS_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface

{
	GENERATED_BODY()
public:
	// 构造函数
	AAuraCharacterBase();
	
protected:
	// 武器组件
	UPROPERTY(EditAnywhere, Category = "Combat") TObjectPtr<USkeletalMeshComponent>			m_Weapon;

	// 能力组件
	UPROPERTY(EditAnywhere,category = "Combat") TObjectPtr<UAbilitySystemComponent>			m_AbilitySystemComponent;
	// 属性集
	UPROPERTY(EditAnywhere,category = "Combat") TObjectPtr<UAttributeSet>					m_AttributeSet;

public:
	// 获取 能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GEtAttributeSet() const { return m_AttributeSet; }
protected:
	// 开始运行
	virtual void BeginPlay() override;
	 
};
