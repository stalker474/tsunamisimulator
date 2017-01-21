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
	for (ASafeZonePawn * pawn : pc->SpawnedSafeZones)
	{
		auto location = pawn->GetActorLocation();
		auto myLocation = GetPawn()->GetActorLocation();

	}

}


