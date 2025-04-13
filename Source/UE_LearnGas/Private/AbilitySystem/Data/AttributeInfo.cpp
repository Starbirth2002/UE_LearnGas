// 王乐用于学习Gas的项目，仅供参考

#include "AbilitySystem/Data/AttributeInfo.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

bool UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
	FAuraAttributeInfo& OutAttributeInfo, bool bLogNotFound) const
{
	for ( const FAuraAttributeInfo& Info : AttributeInformation )
	{
		if ( Info.AttributeTag.MatchesTagExact(AttributeTag) )
		{
			OutAttributeInfo = Info;
			return true;
		}
	}

	if ( bLogNotFound )
	{
		UE_LOG(LogTemp, Error, TEXT("没有找到标签[%s]，在表[%s]中"),
			*AttributeTag.ToString(), *GetNameSafe(this))
	}
	return false;
}

WL_DEBUG_END