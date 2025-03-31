// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "OverlayWidgetController.generated.h"

#define ASC_BindChangeDelegate(name) AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->Get##name##Attribute()).AddUObject(this, &UOverlayWidgetController::name##Changed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
/**
 * 
 */
UCLASS(blueprintable)
class UE_LEARNGAS_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnHealthChangedSignature		OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnMaxHealthChangedSignature	OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes") FOnManaChangedSignature			OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnMaxManaChangedSignature		OnMaxManaChanged;
	
public:
	// 初始化
	virtual void BroadcastInitialValues() override;
	// 绑定回调到依赖项
	virtual void BindCallbacksToDependencies() override;

protected:
	void HealthChanged		(const FOnAttributeChangeData& Data) const { OnHealthChanged.Broadcast(Data.NewValue); }
	void MaxHealthChanged	(const FOnAttributeChangeData& Data) const { OnMaxHealthChanged.Broadcast(Data.NewValue); }
	void ManaChanged		(const FOnAttributeChangeData& Data) const { OnManaChanged.Broadcast(Data.NewValue); }
	void MaxManaChanged		(const FOnAttributeChangeData& Data) const { OnMaxManaChanged.Broadcast(Data.NewValue); }
};
