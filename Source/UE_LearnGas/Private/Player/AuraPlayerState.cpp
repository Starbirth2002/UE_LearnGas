// 王乐用于学习Gas的项目，仅供参考

#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraPlayerState::AAuraPlayerState()
{
	// 创建 属性集 和 能力系统组件
	m_AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	m_AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	m_AbilitySystemComponent->SetIsReplicated(true);
	// 设置网络复制模式
	m_AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// 设置网络更新频率
	SetNetUpdateFrequency( 100.f);
}

// 获取 能力系统组件
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return m_AbilitySystemComponent;
}

WL_DEBUG_END
