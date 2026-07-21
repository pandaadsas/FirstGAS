// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGAS/MyBlueprintLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "MyGAS/MyGameMode.h"

UCharacterClassInfo* UMyBlueprintLibrary::GetCharacterClassDefaultInfo(const UObject* WorldContextObject)
{
	if (const AMyGameMode* GM=Cast<AMyGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GM->GetCharacterClassDefaultInfo();
	}
	return nullptr;
}
