// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereInterpolation.h"

FVector ASphereInterpolation::GetLerpedLocation(FVector A, FVector B, float Alpha)
{
	FVector LerpedLocation = Super::GetLerpedLocation(A, B, Alpha);

	FVector BaseActorLocation = BaseActor->GetActorLocation();

	FVector DirectionFromBase = (BaseActorLocation - LerpedLocation).GetSafeNormal();

	DirectionFromBase *= Radius;
	
	return DirectionFromBase + BaseActorLocation;
}
