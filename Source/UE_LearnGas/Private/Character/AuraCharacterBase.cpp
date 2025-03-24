// 王乐用于学习Gas的项目，仅供参考
#include "Character/AuraCharacterBase.h"
#include "UE_LearnGas/Kernel/WlHead.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	m_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	m_Weapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponHandSocket")));
	m_Weapon->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// 开始运行
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

WL_DEBUG_END
