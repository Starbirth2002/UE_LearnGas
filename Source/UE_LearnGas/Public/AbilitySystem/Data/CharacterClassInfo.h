// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
// 角色类型
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "角色类默认值")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> Map_CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category = "普通类默认值")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "普通类默认值")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	// 获取角色类型的默认属性
	UFUNCTION(BlueprintPure)
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass) const;
};
