// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CoinActor.generated.h"

UENUM(BlueprintType)
enum class ECoinType : uint8
{
	Gold,
	Silver,
	Bronze,
};
UCLASS()
class MYPROJECT6_API ACoinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationInterval;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Coin type and value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	ECoinType CoinType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 CoinValue;

private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CoinMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionSphere;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
