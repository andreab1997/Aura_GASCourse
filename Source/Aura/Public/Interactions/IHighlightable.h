// Property of Andrea Barontini

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHighlightable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHighlightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IIHighlightable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
