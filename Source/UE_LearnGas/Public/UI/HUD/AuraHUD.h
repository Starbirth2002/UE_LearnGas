// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY() TObjectPtr<UAuraUserWidget>								OverlayWidget;
	
	UPROPERTY() TObjectPtr<UOverlayWidgetController>					OverlayWidgetController;
	UPROPERTY() TObjectPtr<UAttributeMenuWidgetController>				AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere) TSubclassOf<UAuraUserWidget>				OverlayWidgetClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UOverlayWidgetController>		OverlayWidgetControllerClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UAttributeMenuWidgetController>	AttributeMenuWidgetControllerClass;
	
public:
	// 构造函数
	AAuraHUD();

public:
	
	// 获取主界面控制器
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	// 获取属性菜单界面控制器
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	// 初始化主界面
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
