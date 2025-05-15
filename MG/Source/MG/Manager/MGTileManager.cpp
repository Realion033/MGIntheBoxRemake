// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/MGTileManager.h"

// Sets default values
AMGTileManager::AMGTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMGTileManager::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Display, TEXT("[AMG Manager] : Begin play"));
	Init();
}

void AMGTileManager::Init()
{
	for (int32 i = 0; i < MaxRows; i++)
	{
		for (int32 j = 0; j < MaxCols; j++)
		{
			
		}
	}
}


// Called every frame
void AMGTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
