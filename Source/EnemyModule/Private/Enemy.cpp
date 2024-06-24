// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyGroupSystemComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<AEnemyController>(GetController());
	egsc = FindComponentByClass<UEnemyGroupSystemComponent>();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::HpUpdate()
{
	if (controller != nullptr)
	{
		//controller->bbc->SetValueAsFloat("HealthPoint", stat->hp);
	}
}

void AEnemy::MovementUpdate()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed - slow;

	// Ç¥½Ã¿ë
	curSpeed = GetCharacterMovement()->MaxWalkSpeed;
}