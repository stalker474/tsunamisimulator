// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "HawainanAIController.h"
#include "jam2017PlayerController.h"

AHawainanAIController::AHawainanAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}


void AHawainanAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	float minDist = 9999999.0f;
	FVector Destination = GetPawn()->GetActorLocation();
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
	auto res = MoveToLocation(Destination, -1.0f, true);
	int k = 6;

}


