// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

// These macros generate getter, setters, getter of the attribute itself and initializer automatically for all our attributes
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


// Convenient struct to hold data about a gameplay effect
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
private:
	GENERATED_BODY()

public:
	UAuraAttributeSet() = default;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
/*
 * Vital Attributes
 */
	
/* Health */
	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing = OnRep_Health) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
/* Mana */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);


	
/*
 * Primary Attributes
 */
/* Strength */
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing = OnRep_Strength) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
/* Intelligence */
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing = OnRep_Intelligence) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Intelligence;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
/* Resilience */
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing = OnRep_Resilience) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Resilience;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
/* Vigor */
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing = OnRep_Vigor) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Vigor;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

/*
 * Secondary Attributes
 */
	/* Armor */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_Armor) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData Armor;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	/* ArmorPenetration */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_ArmorPenetration) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData ArmorPenetration;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	/* BlockChance */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_BlockChance) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData BlockChance;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	/* CriticalHitChance */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitChance) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData CriticalHitChance;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	/* CriticalHitDamage */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitDamage) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData CriticalHitDamage;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	/* CriticalHitResistance */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitResistance) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData CriticalHitResistance;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	/* HealthRegeneration */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_HealthRegeneration) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData HealthRegeneration;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	/* ManaRegeneration */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_ManaRegeneration) // The replicatedUsing meta is needed to replicate the attribute to the clients
	FGameplayAttributeData ManaRegeneration;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	/* Max Health */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	/* Max Mana */
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
