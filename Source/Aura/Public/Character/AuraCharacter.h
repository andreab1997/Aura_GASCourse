// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Player/AuraPlayerState.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	void InitializeHUDOverlay(AAuraPlayerState* AuraPlayerState);
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	
/*
 * Utilities
*/
	void InitCharacterMovement();
	virtual void InitAbilitySystemAndAttributeSet() override;
	
	
};
