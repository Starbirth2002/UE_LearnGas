// 王乐用于学习Gas的项目，仅供参考


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 初始化
void UOverlayWidgetController::BroadcastInitialValues()
{
	auto AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAS->GetMana());
	OnMaxManaChanged.Broadcast(AuraAS->GetMaxMana());
}

// 绑定回调到依赖项
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	auto AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);

	// 使用Lambda表达式进行替换
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	ASC_BindChangeDelegate(Health)
	ASC_BindChangeDelegate(MaxHealth)
	ASC_BindChangeDelegate(Mana)
	ASC_BindChangeDelegate(MaxMana)

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for ( const auto& Tag : AssetTags )
			{
				// GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString()));
				// "Message.HealthPotion".MatchesTag("Message") will return True,
				// "Message".MatchesTag("Message.HealthPotion") will return False
				auto MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if ( !Tag.MatchesTag(MessageTag) ) { continue; }
				
				auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		});
}

WL_DEBUG_END
