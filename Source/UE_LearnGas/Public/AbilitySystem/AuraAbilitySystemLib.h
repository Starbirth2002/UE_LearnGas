// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLib.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UAuraAbilitySystemLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|视图控制器", meta=(WorldContext="WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|视图控制器", meta=(WorldContext="WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|角色类默认",  meta=(WorldContext="WorldContextObject"))
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass,
		float Level, UAbilitySystemComponent* ASC);
};
