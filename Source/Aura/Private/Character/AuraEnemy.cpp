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
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AAuraEnemy::InitializeCustomDepthForHighlight() const
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

AAuraEnemy::AAuraEnemy()
{
	InitializeCustomDepthForHighlight();
	InitAbilitySystemComponent();
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::SetActivateCustomDepth(const bool bActive) const
{
	GetMesh()->SetRenderCustomDepth(bActive);
	Weapon->SetRenderCustomDepth(bActive);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAuraEnemy::HighlightActor()
{
	SetActivateCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetActivateCustomDepth(false);
}

