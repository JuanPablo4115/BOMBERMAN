// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bomb.h"
#include "SimpleBomb.h"
#include "GrowBomb.h"
#include "MyBomb.h"
#include "Engine/World.h"
#include "FactoryBomb.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBombType : uint8
{
	Simple,
	Grow,
	Particle,
};
UCLASS()
class MYPROJECT6_API UFactoryBomb : public UObject
{
	GENERATED_BODY()
public:
	static UFactoryBomb* GetInstance(UWorld* World);
	ABomb* CreateBomb(UWorld* World, EBombType BombType, const FVector& Location, const FRotator& Rotation);
	virtual void ApplyMaterial(ABomb* Bomb)PURE_VIRTUAL(UFactoryBomb::ApplyMaterial, );
private:
	static UFactoryBomb* Instance;
	UFUNCTION()
	void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
};
