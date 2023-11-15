// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplePhysicsObject.h"
#include "Intersection.h"
#include "GameFramework/Actor.h"
#include "SimpleCollision.generated.h"

class USphereComponent;
UCLASS()
class GAMEPLAYMATHEMATICS_API ASimpleCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleCollision();
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASimplePhysicsObject> PhysicsActorPrefab;
	
	UPROPERTY(EditAnywhere)
	int PhysicsActorAmount = 10;

	
	UPROPERTY(VisibleAnywhere)
	TArray<ASimplePhysicsObject*> PhysicsActors;

	UPROPERTY(EditAnywhere)
	AIntersection* Intersection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Radius = 500;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

	UPROPERTY()
	USphereComponent* SphereComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
