// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Tower.h"
#include "SafeZonePawn.h"
#include "GameFramework/PlayerController.h"
#include "jam2017PlayerController.generated.h"

UCLASS()
class Ajam2017PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	Ajam2017PlayerController();

	UPROPERTY()
	ATower * SelectedTower;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TimeBeforeCatastrophy;

	UPROPERTY(BlueprintReadOnly)
	bool Catastrophy;

	UPROPERTY(BlueprintReadOnly)
		int DestroyedTowers;

	UPROPERTY(BlueprintReadOnly)
	int TotalPopulationTrapped;

	UPROPERTY(BlueprintReadOnly)
	int TotalPopulationLeft;

	UPROPERTY(BlueprintReadOnly)
	int MaxPopulation;

	UPROPERTY(BlueprintReadOnly)
	int MaxResources;

	UPROPERTY(BlueprintReadOnly)
	int Resources;

	UFUNCTION(BlueprintCallable, Category = "Start")
	void Start();

	UFUNCTION(BlueprintCallable, Category="Spawning")
	void AddTower(TSubclassOf<ATower> TowerClass);

	UPROPERTY(BlueprintReadOnly)
	TArray<ATower*> SpawnedTowers;

	UPROPERTY()
	TArray<ASafeZonePawn*> SpawnedSafeZones;

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface


	void MouseMoveX(float value);
	void MouseMoveY(float value);
	void ScrollNorthSouth(float value);
	void ScrollEastWest(float value);
	void LeftPress();
	void RightPress();
	void LeftRelease();

	bool Started;

};


