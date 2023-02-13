// Fill out your copyright notice in the Description page of Project Settings.


#include "BallAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BallAICharacter.h"


ABallAIController::ABallAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ABallAIController::OnSenseUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	/* Initialize blackboard keys */
	EnemyKey = "Target";
}

void ABallAIController::SetEnemy(APawn* pawn)
{
	if(IsValid(BlackboardComponent))
	{
		BlackboardComponent->SetValueAsObject(EnemyKey, pawn);
	}
}


void ABallAIController::OnSenseUpdated(const TArray<AActor*>& DetectedActors)
{
	if(DetectedActors.Num() > 0)
	{
		for(int i = 0; i < DetectedActors.Num(); i++)
		{
			ABallAICharacter* enemy = Cast<ABallAICharacter>(DetectedActors[i]);
			if(enemy)
			{
				SetEnemy(enemy);
			}
			
		}
	}
}

void ABallAIController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
	
}

void ABallAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}
