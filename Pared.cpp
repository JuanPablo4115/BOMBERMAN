// Fill out your copyright notice in the Description page of Project Settings.


#include "Pared.h"
#include "MyProject6PlayerController.h"

// Sets default values
APared::APared()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMeshComp->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
    if (MeshAsset.Succeeded())
    {
        // Asignar la malla estática al componente
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }
    StaticMeshComp->SetVisibility(true);
}

// Called when the game starts or when spawned
void APared::BeginPlay()
{
	Super::BeginPlay();
    if (ListaDeMeshes.Num() > 0 && ListaDeMeshes[0] != nullptr)
    {
        StaticMeshComp->SetStaticMesh(ListaDeMeshes[0]);
    }
    AMyProject6PlayerController* PC = Cast<AMyProject6PlayerController>(GetWorld()->GetFirstPlayerController());
    if (PC) {
        PC->ActoresRegistrados.Add(this);
    }

}

// Called every frame
void APared::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APared::CambiarMesh() {
    if (ListaDeMeshes.Num() == 0) return;

    IndiceActual = (IndiceActual + 1) % ListaDeMeshes.Num();
    StaticMeshComp->SetStaticMesh(ListaDeMeshes[IndiceActual]);
}
void APared::CambiarMaterial()
{
    if (ListaDeMateriales.Num() == 0) return;

    IndiceMaterialActual = (IndiceMaterialActual + 1) % ListaDeMateriales.Num();
    StaticMeshComp->SetMaterial(0, ListaDeMateriales[IndiceMaterialActual]);
}



