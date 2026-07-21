// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "MyBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTGAS_API UMyBlueprintLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure)
	static UCharacterClassInfo* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
};
