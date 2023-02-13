// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBTTask_FindRandomLocation.h"

#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBallBTTask_FindRandomLocation::UBallBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	// filters only vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(
		UBallBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBallBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	// get ai pawn
	AAIController* AIClontroller{ OwnerComp.GetAIOwner() };
	const APawn* AIPawn{ AIClontroller->GetPawn() };
	// get pawn origin
	const FVector Origin{ AIPawn->GetActorLocation() };

	// get nav system and find random location
	const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };

	//const UNavigationSystemBase* NavSystem {UNavigationSystemBase::GetCurrent}
	if(IsValid(NavSystem)&& NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIClontroller->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// signal for succesfull execute
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UBallBTTask_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
