// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "jam2017.h"
#include "jam2017PlayerController.h"
#include "CameraPawn.h"

Ajam2017PlayerController::Ajam2017PlayerController()
{
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
	bEnableTouchOverEvents = false;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	bBlockInput = false;
	SelectedTower = nullptr;
	TotalPopulationTrapped = 0;
	TotalPopulationLeft = 0;
	MaxPopulation = 0;
	MaxResources = 100;
	Resources = 100;
	TimeBeforeCatastrophy = 120.0f;
	DestroyedTowers = 0;
}

void Ajam2017PlayerController::Start()
{
	Started = true;
}

void Ajam2017PlayerController::AddTower(TSubclassOf<ATower> TowerClass)
{
	if (Resources - TowerClass.GetDefaultObject()->Cost <= 0)
		return;
	FActorSpawnParameters params;
	params.Owner = this;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SelectedTower = GetWorld()->SpawnActor<ATower>(TowerClass,params);
	SelectedTower->Grab(this);
}

void Ajam2017PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if(Started)
		TimeBeforeCatastrophy -= DeltaTime;
}

void Ajam2017PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAxis("ScrollNorthSouth", this, &Ajam2017PlayerController::ScrollNorthSouth);
	InputComponent->BindAxis("ScrollEastWest", this, &Ajam2017PlayerController::ScrollEastWest);
	InputComponent->BindAxis("MouseMoveX", this, &Ajam2017PlayerController::MouseMoveX);
	InputComponent->BindAxis("MouseMoveY", this, &Ajam2017PlayerController::MouseMoveY);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &Ajam2017PlayerController::LeftPress);
	InputComponent->BindAction("LeftClick", IE_Released, this, &Ajam2017PlayerController::LeftRelease);
	InputComponent->BindAction("RightClick", IE_Released, this, &Ajam2017PlayerController::RightPress);
}

void Ajam2017PlayerController::MouseMoveX(float value)
{
	if(!SelectedTower)
	ScrollEastWest(value);
}

void Ajam2017PlayerController::MouseMoveY(float value)
{
	if (!SelectedTower)
	ScrollNorthSouth(value);
}

void Ajam2017PlayerController::ScrollNorthSouth(float value)
{
	ACameraPawn * player = Cast<ACameraPawn>(GetPawn());
	auto movementComp = player->GetMovementComponent();
	movementComp->AddInputVector(FVector(value, 0, 0),true);
}

void Ajam2017PlayerController::ScrollEastWest(float value)
{
	ACameraPawn * player = Cast<ACameraPawn>(GetPawn());
	auto movementComp = player->GetMovementComponent();
	movementComp->AddInputVector(FVector(0, value, 0), true);
}

void Ajam2017PlayerController::LeftPress()
{
	FHitResult result;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, result);

	if (result.Actor.IsValid())
	{
		ATower * tower = Cast<ATower>(result.Actor.Get());
		if (tower)
		{
			SelectedTower = tower;
			tower->Grab(this);
		}	
	}	
}

void Ajam2017PlayerController::RightPress()
{
	FHitResult result;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, result);

	if (result.Actor.IsValid())
	{
		ATower * tower = Cast<ATower>(result.Actor.Get());
		if (tower)
			tower->Remove();
	}
}

void Ajam2017PlayerController::LeftRelease()
{
	if (SelectedTower)
	{
		SelectedTower->Drop();
		SelectedTower = nullptr;
	}
}
