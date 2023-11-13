// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interpolation.generated.h"

UCLASS()
class GAMEPLAYMATHEMATICS_API AInterpolation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterpolation();

	UPROPERTY(EditAnywhere)
	AActor* BaseActor;

	UPROPERTY(EditAnywhere)
	AActor* TestActor;

	UPROPERTY(EditAnywhere)
	float Duration;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FVector> Locations;
	
	int Index;
	int PreviousIndex;

	float Time = 0;
	

	void IncrementIndex();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
