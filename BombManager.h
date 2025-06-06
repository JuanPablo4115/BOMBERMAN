// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "BombManager.generated.h"

/**
 * Singleton manager for handling bomb spawning and management
 */
UCLASS()
class MYPROJECT6_API UBombManager : public UObject
{
    GENERATED_BODY()

public:
    // Obtener la instancia singleton
    static UBombManager* GetInstance(UWorld* World);

    // Spawnear una bomba en la ubicación especificada
    void SpawnBomb(FVector Location);


private:
    // Instancia singleton estática
    static UBombManager* Instance;

    // Método para limpiar cuando el mundo se destruye
    UFUNCTION()
    void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
};