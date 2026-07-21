// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MyGAS/MyAbilitySystemComponent.h"


// Sets default values for this component's properties
UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f); 
		GiveAbility(AbilitySpec);
	}
}

void UMyAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassivesToGrant)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : PassivesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f); 
		GiveAbility(AbilitySpec);
	}
}

void UMyAbilitySystemComponent::InitializeDefaultAttributes( const TSubclassOf<UGameplayEffect>& AttributeEffect)
{
	
	const FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(AttributeEffect, 1.f, EffectContext);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}


// Called when the game starts
void UMyAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

