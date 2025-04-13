// 王乐用于学习Gas的项目，仅供参考

#include "AuraGameplayTags.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "GameplayTagsManager.h"

#define ANGT_Primary(Name, Description) Attributes_Primary_##Name = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary." #Name), FString(Description))
#define ANGT_Secondary(Name, Description) Attributes_Secondary_##Name = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary." #Name), FString(Description))


WL_DEBUG_BEGIN

FAuraGameplayTags FAuraGameplayTags::GameplayTags;


// 初始化本地标签
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.InitPrimary();
	GameplayTags.InitSecondary();
}

// 初始化主要属性
void FAuraGameplayTags::InitPrimary()
{
	ANGT_Primary(Strength,		"增加物理伤害(Increases physical damage)");
	ANGT_Primary(Intelligence,	"增加魔法伤害(Increases magical damage)");
	ANGT_Primary(Resilience,	"增加护甲和护甲穿透力(Increases armor and armor penetration)");
	ANGT_Primary(Vigor,			"增加生命值(Increases health)");
}

// 初始化次要属性
void FAuraGameplayTags::InitSecondary()
{
	ANGT_Secondary(Armor,				"减少伤害，提高格挡几率(Reduces damage taken, improves Block Chance)");
	ANGT_Secondary(ArmorPenetration,	"忽略敌方护甲百分比，增加暴击几率(Ignores percentage of enemy Armor, increases Critical Hit Chance)");
	ANGT_Secondary(BlockChance,			"将受到的伤害减半的几率(Chance to cut incoming damage in half)");
	ANGT_Secondary(CriticalHitChance,	"造成双倍伤害的暴击几率(Chance to double damage plus critical hit bonus)");
	ANGT_Secondary(CriticalHitDamage,	"造成暴击时增加的额外伤害(Bonus damage added when a Critical hit is scored)");
	ANGT_Secondary(CriticalResistance,	"降低攻击敌人的暴击几率(Reduces critical hit chance of attacking enemies)");
	ANGT_Secondary(HealthRegeneration,	"每秒再生的生命值(Amount of Health regenerated every 1 second)");
	ANGT_Secondary(ManaRegeneration,	"每秒再生的法力值(Amount of Mana regenerated every 1 second)");
	ANGT_Secondary(MaxHealth,			"最大生命值(Maximum amount of Health obtainable)");
	ANGT_Secondary(MaxMana,				"最大法力值(Maximum amount of Mana obtainable)");
}

void FAuraGameplayTags::InitVital()
{
	// Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),FString("玩家死前可以承受的伤害量(Amount of Damage a player can take before death)"));
	// Attributes_Vital_Mana	= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),	FString("用于施放法术的资源(A resource used to cast spells)"));
}



WL_DEBUG_END
