// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBomb.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AMyBomb::AMyBomb()
{
    // Crear y configurar el componente de partículas
    ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionEffect"));
    ParticleComponent->SetupAttachment(RootComponent);
    ParticleComponent->bAutoActivate = false; // No se activa hasta que explote

    // Cargar el sistema de partículas desde el contenido
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'")); // Reemplaza si usas otro efecto

    if (ParticleAsset.Succeeded())
    {
        ParticleComponent->SetTemplate(ParticleAsset.Object);
    }
}
void AMyBomb::BeginPlay()
{
    Super::BeginPlay();
    CurrentScale = 1.0f;
}
void AMyBomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GrowAndExplode(DeltaTime);
}
void AMyBomb::GrowAndExplode(float DeltaTime) {
    if (!bCanExplode || bHasReachedMaxSize) return;

    CurrentScale += GrowthRate * DeltaTime;

    if (CurrentScale >= MaxScale)
    {
        CurrentScale = MaxScale;
        bHasReachedMaxSize = true;

        GetWorldTimerManager().SetTimer(ExplosionDelayHandle, this, &AMyBomb::Explode, ExplosionDelayAfterMaxSize, false);
    }

    StaticMeshComponent->SetWorldScale3D(FVector(CurrentScale));
    CollisionComponent->SetSphereRadius(radioCollision * CurrentScale);
}
void AMyBomb::Explode()
{
    UE_LOG(LogTemp, Warning, TEXT("MyBomb exploded with particle effects!"));

    // Activar el componente de partículas (si está adjunto)
    if (ParticleComponent && !ParticleComponent->IsActive())
    {
        ParticleComponent->Activate(true);
    }

    // O bien, generar una instancia suelta en el mundo (más notorio y desacoplado del actor destruido)
    if (ParticleComponent && ParticleComponent->Template)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleComponent->Template, GetActorLocation());
    }

    Destroy();
}