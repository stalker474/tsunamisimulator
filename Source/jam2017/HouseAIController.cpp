// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "HouseAIController.h"
#include "HawaianCharacter.h"
#include "House.h"
#include "jam2017PlayerController.h"

AHouseAIController::AHouseAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NextSpawn = 0.0f;
	SpawnSpeed = 1.0f;
}

void AHouseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NextSpawn -= DeltaTime;
	if (NextSpawn <= 0.0f)
	{
		Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
		bool canSpawn = false;
		for (ATower * tower : pc->SpawnedTowers)
		{
			if (!tower->CanAlert || !tower->GetIsActive())
				continue;
			AHouse * house = Cast<AHouse>(GetPawn());
			auto position = tower->GetActorLocation();
			auto myPosition = GetPawn()->GetActorLocation();

			if ((myPosition - position).Size2D() < tower->MaxRadius)
			{
				house->IsAlerted = true;
				if (house->Population > 0)
				{
					house->Population--;
					pc->TotalPopulationTrapped--;
					Spawn();
					NextSpawn = SpawnSpeed;
				}
			}
		}
	}
}

void AHouseAIController::Possess(APawn * PossessedPawn)
{
	Super::Possess(PossessedPawn);
	AHouse * house = Cast<AHouse>(PossessedPawn);
	CharacterClass = house->CharacterClass;
}

void AHouseAIController::Spawn()
{
	if (CharacterClass)
	{
		FActorSpawnParameters params;
		params.Owner = GetPawn();
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AHawaianCharacter * haw = GetWorld()->SpawnActor<AHawaianCharacter>(CharacterClass, params.Owner->GetActorLocation() + FVector(0.0f,-70,20.0f), FRotator(0, 0, 0), params);
	}
}
