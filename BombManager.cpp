// Fill out your copyright notice in the Description page of Project Settings.
#include "BombManager.h"
#include "Engine/World.h"
#include "BombActor.h"

// Inicializar la variable estática
UBombManager* UBombManager::Instance = nullptr;

UBombManager* UBombManager::GetInstance(UWorld* World) {
    // Si no existe instancia y tenemos un mundo válido
    if (!Instance && World) {
        // Crear nueva instancia ligada al mundo
        Instance = NewObject<UBombManager>(World);
        // Proteger de garbage collection
        Instance->AddToRoot();

        // Configurar delegado para limpiar cuando el mundo se destruya
        if (World) {
            FWorldDelegates::OnWorldCleanup.AddUObject(Instance, &UBombManager::OnWorldCleanup);
        }
    }
    return Instance;
}

void UBombManager::SpawnBomb(FVector Location) {
    if (Instance) {
        UWorld* World = Instance->GetWorld();
        if (World) {
            // Parámetros de spawn
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            // Spawn de la bomba
            ABombActor* NewBomb = World->SpawnActor<ABombActor>(ABombActor::StaticClass(), Location, FRotator::ZeroRotator, SpawnParams);

            if (NewBomb) {
                UE_LOG(LogTemp, Log, TEXT("Bomb spawned at location: %s"), *Location.ToString());
            }
        }
    }
}

void UBombManager::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources) {
    // Limpiar la instancia cuando el mundo se destruya
    if (Instance && Instance->GetWorld() == World) {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
}