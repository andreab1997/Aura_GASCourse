// Property of Andrea Barontini


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	InitCharacterMovement();
	
}

void AAuraCharacter::InitAbilitySystemAndAttributeSet()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	AttributeSet = AuraPlayerState->GetAttributeSet();

	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	// In this case AuraPlayerController can be null, and it will be null for a multiplayer game, when this function gets the controller of other clients
	// So we should not crash here, we should just proceed if the controller is non-null which means it is actually our controller
	if (AuraPlayerController)
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the server here
	InitAbilitySystemAndAttributeSet();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client here
	InitAbilitySystemAndAttributeSet();
}

void AAuraCharacter::InitCharacterMovement()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// The following are typical settings for a top-down game like this
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

