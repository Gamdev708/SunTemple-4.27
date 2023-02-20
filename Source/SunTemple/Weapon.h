// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState:uint8
{
	EWS_Pickup UMETA(DisplayName="Pickup"),
	EWS_Equipped UMETA(DisplayName="Equipped"),
	EWS_DefaultMax UMETA(DisplayName="DefaultMax")
};

/**
 * 
 */
UCLASS()
class SUNTEMPLE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	AWeapon();

	UPROPERTY(EditDefaultsOnly, Category = "Save Data") FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item") EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Particle") bool bWeaponParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Sound")class USoundCue* OnEquipSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Sound") USoundCue* SwingSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh") class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Combat") class UBoxComponent* CombatCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Combat") float Damage;


	virtual	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION() void CombatOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void CombatOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Equip(class AMainCharacter* Char);

	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }

	UFUNCTION(BlueprintCallable) void ActivateCollision();
	UFUNCTION(BlueprintCallable) void DeactivateCollision();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Combat")TSubclassOf<UDamageType> DamageTypeClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Combat")AController* WeaponInstigator;
	FORCEINLINE void SetInstigator(AController* Inst) { WeaponInstigator = Inst; }

protected:
	virtual	void BeginPlay() override;
};
