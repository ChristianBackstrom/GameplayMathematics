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
		float testActorRadius = (100 * TestActor->GetActorScale3D().X)/2;
		FVector ContactPoint;

		bool intersected = SphereSphereIntersection(location, intersectionSphere.Radius, testActorLocation, testActorRadius, ContactPoint);
		FColor color = intersected ? FColor::Green : FColor::Red;

		DrawDebugSphere(GetWorld(), location, intersectionSphere.Radius, 10, color, false, -1, 0, 2);
		if (intersected)
			DrawDebugLine(GetWorld(), ContactPoint, location, FColor::Blue, false, -1, 0, 5);
	}
}

bool AIntersection::SphereSphereIntersection(FVector ALocation, float ARadius, FVector BLocation, float BRadius, FVector& ContactPoint)
{
	float TotalRadius = ARadius + BRadius;
	FVector Diff = ALocation - BLocation;

	if (Diff.Size() < TotalRadius)
	{
		FVector Direction = BLocation - ALocation;
		RaySphere(ALocation, Direction.GetSafeNormal(), BLocation, BRadius, ContactPoint);
		return true;
	}

	return false;
}

bool AIntersection::RaySphere(const FVector Origin, const FVector Direction, const FVector Center, const float Radius,
	FVector& ContactPoint)
{
	const auto W = Center - Origin;
	const double WSQ = W.Dot(W);
	const double Projection = W.Dot(Direction);
	const float RSQ = Radius * Radius;

	// If sphere is behind ray, no intersection
	if(Projection < 0.f && WSQ > RSQ)
		return false;

	const auto VSQ = Direction.Dot(Direction);

	// Diff vs radius
	const auto bIntersects = (VSQ * WSQ - Projection * Projection <= VSQ * Radius * Radius);

	if(bIntersects)
	{
		const double B = 2.f * Projection;
		const double C = WSQ - Radius * Radius;
		const double Discriminant = B * B - 4 * VSQ * C;
		const double T = (B - FMath::Sqrt(Discriminant)) / (2.f * VSQ);

		if(Discriminant < 0)
			ContactPoint = Origin + (Direction * -1.f);
		else
			ContactPoint = Origin + (Direction * T);
	}
		
	return bIntersects;
}

