// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Intersection.generated.h"

USTRUCT(BlueprintType)
struct FIntersectionSphere
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float Radius;
	UPROPERTY(EditAnywhere)
	FVector RelativeLocation;

	FIntersectionSphere()
	{
		Radius = 0;
		RelativeLocation = FVector::ZeroVector;
	}
};

UCLASS()
class GAMEPLAYMATHEMATICS_API AIntersection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersection();

	UPROPERTY(EditAnywhere)
	AActor* BaseActor;

	UPROPERTY(EditAnywhere)
	AActor* TestActor;

	UPROPERTY(EditAnywhere)
	TArray<FIntersectionSphere> IntersectionSpheres;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static bool SphereSphereIntersection(FVector ALocation, float ARadius, FVector BLocation, float BRadius, FVector& ContactPoint);
	
	// Line-Sphere Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RaySphere(const FVector Origin, const FVector Direction, const FVector Center, const float Radius, FVector& ContactPoint);

};
