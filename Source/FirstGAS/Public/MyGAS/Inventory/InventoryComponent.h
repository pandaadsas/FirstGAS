// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInventoryComponent();
	
	UFUNCTION(BlueprintCallable,Category="Inventory")
	void AddItem(const FGameplayTag& ItemTag, int32 NumItems=1);
protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag,int32>InventoryTagMap;
	
	UFUNCTION(Server, Reliable, Category="Inventory")
	void ServerAddItem(const FGameplayTag& ItemTag, int32 NumItems);

		
};
