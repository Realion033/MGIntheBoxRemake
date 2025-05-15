// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGTileManager.generated.h"

USTRUCT()
struct FTileRow
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<AActor*> Row;
};

UCLASS()
class MG_API AMGTileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMGTileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();
	
private:
	static const int32 MaxRows = 10;
	static const int32 MaxCols = 10;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TileActorClass;
	UPROPERTY(EditAnywhere)
	TArray<FTileRow> Tiles;
};