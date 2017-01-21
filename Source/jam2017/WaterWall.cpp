// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "WaterWall.h"


// Sets default values
AWaterWall::AWaterWall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaterWall::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AWaterWall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	auto location = GetActorLocation();
	location.Z += 0.3f * DeltaTime;
	SetActorLocation(location);
}

// Called to bind functionality to input
void AWaterWall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

