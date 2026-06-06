// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IIHighlightable;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

enum ETraceCase
{
	A,B,C,D,E
};

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputMappingContext> AuraContext;
	
/*
 * Movement Input
*/
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
/*
 * MouseTrace hits
*/
	// I could have used raw pointers, but using TScriptInterface wrapper for interface objects is better
	TScriptInterface<IIHighlightable> CurrentHighlightableActor;
	TScriptInterface<IIHighlightable> PreviousHighlightableActor;
/*
 * Utilities
*/
	FVector GetRelativeVector(const EAxis::Type Axis) const;
	void MouseTrace();
	ETraceCase CheckTraceCase() const;
	void HandleTraceCases(ETraceCase TraceCase) const;
};
