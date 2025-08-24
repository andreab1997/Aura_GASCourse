// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove,
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;
/*
 * Instant effect
*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
/*
 * Duration effect
*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;;
/*
 * Infinite effect
*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy= EEffectApplicationPolicy::DoNotApply;;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
	bool bDestroyOnEffectRemoval = false;
	
	UFUNCTION(BlueprintCallable, Category = "Applied Effect")
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	UFUNCTION(BlueprintCallable, Category = "Applied Effect")
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, Category = "Applied Effect")
	void OnEndOverlap(AActor* TargetActor);
private:
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> InfiniteActiveEffectHandles;
};
