// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AuraAttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependecies() override;
};
