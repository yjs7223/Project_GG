// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	SetDataTable(curWave);
	LoadControl();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WaveControl(DeltaTime);
}

void AEnemySpawner::SpawnWave()
{
	if (EnemySpawn(EnemyName::RIFLE))
	{

	}
	else
	{
		// ���� �Ϸ�
		spawnCheck = true;
		for (int i = 0; i < enemyCount.Num(); i++)
		{
			enemyCount[i] = 0;
		}
		
	}
}

bool AEnemySpawner::EnemySpawn(EnemyName p_name)
{
	AEnemy* e = nullptr;
	// ������
	if (enemyCount[(int)p_name] < spawn_Wave[p_name])
	{
		// ���� ��ġ �˻� �� ����
		spawn_Spot = SetSpawnSpot(spawn_Spot);

		// ����
		APawn* temp = nullptr;

		switch (p_name)
		{
		case EnemyName::RIFLE:
			temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), enemyRifle, enemyBT, loadPos->GetActorLocation(), FRotator(0, 0, 0), true);
			break;
		case EnemyName::HEAVY:
			temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), enemyHeavy, enemyBT, loadPos->GetActorLocation(), FRotator(0, 0, 0), true);
			break;
		case EnemyName::SNIPER:
			temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), enemySniper, enemyBT, loadPos->GetActorLocation(), FRotator(0, 0, 0), true);
			break;
		}

		e = Cast<AEnemy>(temp);

		// �����Ǹ鼭 �ڽ��� ������ �����ʸ� �����ϵ��� ��
		if (e != nullptr)
		{
			e->mySpawner = this;
			e->Init();

			enemyCount[(int)p_name]++;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void AEnemySpawner::WaveControl(const float DeltaTime)
{
	if (curSpawnData == nullptr || spawnSpots.Num() <= 0)
	{
		return;
	}

	// ������ ���̺����� Ȯ�� �� ����
	if (bSpawnerOn && !spawnCheck)
	{
		switch (spawn_Type)
		{
		case SpawnType::KILL:
			if (playerKill >= spawn_Condition)
			{
				spawn_Delay += DeltaTime;
				if (spawn_Delay >= curSpawnData->spawn_Delay)
				{
					SpawnWave();
					spawn_Delay = 0;
				}
			}
			break;
		case SpawnType::SECONDS:
			spawn_Timer += DeltaTime;
			if (spawn_Timer >= spawn_Condition)
			{
				spawn_Delay += DeltaTime;
				if (spawn_Delay >= curSpawnData->spawn_Delay)
				{
					SpawnWave();
					spawn_Delay = 0;
					playerKill = 0;
				}
			}
			break;
		}
	}

	if (spawnCheck && spawnData->GetRowNames().Num() >= curWave)
	{
		bSpawnerOn = false;
		waveEnd = true;
		curWave = 0;

	}
	// ���� ���̺�
	else if (spawnCheck)
	{
		NextWave();
	}
}

void AEnemySpawner::NextWave()
{
	playerKill = 0;
	spawn_Timer = 0;
	// ���� ���̺�� �ѱ��
	SetDataTable(++curWave);
	spawnCheck = false;
}

void AEnemySpawner::SpawnEnable(bool p_flag)
{
	bSpawnerOn = p_flag;
}

void AEnemySpawner::SetDataTable(int p_curWave)
{
	if (spawnData != nullptr)
	{
		curSpawnData = spawnData->FindRow<FST_Spawner>(*FString::FromInt(p_curWave), TEXT(""));
		if (curSpawnData != nullptr)
		{
			spawn_Condition = curSpawnData->spawn_Condition;
			spawn_Delay = curSpawnData->spawn_Delay;
			spawn_Spot = curSpawnData->spawn_Spot;
			spawn_Type = curSpawnData->spawn_Type;
			spawn_Wave = curSpawnData->spawn_Wave;
		}
	}
}

void AEnemySpawner::LoadEnemy()
{

	if (EnemySpawn(EnemyName::RIFLE))
	{

	}
	else
	{
		// ���� �Ϸ�
		spawnCheck = true;
		for (int i = 0; i < enemyCount.Num(); i++)
		{
			enemyCount[i] = 0;
		}

	}
}

void AEnemySpawner::LoadControl()
{
	if (curSpawnData == nullptr || spawnSpots.Num() <= 0)
	{
		return;
	}

	// ������ ���̺����� Ȯ�� �� ����
	if (bSpawnerOn && !spawnCheck)
	{
		switch (spawn_Type)
		{
		case SpawnType::KILL:
			LoadEnemy();
			spawn_Delay = 0;
			break;
		case SpawnType::SECONDS:
			LoadEnemy();
			spawn_Delay = 0;
			playerKill = 0;
			break;
		}
	}

	if (spawnCheck && spawnData->GetRowNames().Num() >= curWave)
	{
		bSpawnerOn = false;
		waveEnd = true;
		curWave = 0;
	}
	// ���� ���̺�
	else if (spawnCheck)
	{
		NextWave();
	}
}

int AEnemySpawner::SetSpawnSpot(int p_Spawn_Pos)
{
	// �÷��̾�� ������ �ʴٸ� ��ȯw
	if (spawnSpots[spawn_Spot]->GetDistanceTo(player) >= 0)
	{
		p_Spawn_Pos = spawn_Spot;
	}
	else
	{
		for (int i = 0; i < spawnSpots.Num(); i++)
		{
			// �÷��̾� �Ÿ��� 50���� ū ������ġ��
			if (spawnSpots[i]->GetDistanceTo(player) > 50)
			{
				// ó�� ���� �Ŷ�� �ϴ� �ֱ�
				if (p_Spawn_Pos == spawn_Spot)
				{
					p_Spawn_Pos = i;
				}
				// ���� �� ���� �� Ȯ���ϰ� ���� �ɷ� �ֱ�
				if (spawnSpots[p_Spawn_Pos]->GetDistanceTo(player) >
					spawnSpots[i]->GetDistanceTo(player))
				{
					p_Spawn_Pos = i;
				}
			}
		}
	}
	return p_Spawn_Pos;
}
