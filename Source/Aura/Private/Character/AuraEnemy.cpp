// Property of Andrea Barontini


#include "Character/AuraEnemy.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraEnemy::InitAbilitySystemComponent()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // Minimal is ok for enemies, but not for the player
}

void AAuraEnemy::InitializeCustomDepthForHighlight() const
{
	// Setup for the highlighting
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::InitializeHealthBarWidget()
{
	if (UAuraUserWidget* HealthBarWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}
}

void AAuraEnemy::InitAbilitySystemAndAttributeSet()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	InitializeDefaultAttributes();
}

AAuraEnemy::AAuraEnemy()
{
	InitializeCustomDepthForHighlight();
	InitAbilitySystemComponent();
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(FName("HealthBarWidget"));
	HealthBar->SetupAttachment(GetRootComponent());;
}

void AAuraEnemy::SetActivateCustomDepth(const bool bActive) const
{
	// This is called when it is necessary to highlight the character
	GetMesh()->SetRenderCustomDepth(bActive);
	Weapon->SetRenderCustomDepth(bActive);
}

void AAuraEnemy::SetupHealthChangeDelegates() const
{
	const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(GetAttributeSet());
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
	// Initial values
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemAndAttributeSet();
	// Health Bar
	InitializeHealthBarWidget();
	SetupHealthChangeDelegates();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AAuraEnemy::HighlightActor()
{
	SetActivateCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetActivateCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

