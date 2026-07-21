// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UBoxComponent;

UCLASS()
class FIRSTGAS_API AEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AEffectActor();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent>ActorMesh;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent>OverlapBox;
	
	UPROPERTY(EditAnywhere, Category = "Custom Values|Effects")
	TSubclassOf<class UGameplayEffect>OverlapEffect;
};
