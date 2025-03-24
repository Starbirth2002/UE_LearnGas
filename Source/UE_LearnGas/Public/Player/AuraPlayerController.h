// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
struct FInputActionValue;
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

	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	// 开始运行
	virtual void BeginPlay() override;
	// 设置自定义输入绑定
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputMappingContext>	m_AuraContext;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction>			m_MoveAction;

	// 移动
	void Move(const FInputActionValue& InputActionValue);

	// 鼠标射线检测
	void CursorTrace();

	IEnemyInterface* LastActor = nullptr;	// 上一次指向的Actor
	IEnemyInterface* ThisActor = nullptr; // 这一次指向的Actor
};


