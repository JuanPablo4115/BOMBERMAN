// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "Bomb.generated.h"

UCLASS()
class MYPROJECT6_API ABomb : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABomb();


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(VisibleAnywhere)
    USphereComponent* CollisionComponent;

    // Static mesh component for visual representation
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;


    // Called when the bomb collides with an object
    UFUNCTION()

    void ChocarBomba(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult);
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    UPROPERTY(EditAnywhere)
    float radioCollision = 60.0f;
    FTimerHandle ExplosionDelayHandle;
    bool bCanExplode = false;

    // Método para habilitar explosión
    void EnableExplosion();
    virtual void Explode();
};