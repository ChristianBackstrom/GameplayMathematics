// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsBall.h"
#include "GameFramework/Actor.h"
#include "PerlinNoiseFlowField.generated.h"
USTRUCT()
struct FFlowNode
{
	GENERATED_BODY()

	FVector Direction;
	FIntVector2 Index;
	FVector2d NoiseLocation;

	FFlowNode()
	{
		Direction = FVector(0,0,0);
		Index = FIntVector2(0,0);
		NoiseLocation = FVector2d(0,0);
	}
	
	FFlowNode(FVector direction, FIntVector2 index, FVector2d noiseLocation)
	{
		Direction = direction;
		Index = index;
		NoiseLocation = noiseLocation;
	}
};

UCLASS()
class GAMEPLAYMATHEMATICS_API APerlinNoiseFlowField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinNoiseFlowField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool ShowDebugArrows = true;

	UPROPERTY(EditAnywhere)
	FIntVector2 FlowFieldSize;

	UPROPERTY(EditAnywhere)
	float Zoom;

	UPROPERTY()
	TArray<APhysicsBall*> PhysicsBalls;

	UPROPERTY(EditAnywhere)
	int BallAmount = 10;
	
	UPROPERTY(EditAnywhere)
	float BallForce = 100;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntVector2, FFlowNode> Nodes;

	FVector2D GetSeededLocation(float x, float y);

	FFlowNode* GetClosestNode(FVector location);
	
	const float pi = PI;

	float Time = 0;

	UPROPERTY(EditAnywhere)
	float TimeScale = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
