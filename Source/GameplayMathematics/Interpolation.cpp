// Fill out your copyright notice in the Description page of Project Settings.


#include "Interpolation.h"

// Sets default values
AInterpolation::AInterpolation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInterpolation::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(BaseActor) || !IsValid(TestActor)) return;
	
	FVector BaseLocation = BaseActor->GetActorLocation();
	// Above
	Locations.Add(BaseLocation + BaseActor->GetActorUpVector() * 200);
	// Right
	Locations.Add(BaseLocation + BaseActor->GetActorRightVector() * 200);
	// Below
	Locations.Add(BaseLocation - BaseActor->GetActorUpVector() * 200);
	// In front
	Locations.Add(BaseLocation + BaseActor->GetActorForwardVector() * 200);
	// Left
	Locations.Add(BaseLocation - BaseActor->GetActorRightVector() * 200);
	// Behind
	Locations.Add(BaseLocation - BaseActor->GetActorForwardVector() * 200);

	TestActor->SetActorLocation(Locations[0]);
	PreviousIndex = 0;
	Index = 1;
}

void AInterpolation::IncrementIndex()
{
	PreviousIndex = Index;
	Index = (Index + 1) % Locations.Num();
	Time = 0;
}

// Called every frame
void AInterpolation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime / Duration;
	Time = FMath::Clamp(Time, 0.f, 1.f);
	
	FVector Start = Locations[PreviousIndex];
	FVector End = Locations[Index];

	FVector LerpedLocation = FMath::Lerp(Start, End, Time);

	TestActor->SetActorLocation(LerpedLocation);

	if (Time >= 1.f)
	{
		IncrementIndex();
	}

}

