// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	RootComponent = Mesh;
	
	StartPosition = FVector(0.f);
	EndPosition = FVector(0.f);
	InterpSpeed = 4.f;
	InterpTime = 1.f;
	bInterping = false;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	EndPosition += StartPosition;
	bInterping = false;

	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);

	Distance = (EndPosition - StartPosition).Size();
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterping)
	{
		FVector CurrrentLocation = GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrrentLocation, EndPosition, DeltaTime, InterpSpeed);
		SetActorLocation(Interp);

		float DistanceTravelled = (GetActorLocation() - StartPosition).Size();
		if (Distance-DistanceTravelled <= 1.f)
		{
			ToggleInterping();
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
			SawpVectors(StartPosition, EndPosition);
		}
	}
	
}

void AFloatingPlatform::ToggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingPlatform::SawpVectors(FVector& Vec1, FVector& Vec2)
{
	FVector Temp = Vec1;
	Vec1 = Vec2;
	Vec2 = Temp;
}

