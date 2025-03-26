// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAuraAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	// 构造函数
	UAuraWidgetController();
	
protected:
	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<APlayerController>			PlayerController;

	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<APlayerState>				PlayerState;

	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<UAbilitySystemComponent>		AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<UAuraAttributeSet>			AttributeSet;
};
