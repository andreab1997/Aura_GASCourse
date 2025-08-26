// Property of Andrea Barontini


#include "WidgetController/AuraOverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAuraOverlayWidgetController::BindCallbacksToDependecies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	// Binding delegates for Health and MaxHealth changed
	// Leaving here an example on how to do the same without lambda
	/*
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(
		this, &UAuraOverlayWidgetController::HealthChanged);
	*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		 [this](const FOnAttributeChangeData& Data) -> void {OnHealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		 [this](const FOnAttributeChangeData& Data) -> void {OnMaxHealthChanged.Broadcast(Data.NewValue);});
	// Binding delegates for Mana and MaxMana changed
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		 [this](const FOnAttributeChangeData& Data) -> void {OnManaChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		 [this](const FOnAttributeChangeData& Data) -> void {OnMaxManaChanged.Broadcast(Data.NewValue);});
	// Binding to EffectAssetTags delegate
	// Note in this case we are using a lambda function as delegate instead
	// The "this" inside the square brackets is for capturing variable. In other words, the lambda does not know
	// anything about the object it is inside, unless you pass a reference to it in the square brackets.
	// In this way it is able to call the DataTableRowByTag function which is owned by this class
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) -> void
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
				{
					const FUIWidgetRow* Row = DataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRow.Broadcast(*Row);
				}
			}
		}
	);
}