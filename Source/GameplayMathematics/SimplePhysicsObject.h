// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimplePhysicsObject.generated.h"

UCLASS()
class GAMEPLAYMATHEMATICS_API ASimplePhysicsObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimplePhysicsObject();

	FVector Velocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetRadius() const
	{
		return (100 * GetActorScale3D().X) / 2;
	}

};
