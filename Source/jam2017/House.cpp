// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "House.h"
#include "jam2017PlayerController.h"


// Sets default values
AHouse::AHouse()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Population = 0;
	IsAlerted = false;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision comp");
}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{
	Super::BeginPlay();
	Ajam2017PlayerController * ctrl = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	ctrl->TotalPopulationTrapped += Population;
	ctrl->TotalPopulationLeft += Population;
	ctrl->MaxPopulation += Population;
}

// Called every frame
void AHouse::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHouse::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

