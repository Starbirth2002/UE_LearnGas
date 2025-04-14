// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct UE_LEARNGAS_API FAuraInputAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly) const UInputAction*	InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly) FGameplayTag		InputTag = FGameplayTag();

	bool IsValid() const { return InputAction && InputTag.IsValid(); }
};

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FAuraInputAction> AbilityInputActions;

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
