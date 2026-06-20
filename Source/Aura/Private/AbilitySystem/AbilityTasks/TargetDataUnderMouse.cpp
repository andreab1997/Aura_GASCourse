// Property of Andrea Barontini


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::GetTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;		
}

void UTargetDataUnderMouse::Activate()
{
	FHitResult HitResult;
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	ValidData.Broadcast(HitResult.ImpactPoint);
}
