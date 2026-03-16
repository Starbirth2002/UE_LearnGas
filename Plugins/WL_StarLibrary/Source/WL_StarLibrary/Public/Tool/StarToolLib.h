// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StarToolLib.generated.h"

class USceneComponent;
/**
 * 王乐的工具库
 */
UCLASS()
class WL_STARLIBRARY_API UStarToolLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// 创建并添加组件
	template<typename T>
	static T* Construct_CreateAndSetupComp(FName SubobjectName, USceneComponent* pParent);
};


template <typename T>
T* UStarToolLib::Construct_CreateAndSetupComp(FName SubobjectName, USceneComponent* pParent)
{
	if ( pParent && pParent->GetOwner() )
	{
		T* pComponent = pParent->GetOwner()->CreateDefaultSubobject<T>(SubobjectName);
		pComponent->SetupAttachment(pParent);

		return pComponent;
	}

	return nullptr;
}
