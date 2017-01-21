// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "jam2017PlayerController.h"
#include "SafeZonePawn.h"


// Sets default values
ASafeZonePawn::ASafeZonePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision comp");
}

// Called when the game starts or when spawned
void ASafeZonePawn::BeginPlay()
{
	Super::BeginPlay();
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetPrimaryPlayerController());
	
	
}

// Called every frame
void ASafeZonePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ASafeZonePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

