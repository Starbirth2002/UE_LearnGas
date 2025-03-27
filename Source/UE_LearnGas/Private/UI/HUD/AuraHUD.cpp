// 王乐用于学习Gas的项目，仅供参考

#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "UI/WidgetController/OverlayWidgetController.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraHUD::AAuraHUD()
{
}

// 获取主界面控制器
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if ( OverlayWidgetController == nullptr )
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return OverlayWidgetController;
}

// 初始化主界面
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("未设置OverlayWidgetClass， 请在AuraHUD中设置"))
	checkf(OverlayWidgetControllerClass, TEXT("未设置OverlayWidgetController， 请在AuraHUD中设置"))

	// 创建主界面 和 主界面控制器
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(GetOverlayWidgetController(FWidgetControllerParams(PC, PS, ASC, AS)));
	OverlayWidget->AddToViewport();
}

WL_DEBUG_END
