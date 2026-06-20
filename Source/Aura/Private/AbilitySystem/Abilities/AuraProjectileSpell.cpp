// Property of Andrea Barontini


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Actor/AuraProjectile.h"
#include "Character/AuraCharacterBase.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile() const
{
	if (const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority(); !bIsServer) return;

	if (ICombatInterface* OwningCombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector WeaponSocketLocation = OwningCombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(WeaponSocketLocation);
		// TODO: set the projectile rotation based on the aim
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, 
			SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// TODO: Give the projectile the gameplay effect spec for causing damage
		Projectile->FinishSpawning(SpawnTransform);
	}
}
