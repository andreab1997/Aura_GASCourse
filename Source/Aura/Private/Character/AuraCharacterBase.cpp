// Property of Andrea Barontini


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	// the weapon is a skeletalMeshComponent and it is attached to a specific socket
	// TODO: avoid to hardcode the name of the socket
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilitySystemAndAttributeSet()
{
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon)
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
}

void AAuraCharacterBase::InitializeSecondaryAttributes() const
{
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}

void AAuraCharacterBase::InitializeVitalAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
	InitializeVitalAttributes();
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level) const
{
	check(GameplayEffectClass)
	check(IsValid(GetAbilitySystemComponent()))
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::AddCharacterStartupAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	if (!HasAuthority()) return;
	
	AuraASC->AddCharacterStartupAbilities(StartupAbilities);
}

