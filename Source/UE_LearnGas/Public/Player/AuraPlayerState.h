// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	// 能力组件
	UPROPERTY(EditAnywhere,category = "Combat") TObjectPtr<UAbilitySystemComponent>			m_AbilitySystemComponent;
	// 属性集
	UPROPERTY(EditAnywhere,category = "Combat") TObjectPtr<UAttributeSet>					m_AttributeSet;

public:
	// 构造函数
	AAuraPlayerState();
	
public:
	// 获取 能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GEtAttributeSet() const { return m_AttributeSet; }
};
