// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "GrowBomb.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT6_API AGrowBomb : public ABomb
{
	GENERATED_BODY()
public:
	AGrowBomb();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Bomb Settings")
	float GrowthRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Bomb Settings")
	float MaxScale = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Bomb Settings")
	float ExplosionDelayAfterMaxSize = 0.5f;
private:
	float CurrentScale = 1.0f;
	bool bHasReachedMaxSize = false;
	void GrowAndExplode(float DeltaTime);
};
