// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "HawaianCharacter.h"


// Sets default values
AHawaianCharacter::AHawaianCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHawaianCharacter::BeginPlay()
{
	Super::BeginPlay();
	Killed = false;
}

// Called every frame
void AHawaianCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHawaianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

