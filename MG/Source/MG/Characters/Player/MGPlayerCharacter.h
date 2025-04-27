// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MGBaseCharacter.h"
#include "InputActionValue.h"
#include "MGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MG_API AMGPlayerCharacter : public AMGBaseCharacter
{
	GENERATED_BODY()
	
public:
	AMGPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> FollowCam;
	
protected:
	void Look(const FInputActionValue& Value);
	void Movement(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	void AimCanceled(const FInputActionValue& Value);
	
protected:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> IMCDefault;

	// Input variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Section | InputAction")
	TObjectPtr<class UInputAction> IALook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Section | InputAction")
	TObjectPtr<class UInputAction> IAMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Section | InputAction")
	TObjectPtr<class UInputAction> IAFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Section | InputAction")
	TObjectPtr<class UInputAction> IAAim;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float AimTargetArmLength = 300.f;
	
// Test Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test Section");
	TSoftClassPtr<AActor> ProjectileClass;
};
