#include "MyGAS/Inventory/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 NumItems)
{
	AActor* OwnerActor=GetOwner();
	if (!IsValid(OwnerActor))return ;
	if (!OwnerActor->HasAuthority())
	{
		ServerAddItem(ItemTag,NumItems);
		return ;
	}
	if (InventoryTagMap.Contains(ItemTag))
	{
		InventoryTagMap[ItemTag]+=NumItems;
	}
	else
	{
		InventoryTagMap.Emplace(ItemTag,NumItems);
	}
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::Printf(TEXT("Added %d of item %s to inventory."),NumItems,*ItemTag.ToString()));
}

void UInventoryComponent::ServerAddItem_Implementation(const FGameplayTag& ItemTag, int32 NumItems)
{
	AddItem(ItemTag, NumItems);
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	
}





