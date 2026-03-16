// 王乐用于学习Gas的项目，仅供参考

#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "UE_LearnGas/UE_LearnGas.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

WL_DEBUG_BEGIN

void FEffectProperties::SetSource(UAbilitySystemComponent* ASC, AActor* AvatarActor, AController* Controller, ACharacter* Character)
{
	SourceASC = ASC;
	SourceAvatarActor = AvatarActor;
	SourceController = Controller;
	SourceCharacter = Character;
}

void FEffectProperties::SetTarget(UAbilitySystemComponent* ASC, AActor* AvatarActor, AController* Controller, ACharacter* Character)
{
	TargetASC = ASC;
	TargetAvatarActor = AvatarActor;
	TargetController = Controller;
	TargetCharacter = Character;
}

// 构造函数
UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	// 主要属性
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength,				GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence,			GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience,			GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor,					GetVigorAttribute);

	// 次要属性
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor,				GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, 	GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance,			GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance,	GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage,	GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalResistance,	GetCriticalResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration,	GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration,	GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth,			GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana,				GetMaxManaAttribute);
	// 测试添加 TagsToAttributes
	// DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);
	// FAttributeSignature StrengthDelegate;
	// StrengthDelegate.BindStatic(GetStrengthAttribute);
	// TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, StrengthDelegate);
	
}

// 获取生命周期内复制的属性
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	
	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	
}

// 当属性发生任何修改前
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if ( GetHealthAttribute() == Attribute )
	{
		// NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if ( GetMaxHealthAttribute() == Attribute )
	{
		NewValue = FMath::Max(0, NewValue);
	}

	if ( GetManaAttribute() == Attribute )
	{
		// NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
	if ( GetMaxManaAttribute() == Attribute )
	{
		NewValue = FMath::Max(0, NewValue);
	}
}

// 在GameplayEffect执行完毕后立即调用
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if ( Data.EvaluatedData.Attribute == GetHealthAttribute() )
	{
		// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("Health: %f"), GetHealth()));
		// SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		
		UE_LOG(LogTemp, Warning, TEXT("%s改变了生命值为 %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	if ( Data.EvaluatedData.Attribute == GetMaxHealthAttribute() )
	{
		SetMaxHealth(FMath::Max(0, GetMaxHealth()));
	}

	if ( Data.EvaluatedData.Attribute == GetManaAttribute() )
	{
		// SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	if ( Data.EvaluatedData.Attribute == GetMaxManaAttribute() )
	{
		SetMaxMana(FMath::Max(0, GetMaxMana()));
	}

	if ( Data.EvaluatedData.Attribute == GetIncomingDamageAttribute() )
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if ( LocalIncomingDamage > 0.f )
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
		}
		
	}
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalResistance(const FGameplayAttributeData& OldCriticalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalResistance, OldCriticalResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}


void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutProps) const
{
	// Source = Causer of the effect, Target = Target of the effect(owner of this AS)
	auto EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();
	UAbilitySystemComponent*  TargetASC = nullptr;
	AActor* SourceAvatarActor = nullptr;
	AActor* TargetAvatarActor = nullptr;
	AController* SourceController = nullptr;
	AController* TargetController = nullptr;
	ACharacter* SourceCharacter = nullptr;
	ACharacter*TargetCharacter = nullptr;
	
	if ( IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid() )
	{
		SourceAvatarActor = SourceASC->AbilityActorInfo->AvatarActor.Get();
		SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
		if ( SourceAvatarActor && !SourceController )
		{
			if ( const auto Pawn = Cast<APawn>(SourceAvatarActor) )
			{
				SourceController = Pawn->GetController();
			}
		}

		if ( SourceController )
		{
			SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
		}
	}

	if ( Data.Target.AbilityActorInfo.IsValid() )
	{
		TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
		TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
	}

	OutProps.EffectContextHandle = Data.EffectSpec.GetContext();
	OutProps.SetSource(SourceASC, SourceAvatarActor, SourceController, SourceCharacter);
	OutProps.SetTarget(TargetASC, TargetAvatarActor, TargetController, TargetCharacter);
}


WL_DEBUG_END
