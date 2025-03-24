// 王乐用于学习Gas的项目，仅供参考

#include "UE_LearnGas/Public/Character/AuraEnemy.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

// 高亮Actor
void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	m_Weapon->SetRenderCustomDepth(true);
	m_Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

// 取消高亮Actor
void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	m_Weapon->SetRenderCustomDepth(false);
}

WL_DEBUG_END
