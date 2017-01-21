// Fill out your copyright notice in the Description page of Project Settings.

#include "jam2017.h"
#include "Tower.h"


// Sets default values
ATower::ATower()
{
	this->bBlockInput = false;
	this->AutoReceiveInput = EAutoReceiveInput::Player0;

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
	DecalComp->SetRelativeRotation(FRotator(-90, 0, 0));
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();	
	DecalComp->DecalSize = FVector(MaxRadius, MaxRadius, MaxRadius);
	DecalComp->SetHiddenInGame(true);
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
	DecalComp->SetHiddenInGame(true);
}

void ATower::OnCursorOver_Implementation(UPrimitiveComponent * Component)
{
	DecalComp->SetHiddenInGame(false);
}

void ATower::EndCursorOver_Implementation(UPrimitiveComponent * Component)
{
	if(!Dragged)
	DecalComp->SetHiddenInGame(true);
}
