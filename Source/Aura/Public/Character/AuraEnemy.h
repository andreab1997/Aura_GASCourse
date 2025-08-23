// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interactions/IHighlightable.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IIHighlightable
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	// IIHighlightInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// IIHighlightInterface end
protected:
	virtual void BeginPlay() override;
private:
/*
 * Utilities
*/
	void SetActivateCustomDepth(const bool bActive) const;
	void InitAbilitySystemComponent();
	void InitializeCustomDepthForHighlight() const;
};
