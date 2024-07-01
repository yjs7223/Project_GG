// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyGroupSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENEMYMODULE_API UEnemyGroupSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyGroupSystemComponent();

	float timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLeader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AEnemy* owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AEnemy* leaderEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AEnemy*> group;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector destination;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector settingPos;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindLeader();

	void SetPosition();
};
