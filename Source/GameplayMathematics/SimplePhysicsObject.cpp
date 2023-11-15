// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplePhysicsObject.h"

// Sets default values
ASimplePhysicsObject::ASimplePhysicsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	StaticMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
}

// Called when the game starts or when spawned
void ASimplePhysicsObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimplePhysicsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Velocity * DeltaTime);
}

