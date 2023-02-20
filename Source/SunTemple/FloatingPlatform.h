// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class SUNTEMPLE_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	/** Mesh for the Platform*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Floating Platform") class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere) FVector StartPosition;
	UPROPERTY(EditAnywhere,meta=(MakeEditWidget="true")) FVector EndPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floating Platform") float InterpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floating Platform") float InterpTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floating Platform") float Distance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floating Platform") bool bInterping;
	FTimerHandle InterpTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleInterping();
	void SawpVectors(FVector& Vec1, FVector& Vec2);
};
