// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// 构造函数
	AAuraPlayerController();
protected:
	// 开始运行
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputMappingContext>	 AuraContext;
};
