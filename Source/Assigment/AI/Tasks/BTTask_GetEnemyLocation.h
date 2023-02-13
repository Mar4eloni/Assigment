// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetEnemyLocation.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGMENT_API UBTTask_GetEnemyLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_GetEnemyLocation();

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
