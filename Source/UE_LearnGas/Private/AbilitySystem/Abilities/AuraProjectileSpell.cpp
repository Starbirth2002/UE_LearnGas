// 王乐用于学习Gas的项目，仅供参考


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Debug 
	{
		// const bool bIsServer = HasAuthority(&ActivationInfo);
		// if ( !bIsServer ) { return; }
		//
		// ICombatInterface* ICombat = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
		// if ( ICombat )
		// {
		// 	const FVector SocketLocation = ICombat->GetCombatSocketLocation();
		// 	FTransform SpawnTransform;
		// 	// todo: Set the Projectile Rotation
		// 	SpawnTransform.SetLocation(SocketLocation);
		// 	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		// 		ProjectileClass, SpawnTransform,
		// 		GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),
		// 		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//
		// 	Projectile->FinishSpawning(SpawnTransform);
		//
		// 	// todo: Give ths Projectile a Gameplay Effect Spec for causing Damage
		// }
	}
	
	
	
	// UKismetSystemLibrary::PrintString(this, FString("Active Ability C++"),
	// true, true, FLinearColor::Yellow, 3);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if ( !bIsServer ) { return; }

	ICombatInterface* ICombat = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if ( ICombat )
	{
		const FVector SocketLocation = ICombat->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		const FTransform SpawnTransform(Rotation, SocketLocation, FVector::One());
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// 在生成前创建伤害效果
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetAvatarActorFromActorInfo());

		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		FAuraGameplayTags GameTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameTags.Damage, 50.f);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
