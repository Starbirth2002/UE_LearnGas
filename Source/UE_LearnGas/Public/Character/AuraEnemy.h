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

public:
	// 构造函数
	AAuraEnemy();

	// 高亮Actor
	virtual void HighlightActor() override;
	// 取消高亮Actor
	virtual void UnHighlightActor() override;
};
