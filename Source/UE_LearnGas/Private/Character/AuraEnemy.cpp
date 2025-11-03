// 王乐用于学习Gas的项目，仅供参考

#include "UE_LearnGas/Public/Character/AuraEnemy.h"
#include "StarCore.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Tool/StarToolLib.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "UI/Widget/AuraUserWidget.h"

STAR_DEBUG_BEGIN

// 构造函数
AAuraEnemy::AAuraEnemy()
{
	// 设置角色可以在可视性碰撞通道中阻挡(被检测), 不包括武器
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	// 创建 属性集 和 能力系统组件
	m_AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	m_AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	m_AbilitySystemComponent->SetIsReplicated(true);
	// 设置网络复制模式
	m_AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar= UStarToolLib::CreateAndSetup2Root<UWidgetComponent>("HeathBar", this);
}

// 开始运行
void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 初始化能力信息
	InitAbilityActorInfo();

	if ( UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()) )
	{
		AuraUserWidget->SetWidgetController(this);
	}
	
	// 绑定回调 当属性变化后，通知属性发生变化
	if ( UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(m_AttributeSet) )
	{
		ASC_BIND_CHANGE_DELEGATE(Health, m_AbilitySystemComponent, AuraAS);
		ASC_BIND_CHANGE_DELEGATE(MaxHealth, m_AbilitySystemComponent, AuraAS);

		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
	
}

// 初始化能力信息
void AAuraEnemy::InitAbilityActorInfo()
{
	// 设置拥有者和实际作用对象
	m_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(m_AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

// 高亮Actor
void AAuraEnemy::HighlightActor()
{
	// 设置渲染自定义深度通道
	GetMesh()->SetRenderCustomDepth(true);
	m_Weapon->SetRenderCustomDepth(true);
	// 设置自定义深度模板值
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	m_Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

// 取消高亮Actor
void AAuraEnemy::UnHighlightActor()
{
	// 取消渲染自定义深度通道
	GetMesh()->SetRenderCustomDepth(false);
	m_Weapon->SetRenderCustomDepth(false);
}


STAR_DEBUG_END
