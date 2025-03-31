// 王乐用于学习Gas的项目，仅供参考


#include "UI/WidgetController/OverlayWidgetController.h"
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
	
	ASC_BindChangeDelegate(Health)
	ASC_BindChangeDelegate(MaxHealth)
	ASC_BindChangeDelegate(Mana)
	ASC_BindChangeDelegate(MaxMana)
}

WL_DEBUG_END
