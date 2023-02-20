// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus:uint8
{
	EMS_Normal UMETA(DisplayName="Normal"),
	EMS_Sprint UMETA(DisplayName = "Sprinting"),
	EMS_Death UMETA(DisplayName = "Dead"),
	EMS_MAX UMETA(DisplayName = "DefualtMAX")
};


UENUM(BlueprintType)
enum class EStaminaStatus :uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "Below Minimum"),
	ESS_Exhusted UMETA(DisplayName = "Exhusted"),
	ESS_ExhustedRecovering UMETA(DisplayName = "Exhusted Recovering"),
	ESS_MAX UMETA(DisplayName = "Defualt MAX")
};

UCLASS()
class SUNTEMPLE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Save Data")  TSubclassOf<class AItemStorage> WeaponStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")bool bHasCombatTarget;
	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")class AMainPlayerController* MainPlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")class UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")class USoundCue* HitSound;

	TArray<FVector> PickupLocations;
	void ShowPickupLocations();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums") EMovementStatus MovementStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums") EStaminaStatus StaminaStatus;

	/** Set movement Status and Running Speed*/
	void SetMovementStatus(EMovementStatus Status);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running") float RunningSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running") float SprintinigSpeed;


	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")float StaminaDrainRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")float MinSprintStamina;

	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat") class AEnemy* CombatTarget;
	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }
	FRotator GetLookAtRotationYaw(FVector Target);
	bool bShiftKeyDown;
	bool bHasValidTarget;

	/** Press Down Shift to enable sprinting*/
	void ShiftKeyDown();
	/** Release Shift to stop spriting*/
	void ShiftKeyUp();

	/** Camera boom Positioning the Camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowedPrivateAcess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowedPrivateAcess = "true"))
	class UCameraComponent* FollowCamera;

	/* Base rates to turn scaling for the camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") float BaseLookUpRate;

	/**
	/*
	/* Player Stats
	/*
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats") float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats") float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats") float Stamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats") float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats") int32 Coins;


	void DecrementHealth(float amount);
	void Die();

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)void IncrementCoin(int32 Amount);
	UFUNCTION(BlueprintCallable)void IncrementHealth(float Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for Forward/backwars Input */
	void MoveForward(float Value);
	/** Called for Side to side Input */
	void MoveRight(float Value);

	bool bMovingForward;
	bool bMovingRight;
	/** Called Via input to turn at a given rate
	* @param rate This is the normalized rate, i.e 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float rate);
	/** Called Via input to look up/down at a given rate
	* @param rate This is the normalized rate, i.e 1.0 means 100% of desired up/down rate
	*/
	void LookUpAtRate(float rate);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item") class AWeapon* EquippedWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item") class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item)  { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anims") bool bAttacking;
	void Attack();
	UFUNCTION(BlueprintCallable) void AttackEnd();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")class UAnimMontage* CombatMontage;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable) void PlaySwingSound();
	UFUNCTION(BlueprintCallable) void DeathEnd();

	void UpdateCombatTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat") TSubclassOf<AEnemy> EnemyFilter;

	void SwitchLevel(FName LevelName);

	UFUNCTION(BlueprintCallable) void SaveGame();
	UFUNCTION(BlueprintCallable) void LoadGame(bool SetPosition);

};
