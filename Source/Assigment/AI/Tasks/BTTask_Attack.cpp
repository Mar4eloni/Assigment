// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "AIController.h"
#include "Assigment/AI/BallAICharacter.h"



UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack !");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController{ OwnerComp.GetAIOwner() };
	const APawn* AIPawn{ AIController->GetPawn() };

	ABallAICharacter* Enemy = Cast<ABallAICharacter>(AIController->GetCharacter());

	//Cast<ABallCharacter>()AIController->GetCharacter()

	if (AIPawn && AIController && Enemy)
	{
		Enemy->Attack();
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
