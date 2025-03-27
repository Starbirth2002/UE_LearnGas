// 王乐用于学习Gas的项目，仅供参考

#include "UI/WidgetController/AuraWidgetController.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
UAuraWidgetController::UAuraWidgetController()
{
}

// 设置界面控制器参数
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

WL_DEBUG_END