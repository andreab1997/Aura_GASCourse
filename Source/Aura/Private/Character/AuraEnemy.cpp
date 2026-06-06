// Property of Andrea Barontini


#include "Character/AuraEnemy.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

void AAuraEnemy::InitAbilitySystemComponent()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // Minimal is ok for enemies, but not for the player
}

void AAuraEnemy::InitializeCustomDepthForHighlight() const
{
	// Setup for the highlighting
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::InitAbilitySystemAndAttributeSet()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

AAuraEnemy::AAuraEnemy()
{
	InitializeCustomDepthForHighlight();
	InitAbilitySystemComponent();
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::SetActivateCustomDepth(const bool bActive) const
{
	// This is called when it is necessary to highlight the character
	GetMesh()->SetRenderCustomDepth(bActive);
	Weapon->SetRenderCustomDepth(bActive);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemAndAttributeSet();
	
}

void AAuraEnemy::HighlightActor()
{
	SetActivateCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetActivateCustomDepth(false);
}

