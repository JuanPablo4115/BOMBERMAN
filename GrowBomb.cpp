// Fill out your copyright notice in the Description page of Project Settings.


#include "GrowBomb.h"

AGrowBomb::AGrowBomb() {

}
void AGrowBomb::BeginPlay()
{
    Super::BeginPlay();
    CurrentScale = 1.0f;
}
void AGrowBomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GrowAndExplode(DeltaTime);
}
void AGrowBomb::GrowAndExplode(float DeltaTime) {
    if (!bCanExplode || bHasReachedMaxSize) return;

    CurrentScale += GrowthRate * DeltaTime;

    if (CurrentScale >= MaxScale)
    {
        CurrentScale = MaxScale;
        bHasReachedMaxSize = true;

        GetWorldTimerManager().SetTimer(ExplosionDelayHandle, this, &AGrowBomb::Explode, ExplosionDelayAfterMaxSize, false);
    }

    StaticMeshComponent->SetWorldScale3D(FVector(CurrentScale));
    CollisionComponent->SetSphereRadius(radioCollision * CurrentScale);
}