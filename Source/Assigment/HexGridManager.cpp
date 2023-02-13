// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"

#include "GameFramework/Character.h"
#include "Tiles/HexTile.h"

// Sets default values
AHexGridManager::AHexGridManager()
{
 	

}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();

	// initialize the grid
	HexGrid2D.SetNumZeroed(GridWidth);
	for(int32 i=0; i<HexGrid2D.Num();i++)
	{
		HexGrid2D[i].SetNumZeroed(GridHeight);
	}

	// populate the grid
	for(int32 y=0; y<GridHeight; y++)
	{
		for(int32 x=0; x<GridWidth; x++)
		{
			const bool isOddRow = y % 2 == 1;
			//check if odd row to add horizontal offset
			const float xPosition = isOddRow ? ((x * TileXOffset) + TileYOffset) : x*TileXOffset;
			const float yPostiion = y * TileOddOffset;

			TSubclassOf<AHexTile> ToSpawn = FloorHexTile;

			AHexTile* newTile = GetWorld()->
			SpawnActor<AHexTile>(ToSpawn, FVector(FIntPoint(xPosition, yPostiion)), 
				FRotator::ZeroRotator);

			newTile->TileIndex = FIntPoint(x, y);
			// adding label for debugging
			newTile->SetActorLabel(FString::Printf(TEXT("Tile_%d-%d"), x, y));

			HexGrid2D[x][y] = newTile;


		}
	}
	if(HexGrid2D.Num() > 0)
		SpawnPlayers();
}

void AHexGridManager::SpawnPlayers()
{
	//FMath::RandRange(int32 min, int32 max)
	TSubclassOf<ACharacter> One = PlayerOne;
	FVector oneLocation = 
		HexGrid2D[FMath::RandRange(0, GridWidth - 1)][FMath::RandRange(0, GridHeight - 1)]
	->GetActorLocation();
	oneLocation.Z = oneLocation.Z + 50.f;

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("Player one Location: X: %f, Y: %f,Z: %f"), oneLocation.X, oneLocation.Y, oneLocation.Z));*/

	GetWorld()->SpawnActor<ACharacter>(One, oneLocation, FRotator::ZeroRotator);


	TSubclassOf<ACharacter> Two = PlayerTwo;
	FVector twoLocation =
		HexGrid2D[FMath::RandRange(0, GridWidth - 1)][FMath::RandRange(0, GridHeight - 1)]
		->GetActorLocation();
	twoLocation.Z = twoLocation.Z + 50.f;

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald,
		FString::Printf(TEXT("Player two Location: X: %f, Y: %f,Z: %f"), twoLocation.X, twoLocation.Y, twoLocation.Z));*/

	GetWorld()->SpawnActor<ACharacter>(Two, twoLocation, FRotator::ZeroRotator);
}



