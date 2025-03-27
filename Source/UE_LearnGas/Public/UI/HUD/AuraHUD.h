// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

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

public:
	UPROPERTY() TObjectPtr<UAuraUserWidget>							OverlayWidget;
	
private:
	UPROPERTY() TObjectPtr<UOverlayWidgetController>				OverlayWidgetController;
	
	UPROPERTY(EditAnywhere) TSubclassOf<UAuraUserWidget>			OverlayWidgetClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UOverlayWidgetController>	OverlayWidgetControllerClass;
	
public:
	// 构造函数
	AAuraHUD();

public:
	// 获取主界面控制器
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	// 初始化主界面
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
