// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

UCLASS()
class JAM2017_API ATower : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Grab(APlayerController * ctrl);

	UFUNCTION()
	void Drop();

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnCursorOver(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void EndCursorOver(UPrimitiveComponent* Component);

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	float MaxRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Cost;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	bool CanAlert;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	bool CanGuide;

	UFUNCTION()
	bool GetIsActive();

	UPROPERTY(EditAnywhere, Category = "Active")
	bool IsActive;

	UPROPERTY(EditAnywhere, Category = "Active")
	bool IsForcedActive;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float BuildTime;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* ConstructionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* PickSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* DropSound;

	UPROPERTY(EditDefaultsOnly, Category = "Collisions")
	UBoxComponent * CollisionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Zone")
	UDecalComponent * DecalComp;

	static bool CanCan;

private:
	bool Dragged;
	float PulsateRadius;

	APlayerController * Ctrl;

	
	
};
