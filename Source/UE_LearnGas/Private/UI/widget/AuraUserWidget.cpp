// 王乐用于学习Gas的项目，仅供参考


#include "UI/Widget/AuraUserWidget.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 设置界面控制器
void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

WL_DEBUG_END