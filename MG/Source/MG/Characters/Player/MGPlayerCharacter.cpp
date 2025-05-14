// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MGPlayerCharacter.h"
#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

#include "FrameTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMGPlayerCharacter::AMGPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArmComponent)
	{
		 SpringArmComponent->SetupAttachment(RootComponent);
	}
	
	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	if (FollowCam)
	{
		FollowCam->SetupAttachment(SpringArmComponent);
	}

	FollowCam->bUsePawnControlRotation = true;
	
	ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCDefaultRef(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	
	if (IMCDefaultRef.Succeeded())
	{
		IMCDefault = IMCDefaultRef.Object;
	}
}

void AMGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMCDefault, 0);
		}
	}
}

void AMGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentTargetLength = SpringArmComponent->TargetArmLength;
	float NewTargetLength = FMath::FInterpTo(CurrentTargetLength, AimTargetArmLength, DeltaTime, 25.f);
	SpringArmComponent->TargetArmLength = NewTargetLength;
}

void AMGPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &AMGPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(IAMovement, ETriggerEvent::Triggered, this, &AMGPlayerCharacter::Movement);
		EnhancedInputComponent->BindAction(IAFire, ETriggerEvent::Triggered, this, &AMGPlayerCharacter::Fire);
		EnhancedInputComponent->BindAction(IAAim, ETriggerEvent::Triggered, this, &AMGPlayerCharacter::Aim);
		EnhancedInputComponent->BindAction(IAAim, ETriggerEvent::Completed, this, &AMGPlayerCharacter::AimCanceled);
	}
}

void AMGPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AMGPlayerCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AMGPlayerCharacter::Fire(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Log, TEXT("Fire!"));

	UClass* LoadClass = ProjectileClass.LoadSynchronous();

	// FVector spawnLoaction = FollowCam->GetComponentLocation();
	FVector spawnLoaction = GetMesh()->GetSocketLocation("Muzzle_01");
	// FRotator spawnRotation = FollowCam->GetComponentRotation();
	FRotator spawnRotation = GetMesh()->GetSocketRotation("Muzzle_01");
	
	GetWorld()->SpawnActor<AActor>(LoadClass, spawnLoaction, spawnRotation);
}
	
void AMGPlayerCharacter::Aim(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = true;
	AimTargetArmLength = 85.0f;
}

void AMGPlayerCharacter::AimCanceled(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = false;
	AimTargetArmLength = 300.0f;
}

