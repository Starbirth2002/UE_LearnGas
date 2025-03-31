// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;


// 界面控制器参数
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
public:
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS,
		UAbilitySystemComponent* ASC, UAttributeSet* AS)
		:PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

};

/**
 * 界面控制器
 */
UCLASS()
class UE_LEARNGAS_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<APlayerController>			PlayerController;

	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<APlayerState>				PlayerState;

	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<UAbilitySystemComponent>		AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, category = "WIdgetController")
	TObjectPtr<UAttributeSet>				AttributeSet;

public:
	// 构造函数
	UAuraWidgetController();

	// 通知关联控件初始化
	virtual void BroadcastInitialValues() {}
	// 绑定回调到依赖项
	virtual void BindCallbacksToDependencies() {}
	
public:
	UFUNCTION(BlueprintCallable) // 设置界面控制器参数
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	
};
