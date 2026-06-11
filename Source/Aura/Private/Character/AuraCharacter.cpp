// Property of Andrea Barontini


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	InitCharacterMovement();
	
}

void AAuraCharacter::InitializeHUDOverlay(AAuraPlayerState* AuraPlayerState)
{
	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	// In this case AuraPlayerController can be null. It will be null for a multiplayer game, when this function gets the controller of other clients,
	// So we should not crash here, we should just proceed if the controller is non-null, which means it is actually our controller
	if (AuraPlayerController)
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void AAuraCharacter::InitAbilitySystemAndAttributeSet()
{
	// In this case the aura avatar actor does not own the AbilitySystemComponent, because it is the PlayerState to own it
	// This is generally done as such for the player to avoid problems when respawning the avatar actor
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	// In this case the ability system component itself has been overridden 
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet(); // this function is used to signal that the ASC is ready and set
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this); // setting owner actor and avatar actor
	
	AttributeSet = AuraPlayerState->GetAttributeSet();

	InitializeHUDOverlay(AuraPlayerState);
	
	InitializeDefaultAttributes();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// when this function is called, it is a good moment to init the ASC and AttributeSet on the server
	// Init ability actor info for the server here
	InitAbilitySystemAndAttributeSet();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// when this function is called, it is a good moment to init the ASC and AttributeSet on the clients
	// Init ability actor info for the client here
	InitAbilitySystemAndAttributeSet();
}

void AAuraCharacter::InitCharacterMovement()
{
	//TODO: avoid to hardcode the Yaw rotation rate
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// The following are typical settings for a top-down game like this
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

