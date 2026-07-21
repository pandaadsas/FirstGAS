// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MyGAS/MyPlayerState.h"
#include "Public/MyGAS/MyAbilitySystemComponent.h"
#include "Public/MyGAS/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet=CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	//AttributeSet被设为TSubclassof,和教学视频不一致
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UMyAbilitySystemComponent* AMyPlayerState::GetMyAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UMyAttributeSet* AMyPlayerState::GetMyAttributeSet() const
{
	return AttributeSet;
}
