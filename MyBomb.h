// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "MyBomb.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT6_API AMyBomb : public ABomb
{
	GENERATED_BODY()
	
public:
	AMyBomb();

protected:
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

	virtual void Explode() override;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleComponent;
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
