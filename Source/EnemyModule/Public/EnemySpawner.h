// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_Spawn.h"
#include "EnemySpawner.generated.h"

UCLASS()
class ENEMYMODULE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// ���� ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int curWave;

	// ���� ���� ������ ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* spawnData;
	// ���� ������ ���̺�
	struct FST_Spawner* curSpawnData;

	// ������ Ȱ��ȭ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		bool bSpawnerOn;

	// �÷��̾ ����� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		int playerKill;

	// ���̺� ���� �� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawnSeconds;

	// �����̿�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawn_Timer;

	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemyRifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemySniper;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemyHeavy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		class UBehaviorTree* enemyBT;

	class UEnemyController* controller;

	// Enemy ���� �� ���� ��ġ
	AActor* loadPos;

	// �̹� ���̺� ��ȯ ����
	bool spawnCheck;

	// �̹� ���̺꿡 ��ȯ �� ��
	TArray<int> enemyCount;

	// ������ ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> spawnSpots;
	
	// �÷��̾�
	ACharacter* player;

	// ������ ���̺� ����
	float spawn_Condition;
	float spawn_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawn_Spot;
	enum SpawnType spawn_Type;
	TMap<EnemyName, int> spawn_Wave;

	bool waveEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���̺� ����
	void SpawnWave();

	// �����Լ�
	bool EnemySpawn(EnemyName p_name);

	// ���̺� ��Ʈ��
	void WaveControl(const float DeltaTime);

	// ���� ���� �˻� �� ����
	int SetSpawnSpot(int m_Spawn_Pos);

	// ���� ���̺� �̵� �� �ʱ�ȭ
	void NextWave();

	// ������ Ȱ/��Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnEnable(bool p_flag);

	// ���������̺� �Է�
	void SetDataTable(int p_curWave);

	// �̸� Enemy�� �ε��صδ� �Լ�
	void LoadEnemy();
	void LoadControl();
};
