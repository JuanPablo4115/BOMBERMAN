// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "UObject/ConstructorHelpers.h"
#include "MyProject6Character.h"
// Sets default values
ACoinActor::ACoinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionSphere;


    CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    CoinMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
    if (MeshAsset.Succeeded())
    {
        CoinMesh->SetStaticMesh(MeshAsset.Object);
        CoinMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 0.3f));
        CoinMesh->SetRelativeRotation(FRotator(90.f, 90.f, 0.f));

        UE_LOG(LogTemp, Warning, TEXT("Mesh Rotate!"));
    }



    CollisionSphere->SetSphereRadius(100);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoinActor::OnOverlapBegin);


    RotationSpeed = 45.f;
    RotationDirection = 1.f;
    RotationTimer = 0.f;
    RotationInterval = 1.0f;

    CoinType = ECoinType::Gold;
    CoinValue = 1;

}

// Called when the game starts or when spawned
void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
    UMaterialInterface* GoldMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
    UMaterialInterface* SilverMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
    UMaterialInterface* BronzeMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Worn.M_Wood_Floor_Walnut_Worn'"));
    switch (CoinType) {
    case ECoinType::Gold:
        CoinMesh->SetMaterial(0, GoldMaterial);
    break;
    case ECoinType::Silver:
        CoinMesh->SetMaterial(0, SilverMaterial);
    break;
    case ECoinType::Bronze:
        CoinMesh->SetMaterial(0, BronzeMaterial);
    break;
    }
}

// Called every frame
void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RotationTimer += DeltaTime;
    if (RotationTimer >= RotationInterval)
    {
        RotationDirection *= -1.f;
            RotationTimer = 0.f;
    }


    FRotator CurrentRotation = CoinMesh->GetRelativeRotation();


    CurrentRotation.Yaw += RotationSpeed * RotationDirection * DeltaTime;


    CoinMesh->SetRelativeRotation(CurrentRotation);
}
void ACoinActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Coin overlapped!"));
        AMyProject6Character* Player = Cast<AMyProject6Character>(OtherActor);
        if (Player)
        {
            UE_LOG(LogTemp, Warning, TEXT("Recollecting the coin before call the player function"));
            Player->CollectCoin(this);
            //implementar si el palyer no es nulo agarrar el player apuntando a player recolecte moneda
        }
    }
}

