// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class JAM2017_API ACameraPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MovementComp")
	UFloatingPawnMovement * MovementComp;
	
	
};
