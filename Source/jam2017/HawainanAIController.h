// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "HawainanAIController.generated.h"

/**
 * 
 */
UCLASS()
class JAM2017_API AHawainanAIController : public AAIController
{
	GENERATED_UCLASS_BODY()
	
public:
	void Tick(float DeltaTime);
	bool KnowsDirection;
	float DirectionChange;
};
