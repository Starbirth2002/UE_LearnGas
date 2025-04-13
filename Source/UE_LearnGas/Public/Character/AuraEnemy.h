// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class UE_LEARNGAS_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults") int32 Level = 1;
	
public:
	// 构造函数
	AAuraEnemy();

protected:
	// 开始运行
	virtual void BeginPlay() override;

	// 父类继承
private:
	// 初始化能力信息
	virtual void InitAbilityActorInfo() override;
	
	//~ Begin Enemy Interface
public:
	// 高亮Actor
	virtual void HighlightActor() override;
	// 取消高亮Actor
	virtual void UnHighlightActor() override;

	//~ End Enemy Interface

	//~ Begin Combat Interface
public:
	// 获取等级
	virtual int32 GetPlayerLevel() override { return Level; }
	//~ End Combat Interface

	


};
