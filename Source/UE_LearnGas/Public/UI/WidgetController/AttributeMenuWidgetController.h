// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
class UAttributeInfo;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignarue, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(Blueprintable)
class UE_LEARNGAS_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UAttributeInfo> AttributeInfo;
public:
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attribute")
	FAttributeInfoSignarue AttributeInfoDelegate;
public:
	// 绑定回调到依赖项
	virtual void BindCallbacksToDependencies() override;
	
	// 初始化
	virtual void BroadcastInitialValues() override;

private:
	// 通知属性信息
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
