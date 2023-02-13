// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridManager.generated.h"


class AHexTile;

UCLASS()
class ASSIGMENT_API AHexGridManager : public AActor
{
	GENERATED_BODY()


protected:

	TArray<TArray<AHexTile*>> HexGrid2D;

	UPROPERTY(EditAnywhere, Category = "HexGrid")
	int32 GridWidth;

	UPROPERTY(EditAnywhere, Category = "HexGrid")
	int32 GridHeight;

	UPROPERTY(EditAnywhere, Category = "HexGrid")
	float TileXOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid")
	float TileYOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid")
	float TileOddOffset;

	UPROPERTY(EditAnywhere, Category = "Tile")
	TSubclassOf<AHexTile> FloorHexTile;


	UPROPERTY(EditAnywhere, Category = "HexGrid|Player one")
	TSubclassOf<ACharacter> PlayerOne;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Player two")
	TSubclassOf<ACharacter> PlayerTwo;
	
public:	
	// Sets default values for this actor's properties
	AHexGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPlayers();

};
