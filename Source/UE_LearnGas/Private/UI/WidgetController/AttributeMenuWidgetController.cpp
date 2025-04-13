// 王乐用于学习Gas的项目，仅供参考

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 绑定回调到依赖项
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for ( auto & Pair : AS->TagsToAttributes )
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{ BroadcastAttributeInfo(Pair.Key, Pair.Value()); });
	}
}

// 初始化
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair: AS->TagsToAttributes )
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
	// 测试通知
	// FAuraAttributeInfo Info;
	// AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength, Info);
	// Info.AttributeValue = AS->GetStrength();
	//
	// AttributeInfoDelegate.Broadcast(Info);
}

// 通知属性信息
void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info;
	AttributeInfo->FindAttributeInfoForTag(AttributeTag, Info);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	AttributeInfoDelegate.Broadcast(Info);
}


WL_DEBUG_END
