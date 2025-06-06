// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Pared.generated.h"

UCLASS()
class MYPROJECT6_API APared : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APared();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	void CambiarMesh();
	void CambiarMaterial();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, Category = "Movimiento")
	TArray<UStaticMesh*> ListaDeMeshes;
	int IndiceActual;
	UPROPERTY(EditAnywhere, Category = "Movimiento")
	TArray<UMaterialInterface*> ListaDeMateriales;
	int IndiceMaterialActual;
};
