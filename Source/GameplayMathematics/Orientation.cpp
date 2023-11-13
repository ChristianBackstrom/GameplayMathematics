// Fill out your copyright notice in the Description page of Project Settings.


#include "Orientation.h"

// Sets default values
AOrientation::AOrientation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrientation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrientation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(BaseActor) || !IsValid(TestActor)) return;

	FVector BaseActorLocation = BaseActor->GetActorLocation();
	FVector TestActorLocation = TestActor->GetActorLocation();
	if (FVector::Distance(BaseActorLocation, TestActorLocation) > TriggerDistance) return;
	
	FVector RelativeDirection = (BaseActorLocation - TestActorLocation).GetSafeNormal();
	
	FVector BaseRight = BaseActor->GetActorRightVector();
	FVector BaseUp = BaseActor->GetActorUpVector();
	FVector BaseForward = BaseActor->GetActorForwardVector();

	// Right and Left check
	if (FVector::DotProduct(BaseRight, RelativeDirection) >= .9f || FVector::DotProduct(-BaseRight, RelativeDirection) >= .9f)
	{
		DrawDebugLine(GetWorld(), BaseActorLocation, TestActorLocation, FColor::Red);
		return;
	}

	// Above and Below check
	if (FVector::DotProduct(BaseUp, RelativeDirection) >= .9f || FVector::DotProduct(-BaseUp, RelativeDirection) >= .9f)
	{
		DrawDebugLine(GetWorld(), BaseActorLocation, TestActorLocation, FColor::Green);
		return;
	}

	// Forward and Behind check
	if (FVector::DotProduct(BaseForward, RelativeDirection) >= .9f || FVector::DotProduct(-BaseForward, RelativeDirection) >= .9f)
	{
		DrawDebugLine(GetWorld(), BaseActorLocation, TestActorLocation, FColor::Blue);
		return;
	}

}

