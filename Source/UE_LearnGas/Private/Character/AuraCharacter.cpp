// 王乐用于学习Gas的项目，仅供参考

#include "UE_LearnGas/Public/Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "UI/HUD/AuraHUD.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraCharacter::AAuraCharacter()
{
	auto Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->RotationRate = FRotator(0.f, 400.f, 0.f);
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// 开始运行
void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// 在被控制器控制时调用
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 初始化
	InitAbilityActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 在客户端上初始化
	InitAbilityActorInfo();
}

// 初始化能力信息
void AAuraCharacter::InitAbilityActorInfo()
{
	// 初始化客户端的AS和ASC
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	m_AttributeSet = AuraPlayerState->GEtAttributeSet();
	m_AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	// 设置拥有者和实际作用对象
	m_AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(m_AbilitySystemComponent)->AbilityActorInfoSet();
	// 只有客户端玩家自己控制的角色需要初始化HUD
	if ( AAuraPlayerController* AuraPlayerController = GetController<AAuraPlayerController>() )
	{
		if ( AAuraHUD* AuraHUD = AuraPlayerController->GetHUD<AAuraHUD>() )
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, m_AbilitySystemComponent, m_AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}

// 获取等级
int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

WL_DEBUG_END
