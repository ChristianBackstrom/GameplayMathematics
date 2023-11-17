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

	FBox Box = FBox();
	Box.Max = FVector(FlowFieldSize.X, FlowFieldSize.Y, 1) * 100;
	Box.Min = FVector::UpVector;

	for (int i = 0; i < BallAmount; ++i)
	{
		FVector spawnLocation = FMath::RandPointInBox(Box);
	
		PhysicsBalls.Add(GetWorld()->SpawnActor<APhysicsBall>(spawnLocation, FRotator::ZeroRotator));
	}
	
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

	const UWorld* World = GetWorld();

	for (const auto PhysicsBall : PhysicsBalls)
	{
		PhysicsBall->StaticMesh->AddForce(FVector::ForwardVector * 982.f);
	}

	Time += DeltaTime * TimeScale;

	
	for (int x = 0; x < FlowFieldSize.X; ++x)
	{
		for (int y = 0; y < FlowFieldSize.Y; ++y)
		{
			FFlowNode* FlowNode = Nodes.Find(FIntVector2(x,y));
			FVector location = FVector::One() * 100;
			location.X *= FlowNode->Index.X;
			location.Y *= FlowNode->Index.Y;

			const float perlinNoise = FMath::PerlinNoise2D(GetSeededLocation(FlowNode->Index.X + Time, FlowNode->Index.Y + Time)) * 2;
			FVector direction = FVector(1,0,0).RotateAngleAxisRad(pi * perlinNoise, FVector::UpVector);
			FlowNode->Direction = direction;

			// DrawDebugLine(World, location, location + FlowNode.Direction * 100, FColor::Red, false,-1,0, 5);
			if (ShowDebugArrows)
				DrawDebugDirectionalArrow(World, location, location + direction * 100, 100, FColor::Red, false, -1, 0, 10.f);
		}
	}
	
	const FVector totalSize = FVector(FlowFieldSize.X * 100, FlowFieldSize.Y * 100, 1);
	for (const auto PhysicsBall : PhysicsBalls)
	{
		const FVector ballLocation = PhysicsBall->GetActorLocation();
		if (ballLocation.X > totalSize.X || ballLocation.X < 0 || ballLocation.Y > totalSize.Y || ballLocation.Y < 0)
		{
			FBox Box = FBox();
			Box.Max = totalSize;
			Box.Min = FVector::UpVector;

			FVector randomLocation = FMath::RandPointInBox(Box);
			PhysicsBall->SetActorLocation(randomLocation);
			PhysicsBall->StaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
	
		if (FFlowNode* node = GetClosestNode(PhysicsBall->GetActorLocation()); node != nullptr)
		{
			PhysicsBall->StaticMesh->AddForce(node->Direction * BallForce);
		}
	}
}

FFlowNode* APerlinNoiseFlowField::GetClosestNode(FVector location)
{
	location /= 100;

	FIntVector2 Index = FIntVector2(FMath::RoundToInt(location.X), FMath::RoundToInt(location.Y));

	FFlowNode* node = Nodes.Find(Index);
	
	return node;
}


FVector2D APerlinNoiseFlowField::GetSeededLocation(float x, float y)
{
	return FVector2d((x)/(FlowFieldSize.X * FlowFieldSize.Y) / Zoom, (y)/(FlowFieldSize.X * FlowFieldSize.Y) / Zoom);
}


