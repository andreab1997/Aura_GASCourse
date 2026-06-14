// Property of Andrea Barontini


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
			return Action.InputAction;
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("InputAction for InputTag %s not found in AuraInputConfig"), *InputTag.ToString());
	}
	return nullptr;
}
