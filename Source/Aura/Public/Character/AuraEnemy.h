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
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IIHighlightable // interface to highlight characters in the viewport
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	// IIHighlightInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// IIHighlightInterface end
	
	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	// End Combat Interface
protected:
	virtual void BeginPlay() override;
private:
/*
 * Utilities
*/
	void SetActivateCustomDepth(const bool bActive) const;
	void InitAbilitySystemComponent();
	void InitializeCustomDepthForHighlight() const;

protected:
	virtual void InitAbilitySystemAndAttributeSet() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
