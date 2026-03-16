// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/*
 * AuraGameplayTags
 *  本地的游戏标签单例
 */
struct FAuraGameplayTags
{
	
protected:

private:
	static FAuraGameplayTags GameplayTags;
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	// 初始化本地标签
	static void InitializeNativeGameplayTags();
	
	// 主要属性
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	// 次要属性
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	// 重要属性
	// FGameplayTag Attributes_Vital_Health;
	// FGameplayTag Attributes_Vital_Mana;
	
	FGameplayTag Damage;

	
private:
	// 初始化主要属性
	void InitPrimary();
	// 初始化次要属性
	void InitSecondary();
	void InitVital();

	void InitMeta();

	// 初始化输入Tag
	void InitInputTag();

public:
};