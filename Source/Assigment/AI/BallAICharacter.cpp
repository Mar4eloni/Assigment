// Fill out your copyright notice in the Description page of Project Settings.


#include "BallAICharacter.h"

#include "BallAIController.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ABallAICharacter::ABallAICharacter()
{

}

// Called when the game starts or when spawned
void ABallAICharacter::BeginPlay()
{
	Super::BeginPlay();

}


// Called to bind functionality to input
void ABallAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABallAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0)
		return 0.f;

	float DamageCaused = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageCaused = FMath::Min(Health, DamageCaused);
	Health -= DamageCaused;

	if(Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("character died ...."));
		//DisableInput(this->GetController());
		GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Destroy();
	}


	return DamageCaused;
}

void ABallAICharacter::Attack()
{
	FHitResult HitResult;
	FVector Start = GetMesh()->GetBoneLocation("Head");
	FVector End = Start + GetMesh()->GetForwardVector() * 100;

	FCollisionQueryParams CollQuerryParams;
	CollQuerryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel
	(HitResult,Start,End,ECollisionChannel::ECC_Pawn,CollQuerryParams);

	if(bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage Dealt !"));
		FPointDamageEvent DamageEvent(30.f, HitResult, GetMesh()->GetForwardVector(), nullptr);
		HitResult.GetActor()->TakeDamage(30.f,DamageEvent,GetInstigatorController(),this);
	}
}
