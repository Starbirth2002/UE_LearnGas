// 王乐用于学习Gas的项目，仅供参考
#include "Character/AuraCharacterBase.h" 

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// 设置和投掷物的交互
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
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

// 获取武器插槽坐标
FVector AAuraCharacterBase::GetCombatSocketLocation() const
{
	check(m_Weapon)
	return m_Weapon->GetSocketLocation(WeaponTipSocketName);
	
}

// 应用游戏效果到自己
void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(ASC && GameplayEffectClass)
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
}

// 初始化属性
void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(m_DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(m_DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(m_DefaultVitalAttributes, 1.f);
}

// 添加角色能力
void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	if ( !HasAuthority() ) { return; }

	AuraASC->AddCharacterAbilities(StartupAbilities);
}

WL_DEBUG_END
