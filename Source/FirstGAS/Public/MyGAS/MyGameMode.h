// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class FIRSTGAS_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	
	UCharacterClassInfo* GetCharacterClassDefaultInfo() const ;
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassDefaultInfo;
};
