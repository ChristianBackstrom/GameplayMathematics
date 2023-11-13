// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpolation.h"
#include "SphereInterpolation.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYMATHEMATICS_API ASphereInterpolation : public AInterpolation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Radius;

protected:
	virtual FVector GetLerpedLocation(FVector A, FVector B, float Alpha) override;
	
};
