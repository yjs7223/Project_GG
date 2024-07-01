// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	bbc = Blackboard;
	UseBlackboard(bbd, bbc);
	
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AEnemyController::RunBT()
{
	RunBehaviorTree(bt);
}

void AEnemyController::SetDestination(FVector p_vec)
{
	if (bbc)
	{
		bbc->SetValueAsVector("Destination", p_vec);
	}
}
