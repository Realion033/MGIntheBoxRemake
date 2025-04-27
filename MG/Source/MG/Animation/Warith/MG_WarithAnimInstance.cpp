// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Warith/MG_WarithAnimInstance.h"
#include "Characters/MGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMG_WarithAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AMGBaseCharacter>(GetOwningActor());
	if (Owner)
	{
		MovementCompo = Owner->GetCharacterMovement();
	}
}

void UMG_WarithAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementCompo)
	{
		FVector Velo = MovementCompo->Velocity;
		MovementSpeed = Velo.Size2D();
	}
}
