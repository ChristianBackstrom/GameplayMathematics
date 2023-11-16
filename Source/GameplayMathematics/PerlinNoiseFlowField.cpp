// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinNoiseFlowField.h"

// Sets default values
APerlinNoiseFlowField::APerlinNoiseFlowField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void APerlinNoiseFlowField::BeginPlay()
{
	Super::BeginPlay();

	for (int x = 0; x < FlowFieldSize.X; ++x)
	{
		for (int y = 0; y < FlowFieldSize.Y; ++y)
		{
			FIntVector2 index = FIntVector2(x, y);
			FVector2d location = GetSeededLocation(x,y);
			

			float perlinNoise = FMath::PerlinNoise2D(location) * 2;
			FVector direction = FVector(1,0,0).RotateAngleAxisRad(pi * perlinNoise, FVector::UpVector);

			FFlowNode node = FFlowNode(direction, index, location);
			Nodes.Add(index, node);
		}
	}
}

// Called every frame
void APerlinNoiseFlowField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();

	Time += DeltaTime * TimeScale;
	
	for (auto nodePair : Nodes)
	{
		FFlowNode FlowNode = nodePair.Value;
		FVector location = FVector::One() * 100;
		location.X *= FlowNode.Index.X;
		location.Y *= FlowNode.Index.Y;
		
		float perlinNoise = FMath::PerlinNoise2D(GetSeededLocation(FlowNode.Index.X + Time, FlowNode.Index.Y + Time)) + 1.5f;
		FVector direction = FVector(1,0,0).RotateAngleAxisRad(pi * perlinNoise, FVector::UpVector);

		// DrawDebugLine(World, location, location + FlowNode.Direction * 100, FColor::Red, false,-1,0, 5);
		DrawDebugDirectionalArrow(World, location, location + direction * 100, 100, FColor::Red, false, -1, 0, 10.f);
	}

}

FVector2D APerlinNoiseFlowField::GetSeededLocation(float x, float y)
{
	return FVector2d((x)/(FlowFieldSize.X * FlowFieldSize.Y) / Zoom, (y)/(FlowFieldSize.X * FlowFieldSize.Y) / Zoom);
}

