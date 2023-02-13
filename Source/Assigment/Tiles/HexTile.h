// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexTile.generated.h"


UENUM()
enum class EHexTileType:uint8
{
	INVALID,
	FLOOR,
	WALL
};

UCLASS()
class ASSIGMENT_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	EHexTileType TileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	class UStaticMeshComponent* TileMesh;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
	FIntPoint TileIndex;

};
