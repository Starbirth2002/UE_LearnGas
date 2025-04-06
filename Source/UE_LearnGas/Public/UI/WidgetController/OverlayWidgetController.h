// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

#define  ASC_BindChangeDelegate(name) AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->Get##name##Attribute()).AddLambda([this](const FOnAttributeChangeData& Data) { On##name##Changed.Broadcast(Data.NewValue); });

USTRUCT(Blueprintable)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag					MessageTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText						MessageText = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<UAuraUserWidget>	MessageWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UTexture2D>		Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
// 使用 FOnAttributeChangedSignature 替换
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
/**
 * 
 */
UCLASS(blueprintable)
class UE_LEARNGAS_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnAttributeChangedSignature	OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnAttributeChangedSignature	OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes") FOnAttributeChangedSignature	OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") FOnAttributeChangedSignature	OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages") FMessageWidgetRowSignature		MessageWidgetRowDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wdiget Data") TObjectPtr<UDataTable>		MessageWidgetDataTable;
public:
	// 初始化
	virtual void BroadcastInitialValues() override;
	// 绑定回调到依赖项
	virtual void BindCallbacksToDependencies() override;

protected:
	// 使用Lambda表达式替换
	// void HealthChanged		(const FOnAttributeChangeData& Data) const { OnHealthChanged.Broadcast(Data.NewValue); }
	// void MaxHealthChanged	(const FOnAttributeChangeData& Data) const { OnMaxHealthChanged.Broadcast(Data.NewValue); }
	// void ManaChanged			(const FOnAttributeChangeData& Data) const { OnManaChanged.Broadcast(Data.NewValue); }
	// void MaxManaChanged		(const FOnAttributeChangeData& Data) const { OnMaxManaChanged.Broadcast(Data.NewValue); }

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
