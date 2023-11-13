// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Orientation.generated.h"

UCLASS()
class GAMEPLAYMATHEMATICS_API AOrientation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrientation();

	UPROPERTY(EditAnywhere)
	float TriggerDistance = 500.f;

	UPROPERTY(EditAnywhere)
	AActor* BaseActor;

	UPROPERTY(EditAnywhere)
	AActor* TestActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
