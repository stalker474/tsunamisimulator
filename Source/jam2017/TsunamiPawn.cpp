// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "TsunamiPawn.h"
#include "jam2017PlayerController.h"
#include "HawaianCharacter.h"
#include "House.h"

void ATsunamiPawn::TriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHouse * house = Cast<AHouse>(OtherActor);
	AHawaianCharacter * character = Cast<AHawaianCharacter>(OtherActor);
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	if (!pc)
		return;
	if (house)
	{
		pc->TotalPopulationLeft -= house->Population;
		pc->TotalPopulationTrapped -= house->Population;
		house->Population = 0;
	}
	else if (character)
	{
		pc->TotalPopulationLeft --;
	}
		
}

// Sets default values
ATsunamiPawn::ATsunamiPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision comp");
}

// Called when the game starts or when spawned
void ATsunamiPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATsunamiPawn::TriggerEnter);
}

// Called every frame
void ATsunamiPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	if (pc->TimeBeforeCatastrophy < 0.0f)
	{
		auto location = GetActorLocation();
		location.X -= 150.0f * DeltaTime;
		SetActorLocation(location);
		this->SetActorHiddenInGame(false);
	}

}

// Called to bind functionality to input
void ATsunamiPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

