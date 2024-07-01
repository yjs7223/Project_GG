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

	// 현재 웨이브
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int curWave;

	// 스폰 관련 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* spawnData;
	// 현재 데이터 테이블
	struct FST_Spawner* curSpawnData;

	// 스포너 활성화 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		bool bSpawnerOn;

	// 플레이어가 사살한 적의 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		int playerKill;

	// 웨이브 생성 후 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawnSeconds;

	// 딜레이용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawn_Timer;

	// 스폰할 적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemyRifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemySniper;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> enemyHeavy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		class UBehaviorTree* enemyBT;

	class UEnemyController* controller;

	// Enemy 시작 시 보관 위치
	AActor* loadPos;

	// 이번 웨이브 소환 여부
	bool spawnCheck;

	// 이번 웨이브에 소환 한 수
	TArray<int> enemyCount;

	// 스포너 스폰 지점들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> spawnSpots;
	
	// 플레이어
	ACharacter* player;

	// 데이터 테이블 정보
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

	// 웨이브 스폰
	void SpawnWave();

	// 스폰함수
	bool EnemySpawn(EnemyName p_name);

	// 웨이브 컨트롤
	void WaveControl(const float DeltaTime);

	// 스폰 지점 검사 후 변경
	int SetSpawnSpot(int m_Spawn_Pos);

	// 다음 웨이브 이동 및 초기화
	void NextWave();

	// 스포너 활/비활성화
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnEnable(bool p_flag);

	// 데이터테이블 입력
	void SetDataTable(int p_curWave);

	// 미리 Enemy를 로드해두는 함수
	void LoadEnemy();
	void LoadControl();
};
