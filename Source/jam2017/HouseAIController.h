// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HawaianCharacter.h"
#include "AIController.h"
#include "HouseAIController.generated.h"

/**
 * 
 */
UCLASS()
class JAM2017_API AHouseAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn * PossessedPawn) override;
	
	UPROPERTY(EditDefaultsOnly)
	float SpawnSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHawaianCharacter> CharacterClass;

	void Spawn();
	
private:
	float NextSpawn;
	
};
