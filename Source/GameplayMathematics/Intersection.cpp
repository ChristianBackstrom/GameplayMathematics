// Fill out your copyright notice in the Description page of Project Settings.


#include "Intersection.h"

// Sets default values
AIntersection::AIntersection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntersection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIntersection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(BaseActor) || !IsValid(TestActor)) return;

	FVector testActorLocation = TestActor->GetActorLocation();

	for (auto intersectionSphere : IntersectionSpheres)
	{
		FVector location = BaseActor->GetActorLocation() + intersectionSphere.RelativeLocation;
		
		FColor color = FVector::Distance(location, testActorLocation) < intersectionSphere.Radius ? FColor::Green : FColor::Red;

		DrawDebugSphere(GetWorld(), location, intersectionSphere.Radius, 10, color, false, -1, 0, 5);
	}
}

