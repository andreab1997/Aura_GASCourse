// Property of Andrea Barontini


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interactions/CombatInterface.h"


UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target (this is not really needed here, but I leave it here for future reference in case it will be necessary
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	// Get the value of the Intelligence attribute
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Int = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Int);
	Int = FMath::Max<float>(Int, 0.f); // make sure is >= 0
	
	// Get level from CombatInterface
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 50.f + 2.5f * Int + 15.f * PlayerLevel;
}
