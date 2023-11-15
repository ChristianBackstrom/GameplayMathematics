// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleCollision.h"

#include "Intersection.h"
#include "Components/SphereComponent.h"

// Sets default values
ASimpleCollision::ASimpleCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetHiddenInGame(false);
	
}

// Called when the game starts or when spawned
void ASimpleCollision::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < PhysicsActorAmount; ++i)
	{
		FVector SpawnPoint =  FMath::VRand() * FMath::RandRange(0.f, Radius - 50.f) + GetActorLocation();
		FActorSpawnParameters SpawnParameters;
		ASimplePhysicsObject* PhysicsObject = GetWorld()->SpawnActor<ASimplePhysicsObject>(PhysicsActorPrefab, SpawnPoint, FRotator::ZeroRotator);
		PhysicsActors.Add(PhysicsObject);

		PhysicsObject->Velocity = FMath::VRand() * Speed;
	}
}

// Called every frame
void ASimpleCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsValid(Intersection)) return;
	
	for (int i = 0; i < PhysicsActors.Num(); ++i)
	{
		ASimplePhysicsObject* PhysicsObject = PhysicsActors [i];
		FVector ALocation = PhysicsObject->GetActorLocation();
		float ARadius = PhysicsObject->GetRadius();

		for (int j = 0; j < PhysicsActors.Num(); ++j)
		{
			ASimplePhysicsObject* PhysicsObjectToTest = PhysicsActors [j];
			if (PhysicsObject == PhysicsObjectToTest) continue;
			
			FVector BLocation = PhysicsObjectToTest->GetActorLocation();
			float BRadius = PhysicsObjectToTest->GetRadius();

			FVector ContactPoint;

			const bool intersected = Intersection->SphereSphereIntersection(ALocation, ARadius, BLocation, BRadius, ContactPoint);

			if (intersected)
			{
				FVector velocity = PhysicsObject->Velocity;
				FVector direction = velocity.GetSafeNormal();
				FVector normal = -(ContactPoint - BLocation).GetSafeNormal();
				FVector reflectedVelocity = direction - FVector::DotProduct(direction, normal) * normal * 2.f;

				PhysicsObject->Velocity = reflectedVelocity * velocity.Size();
				continue;
			}

			float distance = FVector::Distance(GetActorLocation(), ALocation);

			if (distance >= Radius - ARadius)
			{
				FVector velocity = PhysicsObject->Velocity;
				PhysicsObject->Velocity = -velocity;
			}

			if (distance > Radius + ARadius)
			{
				FVector SpawnPoint =  FMath::VRand() * FMath::RandRange(0.f, Radius - 50.f) + GetActorLocation();

				PhysicsObject->SetActorLocation(SpawnPoint);
			}
		}
	}
}

void ASimpleCollision::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (IsValid(SphereComponent))
	{
		SphereComponent->SetSphereRadius(Radius);
	}
}

