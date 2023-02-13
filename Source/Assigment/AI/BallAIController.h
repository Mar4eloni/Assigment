// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BallAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;

UCLASS()
class ASSIGMENT_API ABallAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABallAIController();

	void SetEnemy(APawn* pawn);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="AI")
	float AISightRadius = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float AILoseSightRadius = AISightRadius + 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float AIFieldOfView = 70.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnSenseUpdated(const TArray<AActor*>& DetectedActors);

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	//virtual FRotator GetControlRotation() const override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	FName EnemyKey;

	

};
