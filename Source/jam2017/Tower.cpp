// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "Tower.h"
#include "jam2017PlayerController.h"


// Sets default values
ATower::ATower() : Super()
{
	this->bBlockInput = false;
	this->AutoReceiveInput = EAutoReceiveInput::Player0;
	CanAlert = false;
	CanGuide = false;
	IsActive = false;
	IsForcedActive = false;

	FCollisionResponseContainer channels;
	channels.EngineTraceChannel1 = 1;
	channels.Visibility = 0;
	channels.WorldDynamic = 1;
	channels.WorldStatic = 1;
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
	DecalComp = CreateDefaultSubobject<UDecalComponent>("DecalComp");
	CollisionComp->OnBeginCursorOver.AddDynamic(this, &ATower::OnCursorOver);
	CollisionComp->OnEndCursorOver.AddDynamic(this, &ATower::EndCursorOver);
	CollisionComp->SetCollisionResponseToChannels(channels);
	RootComponent = CollisionComp;
	DecalComp->SetupAttachment(RootComponent);
	DecalComp->DecalSize = FVector(1, 1, 1);
	DecalComp->SetRelativeRotation(FRotator(-90, 0, 0));
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();	
	DecalComp->SetRelativeScale3D(FVector(MaxRadius, MaxRadius, MaxRadius));
	DecalComp->SetHiddenInGame(true);
	if (IsForcedActive)
		IsActive = true;
}

// Called every frame
void ATower::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (Dragged && Ctrl)
	{
		FHitResult result;
		Ctrl->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
		if (ATower* tower = Cast<ATower>(result.Actor.Get()))
		{

		}
		else
		SetActorLocation(result.ImpactPoint);
	}
	else if(!IsForcedActive)
	{
		Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
		IsActive = false;
		for (ATower * tower : pc->SpawnedTowers)
		{
			if (tower == this)
				continue;
			auto position = tower->GetActorLocation();
			auto myPosition = GetActorLocation();

			if ((myPosition - position).Size2D() < tower->MaxRadius + MaxRadius)
			{
				if (tower->CanGuide && tower->GetIsActive())
					IsActive = true;
			}
		}
	}
}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(class UInputComponent* _InputComponent)
{
	Super::SetupPlayerInputComponent(_InputComponent);
}

void ATower::Grab(APlayerController * ctrl)
{
	Dragged = true;
	Ctrl = ctrl;
}

void ATower::Drop()
{
	Dragged = false;
}

bool ATower::GetIsActive()
{
	return (IsActive || IsForcedActive) && !Dragged;
}

void ATower::OnCursorOver_Implementation(UPrimitiveComponent * Component)
{
	DecalComp->SetHiddenInGame(false);
}

void ATower::EndCursorOver_Implementation(UPrimitiveComponent * Component)
{
	if(!Dragged && !GetIsActive())
	DecalComp->SetHiddenInGame(true);
}
