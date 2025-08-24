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


// Note that this function is kept here mostly for reference and for future usage, as we implemented the same in BPs
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
	// We can even look at the duration policy
	bool bIsInfinite = GESpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	// Finally we can call the following function to apply the effect
	// There are other versions
	// Note that we used .Data to get the actual FGameplayEffectSpec from the Handle. This returns a shared_ptr, from which we used Get() to get the
	// raw pointer. From the raw pointer, to get the required const reference, we dereferenced with *
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAsc->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get());
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		InfiniteActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetAsc);
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	if (DurationEffectApplicationPolicy ==  EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	if (InfiniteEffectApplicationPolicy ==  EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	if (DurationEffectApplicationPolicy ==  EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	if (InfiniteEffectApplicationPolicy ==  EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto HandlePair : InfiniteActiveEffectHandles)
		{
			if (TargetASC ==  HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			InfiniteActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

