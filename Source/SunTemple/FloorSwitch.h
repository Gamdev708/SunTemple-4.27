// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class SUNTEMPLE_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/** Overlap Volume for functionality to be triggered*/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Floor Switch") class UBoxComponent* TriggerBox;
	/** Switch for the character to be step on*/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Floor Switch") class UStaticMeshComponent* FloorSwtich;
	/** Door to move when the floor switch is sepped on*/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Floor Switch") class UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch") FVector InitialDoorLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch") FVector InitialSwitchocation;

	FTimerHandle SwitchHandle;
	UPROPERTY(EditAnywhere, Category = "Floor Switch") float SwitchTime;
	bool bCharacterOnSwitch;
	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") void RaiseDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") void LowerDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") void RaiseFloorSwitch();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") void LowerFloorSwitch();
	UFUNCTION(BlueprintCallable, Category = "Floor Switch") void UpdateDoorLocation(float Z);
	UFUNCTION(BlueprintCallable, Category = "Floor Switch") void UpdateFloorSwitchLocation(float Z);

};
