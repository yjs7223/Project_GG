// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGroupSystemComponent.h"
#include "Enemy.h"
#include "EnemyController.h"

// Sets default values for this component's properties
UEnemyGroupSystemComponent::UEnemyGroupSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bLeader = false;
	// ...
}


// Called when the game starts
void UEnemyGroupSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner<AEnemy>();
	// ...
	
}


// Called every frame
void UEnemyGroupSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	timer += DeltaTime;
	if (timer >= 1 && leaderEnemy == nullptr)
	{
		FindLeader();
	}

	if (leaderEnemy)
	{
		SetPosition();
	}
	// ...
}

void UEnemyGroupSystemComponent::FindLeader()
{
	if (!bLeader)
	{
		for (auto& e : group)
		{
			if (e->groupSystem->bLeader)
			{
				leaderEnemy = e;
			}
		}
	}
}

void UEnemyGroupSystemComponent::SetPosition()
{
	destination = leaderEnemy->GetActorLocation() + settingPos;
	owner->controller->SetDestination(destination);
}

