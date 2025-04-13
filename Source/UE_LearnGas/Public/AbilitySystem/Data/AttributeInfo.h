// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(Blueprintable)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	FGameplayTag	AttributeTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	FText			AttributeName = FText();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	FText			AttributeDescription = FText();
	UPROPERTY(BlueprintReadOnly)					float			AttributeValue = 0.0f;
};

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FAuraAttributeInfo> AttributeInformation;

public:
	UFUNCTION(BlueprintPure)	
	bool FindAttributeInfoForTag(const FGameplayTag& AttributeTag, FAuraAttributeInfo& OutAttributeInfo, bool bLogNotFound = false) const;	
};
