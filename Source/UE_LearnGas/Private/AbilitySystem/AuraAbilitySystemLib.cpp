// 王乐用于学习Gas的项目，仅供参考


#include "AbilitySystem/AuraAbilitySystemLib.h"
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

WL_DEBUG_END
