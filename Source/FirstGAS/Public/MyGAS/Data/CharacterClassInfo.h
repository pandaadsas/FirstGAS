// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */

USTRUCT(BlueprintType)

struct FCharacterClassDefaultInfo
   {
   	GENERATED_BODY()
	
	
   	UPROPERTY(EditDefaultsOnly)
   	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
   	
   	UPROPERTY(EditDefaultsOnly)
   	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
   	
   	UPROPERTY(EditDefaultsOnly)
   	TArray<TSubclassOf<UGameplayAbility>> StartingPassiveAbilities;
   };
UCLASS()

class FIRSTGAS_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,Category = "属性系统|键:GameplayTag, 值:数值", 
			  meta = (DisplayName = "属性映射表", 
					 ToolTip = "通过 GameplayTag 映射到具体的属性值\n键(Key): 属性标签 (如 Attribute.Health)\n值(Value): 属性的数值"))
	TMap<FGameplayTag,FCharacterClassDefaultInfo> CharacterClassInfoMap;
	
};
