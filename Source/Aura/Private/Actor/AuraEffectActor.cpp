// Property of Andrea Barontini


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAsc == nullptr) return;
	
	check(GameplayEffectClass);
	// To apply a gameplay effect I need first to produce an effect context handle
	// An effect context handle is a wrapper for the specific gameplay effect (or one of its subclasses)
	// We can use it for example to set the source of the gameplay effect, as we do below
	FGameplayEffectContextHandle GEContextHandle = TargetAsc->MakeEffectContext();
	GEContextHandle.AddSourceObject(this); // Object that cause the effect
	
	// Then, in order to call ApplyGameplayEffectSpecToSelf we need an FGameplayEffectSpec which is
	// created using the FGameplayEffectContextHandle created above.
	const FGameplayEffectSpecHandle GESpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.f, GEContextHandle);
	
	// Finally we can call the following function to apply the effect
	// There are other versions
	// Note that we used .Data to get the actual FGameplayEffectSpec from the Handle. This returns a shared_ptr, from which we used Get() to get the
	// raw pointer. From the raw pointer, to get the required const reference, we dereferenced with *
	TargetAsc->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get()); 
}

