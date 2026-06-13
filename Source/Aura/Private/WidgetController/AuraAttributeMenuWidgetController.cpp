// Property of Andrea Barontini


#include "WidgetController/AuraAttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAuraAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto& Pair : AuraAttributeSet->TagsToAttribute)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAuraAttributeMenuWidgetController::BindCallbacksToDependecies()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AuraAttributeSet->TagsToAttribute)
	{
		FGameplayAttribute GameplayAttribute = Pair.Value();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GameplayAttribute).AddLambda(
		[this, Pair, GameplayAttribute](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, GameplayAttribute);
		}
		);
	}
}

void UAuraAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
