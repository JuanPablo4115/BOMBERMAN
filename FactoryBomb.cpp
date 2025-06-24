// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryBomb.h"

UFactoryBomb* UFactoryBomb::Instance = nullptr;
UFactoryBomb* UFactoryBomb::GetInstance(UWorld* World) {
	if (!Instance && World) {
		Instance = NewObject<UFactoryBomb>(World);
		Instance->AddToRoot();
		if (World) {
			FWorldDelegates::OnWorldCleanup.AddUObject(Instance, &UFactoryBomb::OnWorldCleanup);
		}
	}
	return Instance;
}
ABomb* UFactoryBomb::CreateBomb(UWorld* World, EBombType BombType, const FVector& Location, const FRotator& Rotation)
{
    if (!World) return nullptr;

    TSubclassOf<ABomb> BombClass;

    switch (BombType)
    {
    case EBombType::Simple:
        BombClass = ASimpleBomb::StaticClass();
        break;

    case EBombType::Grow:
        BombClass = AGrowBomb::StaticClass();
        break;

    case EBombType::Particle:
        BombClass = AMyBomb::StaticClass();
        break;

    default:
        return nullptr;
    }

    ABomb* NewBomb = World->SpawnActor<ABomb>(BombClass, Location, Rotation);
    if (NewBomb)
    {
        ApplyMaterial(NewBomb);
    }
    return NewBomb;
}
void UFactoryBomb::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources) {
	// Limpiar la instancia cuando el mundo se destruya
	if (Instance && Instance->GetWorld() == World) {
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}