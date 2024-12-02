// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveingPlatform.h"

// Sets default values
AMoveingPlatform::AMoveingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoveingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	

}

// Called every frame
void AMoveingPlatform::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMoveingPlatform::MovePlatform(float DeltaTime) {

	if (ShouldPlatformReturn()) {

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else {
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);	
	}
}

void AMoveingPlatform::RotatePlatform(float DeltaTime) {
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}													

bool AMoveingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > MoveDistance;
}
float AMoveingPlatform::GetDistanceMoved() const {
	return FVector::Dist(StartLocation, GetActorLocation());
}
