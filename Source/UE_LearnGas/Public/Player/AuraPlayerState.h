// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class FLifetimeProperty;
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
	UPROPERTY(VisibleAnywhere) TObjectPtr<UAbilitySystemComponent>			m_AbilitySystemComponent;
	// 属性集
	UPROPERTY() TObjectPtr<UAttributeSet>							m_AttributeSet;

private:
	UPROPERTY(visibleAnywhere, ReplicatedUsing = OnRep_Level) int32 Level = 1;
	
public:
	// 构造函数
	AAuraPlayerState();

	// 父类继承
public:
	// 获取生命周期内复制的属性
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	// AbilitySystem Interface
public:
	// 获取 能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return m_AbilitySystemComponent; }

public:
	// 获取属性集
	UAttributeSet* GEtAttributeSet() const { return m_AttributeSet; }

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
	UFUNCTION() void OnRep_Level(int32 OldLevel);
};
