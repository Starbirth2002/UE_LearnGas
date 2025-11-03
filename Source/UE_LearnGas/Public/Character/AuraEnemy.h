// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

UCLASS()
class UE_LEARNGAS_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults") int32 Level = 1;

	// 生命值
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UWidgetComponent>	HealthBar;
	UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature					OnHealthChanged;
	UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature					OnMaxHealthChanged;
public:
	// 构造函数
	AAuraEnemy();

//~ Begin --- Actor Interface -----
protected:
	// 开始运行
	virtual void BeginPlay() override;

	// 父类继承
private:
	// 初始化能力信息
	virtual void InitAbilityActorInfo() override;
	
//~ End ----- Actor Interface -----
	
//~ Begin --- EnemyInterface -----
public:
	// 高亮Actor
	virtual void HighlightActor() override;
	// 取消高亮Actor
	virtual void UnHighlightActor() override;

//~ End ----- EnemyInterface -----

//~ Begin --- CombatInterface -----
public:
	// 获取等级
	virtual int32 GetPlayerLevel() override { return Level; }
//~ End ----- CombatInterface -----

	


};
