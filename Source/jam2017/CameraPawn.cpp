// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "CameraPawn.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>("Movement comp");
	MovementComp->MaxSpeed = 50000.0f;
	MovementComp->Acceleration = 50000.0f;
	MovementComp->Deceleration = 50000.0f;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

