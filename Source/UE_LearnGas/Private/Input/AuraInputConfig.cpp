// 王乐用于学习Gas的项目，仅供参考


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(
	const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for ( const FAuraInputAction& Action : AbilityInputActions )
	{
		if ( Action.InputAction && Action.InputTag.MatchesTag(InputTag) )
		{
			return Action.InputAction;
		}
	}

	if ( bLogNotFound )	
	{
		UE_LOG(LogTemp, Error, TEXT("没有通过标签[%s]找到InputAction，在表[%s]中"),
			*InputTag.ToString(), *GetNameSafe(this))
	}
	return nullptr;
}
