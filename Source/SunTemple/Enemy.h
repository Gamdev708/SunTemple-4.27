// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus :uint8
{
	EMS_Idle UMETA(DisplayName="Idle"),
	EMS_MoveToAttack UMETA(DisplayName = "Move to Attack"),
	EMS_Attacking UMETA(DisplayName = "Attacking"),
	EMS_Death UMETA(DisplayName = "Dead"),
	EMS_MAX UMETA(DisplayName = "Max"),
};

UCLASS()
class SUNTEMPLE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement") EEnemyMovementStatus EnemyMovementStatus;
	FORCEINLINE void SetEnemyMovementStatus(EEnemyMovementStatus Status) { EnemyMovementStatus = Status; }
	FORCEINLINE EEnemyMovementStatus GetEnemyMovementStatus() { return EnemyMovementStatus; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") class USphereComponent* AgroSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") USphereComponent* CombatSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") class AAIController* AIController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")class UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")class USoundCue* HitSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") USoundCue* SwingSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat") class UBoxComponent* CombatCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat") class UAnimMontage* CombatMontage;
	FTimerHandle AttackTimer;
	FTimerHandle DeathTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")float AttackminTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")float AttackmaxTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")float DeathDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")TSubclassOf<UDamageType> DamageTypeClass;

	bool bHasValidTarget;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION() virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION() void CombatOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void CombatOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable) void MoveToTarget(class AMainCharacter* Target);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") bool bOverlappingCombatSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")AMainCharacter* CombatTarget;
	UFUNCTION(BlueprintCallable) void ActivateCollision();
	UFUNCTION(BlueprintCallable) void DeactivateCollision();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat") bool bAttacking;
	void Attack();
	UFUNCTION(BlueprintCallable) void AttackEnd();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void Die(AActor* Causer);
	bool Alive();
	void Dissappear();
	UFUNCTION(BlueprintCallable) void DeathEnd();
};
