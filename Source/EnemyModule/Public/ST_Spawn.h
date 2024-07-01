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
	// ���� ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SpawnType spawn_Type;

	// ���� ���� ������ ������ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Delay;

	// �� ���̺긶�� ��ȯ�� ���ֵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EnemyName, int> spawn_Wave =
	{ {EnemyName::RIFLE, 0} };

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Condition;

	// ������ ������ ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawn_Spot;
};