// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class UE_LEARNGAS_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface

{
	GENERATED_BODY()
	
protected:
	// 武器组件
	UPROPERTY(EditAnywhere, Category = "Combat") TObjectPtr<USkeletalMeshComponent>			m_Weapon;

	// 能力组件
	UPROPERTY(EditAnywhere, Category = "Combat") TObjectPtr<UAbilitySystemComponent>		m_AbilitySystemComponent;
	// 属性集
	UPROPERTY(EditAnywhere, Category = "Combat") TObjectPtr<UAttributeSet>					m_AttributeSet;

	UPROPERTY(EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect>			m_DefaultPrimaryAttributes;
	UPROPERTY(EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect>			m_DefaultSecondaryAttributes;
	UPROPERTY(EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect>			m_DefaultVitalAttributes;
public:
	// 构造函数
	AAuraCharacterBase();

public:
	// 获取 能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GEtAttributeSet() const { return m_AttributeSet; }
protected:
	// 开始运行
	virtual void BeginPlay() override;

	
private:
	// 初始化能力信息
	virtual void InitAbilityActorInfo() {}


protected:
	// 应用游戏效果到自己
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const;
	// 初始化属性
	void InitializeDefaultAttributes() const;
};
