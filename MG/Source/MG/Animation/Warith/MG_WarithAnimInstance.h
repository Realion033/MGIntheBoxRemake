// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MG_WarithAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MG_API UMG_WarithAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Warith Animation")
	TObjectPtr<class AMGBaseCharacter> Owner;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Warith Animation")
	TObjectPtr<class UCharacterMovementComponent> MovementCompo;

protected:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Warith Animation")
	float MovementSpeed;
};
