// Copyright Ivan Tsarkov Rockdevels

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "CharacterTypes.h"
#include "NinjaCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class NINJA_API ANinjaCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	ANinjaCharacter();

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	AWeapon* EquippedWeapon;

	//animation montages
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* EquipMontage;
	
public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE AItem* GetOverlappingItem() const { return OverlappingItem; }

	UPROPERTY(BlueprintReadWrite, Category="Movement")
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	void EquipCurrentWeapon();

	void Attack();

protected:
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	bool CanAttack();

	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
};
