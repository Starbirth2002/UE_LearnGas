// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="角色类默认")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
