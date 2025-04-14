// 王乐用于学习Gas的项目，仅供参考


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if ( !bIsServer ) { return; }

	ICombatInterface* ICombat = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if ( ICombat )
	{
		const FVector SocketLocation = ICombat->GetCombatSocketLocation();
		FTransform SpawnTransform;
		// todo: Set the Projectile Rotation
		SpawnTransform.SetLocation(SocketLocation);
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);

		// todo: Give ths Projectile a Gameplay Effect Spec for causing Damage
	}
	
	
	
	// UKismetSystemLibrary::PrintString(this, FString("Active Ability C++"),
	// true, true, FLinearColor::Yellow, 3);
}
