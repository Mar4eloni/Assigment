// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetEnemyLocation.h"
#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


UBTTask_GetEnemyLocation::UBTTask_GetEnemyLocation()
{
	NodeName = TEXT("Find Enemy Location");
}

EBTNodeResult::Type UBTTask_GetEnemyLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController{ OwnerComp.GetAIOwner() };
	const APawn* AIPawn{ AIController->GetPawn() };
	FNavLocation Location{};

	

	if (AIPawn && AIController)
	{

		ACharacter* Enemy{Cast<ACharacter>(
			AIController->GetBlackboardComponent()->
			GetValueAsObject(BlackboardKey.SelectedKeyName))};

		Location.Location = Enemy->GetActorLocation();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald,
		FString::Printf(TEXT("Player two Location: X: %f, Y: %f,Z: %f"), Location.Location.X, Location.Location.Y, Location.Location.Z));


		AIController->GetBlackboardComponent()->SetValueAsVector("EnemyLocation", Location.Location);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
