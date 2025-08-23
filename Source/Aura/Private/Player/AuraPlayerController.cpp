// Property of Andrea Barontini


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactions/IHighlightable.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MouseTrace();
}

ETraceCase AAuraPlayerController::CheckTraceCase() const
{
	ETraceCase TraceCase;
	if (PreviousHighlightableActor == nullptr)
	{
		if (CurrentHighlightableActor == nullptr) TraceCase = A;
		else TraceCase = C;
	}
	else
	{
		if (CurrentHighlightableActor == nullptr) TraceCase = B;
		else if (CurrentHighlightableActor != PreviousHighlightableActor) TraceCase = D;
		else TraceCase = E;
	}
	return TraceCase;
}

void AAuraPlayerController::HandleTraceCases(ETraceCase TraceCase) const
{
	switch (TraceCase)
	{
	case B:
		PreviousHighlightableActor->UnHighlightActor();
		break;
	case C:
		CurrentHighlightableActor->HighlightActor();
		break;
	case D:
		CurrentHighlightableActor->HighlightActor();
		PreviousHighlightableActor->UnHighlightActor();
		break;
	default:
		break;
	}
}

void AAuraPlayerController::MouseTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) return;
	PreviousHighlightableActor = CurrentHighlightableActor;
	CurrentHighlightableActor = HitResult.GetActor(); //Thanks to the TScriptInterface I do not need a cast here

	/*
	 * According to the values of PreviousHighlightableActor and CurrentHighlightableActor we may have several scenarios:
	 *	A. Both NULL:
	 *		Do nothing
	 *	B. PreviousHighlightableActor not NULL and CurrentHighlightableActor NULL:
	 *		Unhighlight PreviousHighlightableActor
	 *	C. PreviousHighlightableActor NULL and CurrentHighlightableActor not NULL:
	 *		Highlight CurrentHighlightableActor
	 *	D. PreviousHighlightableActor not NULL and CurrentHighlightableActor not NULL, but they are different:
	 *		Highlight CurrentHighlightableActor, UnHighlight PreviousHighlightableActor
	 *	E. PreviousHighlightableActor not NULL and CurrentHighlightableActor not NULL, and they are the same:
	 *		Do Nothing
	 */
	ETraceCase TraceCase = CheckTraceCase();
	HandleTraceCases(TraceCase);
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

FVector AAuraPlayerController::GetRelativeVector(const EAxis::Type Axis) const
{
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Vector = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
	return Vector;
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputActionVector = InputActionValue.Get<FVector2D>();
	// I need to find the forward and right direction now
	const FVector Forward = GetRelativeVector(EAxis::X);
	const FVector Right = GetRelativeVector(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Forward, InputActionVector.Y);
		ControlledPawn->AddMovementInput(Right, InputActionVector.X);
	}
}
