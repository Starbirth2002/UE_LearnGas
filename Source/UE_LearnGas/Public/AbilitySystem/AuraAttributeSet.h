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
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, DisplayName = "生命值", Category = "重要属性")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, DisplayName = "最大生命值", Category = "重要属性")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, DisplayName = "法力值", Category = "重要属性")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, DisplayName = "最大法力值", Category = "重要属性")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
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
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	
private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& OutProps) const;
};
