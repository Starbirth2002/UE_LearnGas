// 王乐用于学习Gas的项目，仅供参考

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(Blueprintable)
struct UE_LEARNGAS_API FEffectProperties
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayEffectContextHandle		EffectContextHandle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAbilitySystemComponent* 		SourceASC = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AActor*							SourceAvatarActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AController*						SourceController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ACharacter*						SourceCharacter = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAbilitySystemComponent* 		TargetASC = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AActor*							TargetAvatarActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AController*						TargetController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ACharacter*						TargetCharacter = nullptr;
	FEffectProperties() {}

	void SetSource(UAbilitySystemComponent* ASC, AActor* AvatarActor, AController* Controller, ACharacter* Character);
	void SetTarget(UAbilitySystemComponent* ASC, AActor* AvatarActor, AController* Controller, ACharacter* Character);
};

/**
 * 
 */
UCLASS()
class UE_LEARNGAS_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/*
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, DisplayName = "力量", Category = "主要属性")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, DisplayName = "智力", Category = "主要属性")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, DisplayName = "抗性", Category = "主要属性")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, DisplayName = "活力", Category = "主要属性")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	/*
	 * Secondary Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, DisplayName = "护甲", Category = "次要属性")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, DisplayName = "护甲穿透", Category = "次要属性")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, DisplayName = "格挡率", Category = "次要属性")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, DisplayName = "暴击率", Category = "次要属性")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, DisplayName = "暴击伤害", Category = "次要属性")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalResistance, DisplayName = "暴击抗性", Category = "次要属性")
	FGameplayAttributeData CriticalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, DisplayName = "生命恢复", Category = "次要属性")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, DisplayName = "法力恢复", Category = "次要属性")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, DisplayName = "最大生命值", Category = "重要属性")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, DisplayName = "最大法力值", Category = "重要属性")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, DisplayName = "生命值", Category = "重要属性")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, DisplayName = "法力值", Category = "重要属性")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);



	
public :
		// 构造函数
		UAuraAttributeSet();
public:

	// 获取生命周期内复制的属性
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 当属性发生任何修改前
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// 在GameplayEffect执行完毕后立即调用
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Primary Attributes
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	// Secondary Attributes
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION() void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION() void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION() void OnRep_CriticalResistance(const FGameplayAttributeData& OldCriticalResistance) const;
	UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	// Vital Attributes
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;


private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& OutProps) const;
};

