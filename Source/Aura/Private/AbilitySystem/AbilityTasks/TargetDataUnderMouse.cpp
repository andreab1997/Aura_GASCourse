// Property of Andrea Barontini


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::GetTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;		
}

void UTargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		//We are on the client, so we send cursor data to server
		SendMouseCursorData();
	}
	else
	{
		//We are on the server to listen for cursor data
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		// We call the first function above to wait for target data from the client, and once received are calling the OnTargetDataReplicatedCallback callback.
		// However, we may be too slow and having already received the target data before binding that callback.
		// In this case I call the function CallReplicatedTargetDataDelegatesIfSet that forces the callback if the target data has been received. If it does so, it returns the true in the boolean bCalledDelegate,
		// So now if bCalledDelegate is true, we do nothing, otherwise we need to wait for the target data
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	
}

void UTargetDataUnderMouse::SendMouseCursorData() const
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	FHitResult HitResult;
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;
	
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(), 
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(), 
		AbilitySystemComponent->ScopedPredictionKey);
	
	// There are reasons not to broadcast (for example, the ability is ended before)
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag) const
{
	// Here we are telling the ASC to remove the cache of the DataHandle
	AbilitySystemComponent.Get()->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
