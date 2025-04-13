// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class UE_LEARNGAS_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	// 构造函数
	AAuraCharacter();

protected:
	// 开始运行
	virtual void BeginPlay() override;

	// 父类继承
//~ Begin APawn Interface.
public:
	// 在被控制器控制时调用
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
//~ End APawn Interface.

private:
	// 初始化能力信息
	virtual void InitAbilityActorInfo() override;

	//~ Begin Combat Interface
public:
	// 获取等级
	virtual int32 GetPlayerLevel() override;
	//~ End Combat Interface
};
