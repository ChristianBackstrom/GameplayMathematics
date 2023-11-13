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

}

