// 王乐用于学习Gas的项目，仅供参考

#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
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
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

// 获取生命周期内复制的属性
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

// 当属性发生任何修改前
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if ( GetHealthAttribute() == Attribute )
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if ( GetMaxHealthAttribute() == Attribute )
	{
		NewValue = FMath::Max(0, NewValue);
	}

	if ( GetManaAttribute() == Attribute )
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
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
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
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
