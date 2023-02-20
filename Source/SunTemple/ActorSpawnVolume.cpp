// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Critter.h"

// Sets default values
AActorSpawnVolume::AActorSpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawning Box"));}

// Called when the game starts or when spawned
void AActorSpawnVolume::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AActorSpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AActorSpawnVolume::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	FVector Origin = SpawningBox->GetComponentLocation();

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

void AActorSpawnVolume::SpawnOurPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParameters;
		if (World)
		{
			ACritter* CritterSpawned =World->SpawnActor<ACritter>(ToSpawn, Location, FRotator(0.f), SpawnParameters);
		}
	}
}

