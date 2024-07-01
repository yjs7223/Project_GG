// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class ENEMYMODULE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	class UEnemyGroupSystemComponent* groupSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySetting")
		bool bEnable;

	// AI Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySetting")
		float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySetting")
		float curSpeed;	// 현재 속도

	float slow;	// 속도 감소량

	class AEnemyController* controller;

	class AEnemySpawner* mySpawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HpUpdate();
	void MovementUpdate();
	void Init();
};
