// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
struct FInputActionValue;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
		
private:
	UPROPERTY(EditAnywhere, Category = "Input")		TObjectPtr<UInputMappingContext>	m_AuraContext;
	UPROPERTY(EditAnywhere, Category = "Input")		TObjectPtr<UInputAction>			m_MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")		TObjectPtr<UInputAction>			m_ShiftAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")	TObjectPtr<UAuraInputConfig>		m_InputConfig;

	UPROPERTY() TObjectPtr<UAuraAbilitySystemComponent>			m_AuraASC;

	// 鼠标点击移动
	FVector			CachedDestination = FVector::ZeroVector;
	float			FollowTime = 0.0f;
	float			ShortPressThreshold = 0.5f;
	bool			bAutoRunning = false;
	bool			bTargeting = false;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	bool			bShiftKeyDown = false;

	UPROPERTY(VisibleAnywhere) TObjectPtr<USplineComponent> Spline;
	

	FHitResult		 CursorHit;				// 鼠标命中结果
	IEnemyInterface* LastActor = nullptr;	// 上一次指向的Actor
	IEnemyInterface* ThisActor = nullptr;	// 这一次指向的Actor
	
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
	UAuraAbilitySystemComponent* GetASC();
	//
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	// 移动
	void Move(const FInputActionValue& InputActionValue);
	
	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }
	// 自动寻路
	void AutoRun();
	
	// 鼠标射线检测
	void CursorTrace();
};


