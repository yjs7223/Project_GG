// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ST_Spawn.generated.h"

UENUM(BlueprintType)
enum class SpawnType : uint8
{
	KILL, SECONDS
};

UENUM(BlueprintType)
enum class EnemyName : uint8
{
	NONE, RIFLE, HEAVY, SNIPER
};


UCLASS()
class ENEMYMODULE_API UST_Spawn : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FST_Spawner : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// 생성 조건 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SpawnType spawn_Type;

	// 스폰 액터 사이의 딜레이 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Delay;

	// 각 웨이브마다 소환할 유닛들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EnemyName, int> spawn_Wave =
	{ {EnemyName::RIFLE, 0} };

	// 스폰 조건
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Condition;

	// 유닛이 생성될 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawn_Spot;
};