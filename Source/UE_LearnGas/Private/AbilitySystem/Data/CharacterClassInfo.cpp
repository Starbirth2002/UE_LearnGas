// 王乐用于学习Gas的项目，仅供参考


#include "AbilitySystem/Data/CharacterClassInfo.h"

// 获取角色类型的默认属性
FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass) const
{
	return Map_CharacterClassInformation.FindChecked(CharacterClass);
	// FCharacterClassDefaultInfo* pFind = Map_CharacterClassInformation.Find(CharacterClass);
	// check(pFind);
	// return pFind ? *pFind : FCharacterClassDefaultInfo();
}
