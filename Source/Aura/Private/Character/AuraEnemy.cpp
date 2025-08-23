// Property of Andrea Barontini


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::SetActivateCustomDepth(bool bActive) const
{
	GetMesh()->SetRenderCustomDepth(bActive);
	Weapon->SetRenderCustomDepth(bActive);
}

void AAuraEnemy::HighlightActor()
{
	SetActivateCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetActivateCustomDepth(false);
}
