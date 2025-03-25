// 王乐用于学习Gas的项目，仅供参考
#include "Character/AuraCharacterBase.h" 
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 初始化Weapon组件
	m_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	m_Weapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponHandSocket")));
	m_Weapon->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// 获取 能力系统组件
UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return m_AbilitySystemComponent;
}

// 开始运行
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

WL_DEBUG_END