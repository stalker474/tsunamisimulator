// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Tower.h"
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

	UPROPERTY(BlueprintReadOnly)
	int TotalPopulation;

	UFUNCTION(BlueprintCallable, Category="Spawning")
	void AddTower(TSubclassOf<ATower> TowerClass);

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
	void LeftRelease();
};


