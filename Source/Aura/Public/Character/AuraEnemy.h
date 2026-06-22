// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interactions/IHighlightable.h"
#include "WidgetController/AuraOverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
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
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeDefaultAttributes() const override;
private:
/*
 * Utilities
*/
	void SetActivateCustomDepth(const bool bActive) const;
	void SetupHealthChangeDelegates() const;
	void InitAbilitySystemComponent();
	void InitializeCustomDepthForHighlight() const;
	void InitializeHealthBarWidget();

protected:
	virtual void InitAbilitySystemAndAttributeSet() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
