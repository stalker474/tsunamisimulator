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
	CanCan = false;
	CanMove = true;
	BuildTimeLeft = 0.0f;

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

	AudioComp = CreateDefaultSubobject<UAudioComponent>("Audio comp");
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();	
	PulsateRadius = MaxRadius;
	DecalComp->SetHiddenInGame(false);
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	pc->Resources -= Cost;
	pc->SpawnedTowers.Add(this);

	BuildTimeLeft = BuildTime;
}

bool ATower::CanCan = false;

// Called every frame
void ATower::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetIsActive())
	{
		PulsateRadius += DeltaTime * 700.0f;
		if (PulsateRadius > MaxRadius + 800.0f)
		{
			PulsateRadius = 0.0f;
		}
	}
	else
		PulsateRadius = MaxRadius;
	float tempRadius = FMath::Min(PulsateRadius, MaxRadius);
	DecalComp->SetRelativeScale3D(FVector(tempRadius, tempRadius, tempRadius));
	
	if (Dragged && Ctrl)
	{
		BuildTimeLeft = BuildTime;
		FHitResult result;
		Ctrl->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
		if (ATower* tower = Cast<ATower>(result.Actor.Get()))
		{

		}
		else
		SetActorLocation(result.ImpactPoint);
	}
	else if(CanMove)
	{
		if (BuildTimeLeft > 0)
		{
			BuildTimeLeft -= DeltaTime;
			return;
		}

		Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
		bool deactivated = IsActive;
		IsActive = IsForcedActive;
		bool contactWithGuide = false;
		bool contactWithAlert = false;
		
		for (ATower * tower : pc->SpawnedTowers)
		{
			if (tower == this)
				continue;
			auto position = tower->GetActorLocation();
			auto myPosition = GetActorLocation();

			if ((myPosition - position).Size2D() < tower->MaxRadius + MaxRadius)
			{
				if (tower->GetIsActive())
				{
					IsActive = true;
					DecalComp->SetHiddenInGame(false);
					deactivated = false;
					CanGuide = tower->CanGuide;
					CanAlert = tower->CanAlert;
					if (CanGuide)
					{
						contactWithGuide = true;
					}
						
					if (CanAlert)
					{
						contactWithAlert = true;
					}	

					if (contactWithAlert && contactWithGuide)
					{
						IsActive = false;
						deactivated = true;
						break;
					}
				}
			}
		}
	}

	if (GetIsActive() || Dragged)
		DecalComp->SetHiddenInGame(false);
	else
		DecalComp->SetHiddenInGame(true);
}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(class UInputComponent* _InputComponent)
{
	Super::SetupPlayerInputComponent(_InputComponent);
}

void ATower::Grab(APlayerController * ctrl)
{
	if (PickSound && !Dragged)
	{
		AudioComp->SetSound(PickSound);
		AudioComp->Play();
	}

	if (CanMove)
		Dragged = true;
	else
	{
		IsActive = true;
		Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
		for (ATower * tower : pc->SpawnedTowers)
			if (tower != this && !tower->CanMove)
			{
				tower->SetActorHiddenInGame(true);
			}
	}
		
	Ctrl = ctrl;
}

void ATower::Drop()
{
	if (DropSound)
	{
		AudioComp->SetSound(DropSound);
		AudioComp->Play();
	}
	Dragged = false;
}

void ATower::Remove()
{
	Ajam2017PlayerController * pc = Cast<Ajam2017PlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	pc->SpawnedTowers.Remove(this);
	pc->Resources += Cost;
	pc->DestroyedTowers++;
	this->Destroy();
}

bool ATower::GetIsActive()
{
	return IsActive && !Dragged && (BuildTimeLeft <= 0);
}

void ATower::OnCursorOver_Implementation(UPrimitiveComponent * Component)
{
	DecalComp->SetHiddenInGame(false);
	if (HoverSound && !PlayedOnce && !Dragged)
	{
		PlayedOnce = true;
		AudioComp->SetSound(HoverSound);
		AudioComp->Play();
	}
}

void ATower::EndCursorOver_Implementation(UPrimitiveComponent * Component)
{
	if(!GetIsActive())
	DecalComp->SetHiddenInGame(true);

	PlayedOnce = false;
}
