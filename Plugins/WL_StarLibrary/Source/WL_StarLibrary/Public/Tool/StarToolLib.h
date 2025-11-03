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
	static T* CreateAndSetup2Root(FName SubobjectName, AActor* Owner);
};

template <typename T>
T* UStarToolLib::CreateAndSetup2Root(FName SubobjectName, AActor* Owner)
{
	T* pComponent = Owner->CreateDefaultSubobject<T>(SubobjectName);
	pComponent->SetupAttachment(Owner->GetRootComponent());

	return pComponent;
}
