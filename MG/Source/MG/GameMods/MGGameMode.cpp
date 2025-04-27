// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMods/MGGameMode.h"
#include "Player/MGPlayerController.h"
#include "Characters/Player/MGPlayerCharacter.h"

AMGGameMode::AMGGameMode()
{
	ConstructorHelpers::FClassFinder<AMGPlayerController>
		PlayerControllerClassRef(TEXT("/Game/BluePrints/Player/BP_MainPlayerController.BP_MainPlayerController_C"));
	ConstructorHelpers::FClassFinder<AMGPlayerCharacter>
		PlayerCharacterClassRef(TEXT("/Game/BluePrints/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	PlayerControllerClass = PlayerControllerClassRef.Class;
	DefaultPawnClass = PlayerCharacterClassRef.Class;
}
