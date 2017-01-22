// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "HawainanAIController.h"
#include "jam2017PlayerController.h"

AHawainanAIController::AHawainanAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	KnowsDirection = false;
	DirectionChange = 0.0f;
}


void AHawainanAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	bool canSpawn = false;
	if(!KnowsDirection)
		for (ATower * tower : pc->SpawnedTowers)
		{
			if (!tower->CanGuide || !tower->GetIsActive())
				continue;
		
			auto position = tower->GetActorLocation();
			auto myPosition = GetPawn()->GetActorLocation();

			if ((myPosition - position).Size2D() < tower->MaxRadius)
				KnowsDirection = true;
		}

	float minDist = 9999999.0f;
	float random = (FMath::FRand() - 0.5f) * 80.0f;
	FVector Destination = GetPawn()->GetActorLocation() + FVector(random, random, 0);

	if(KnowsDirection)
	for (ASafeZonePawn * pawn : pc->SpawnedSafeZones)
	{
		auto plop = GetPawn()->GetMovementComponent();
		auto location = pawn->GetActorLocation();
		auto myLocation = GetPawn()->GetActorLocation();

		if ((myLocation - location).Size2D() < minDist)
		{
			minDist = (myLocation - location).Size2D();
			Destination = location;
		}

	}
	if (DirectionChange <= 0.0f)
	{
		auto res = MoveToLocation(Destination, -1.0f, true);
		DirectionChange = 0.5f;
	}
	else
		DirectionChange -= DeltaTime;
	
}


