// 王乐用于学习Gas的项目，仅供参考


#include "AbilitySystem/AuraAbilitySystemLib.h"

#include "AbilitySystemComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

WL_DEBUG_BEGIN

UOverlayWidgetController* UAuraAbilitySystemLib::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	do
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		if (!PC) { break; }
		
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
		if (!AuraHUD) { break; }

		AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GEtAttributeSet();
		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
		return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	while (false);

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLib::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	do
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		if (!PC) { break; }
		
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
		if (!AuraHUD) { break; }

		AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GEtAttributeSet();
		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
		return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}
	while (false);

	return nullptr;
}

void UAuraAbilitySystemLib::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	float Level,  UAbilitySystemComponent* ASC)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if ( !AuraGameMode || !AuraGameMode->CharacterClassInfo ) { return; }

	AActor* AvatarActor = ASC->GetAvatarActor();
	
	const UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	// 创建并应用3种GE
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

WL_DEBUG_END
