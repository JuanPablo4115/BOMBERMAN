// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABomb::ABomb()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;  // Set it as the root component
    // Set collision properties
    CollisionComponent->SetSphereRadius(radioCollision);  // Initial radius

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // Ensure collision is enabled
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);  // Make sure it's set to interact with dynamic objects
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);  // Ignore all channels by default
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);  // Respond to player collision
    CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    CollisionComponent->SetSimulatePhysics(true);
    //CollisionComponent->bGenerateHitEvents = true;
    CollisionComponent->SetGenerateOverlapEvents(true);
    // Bind hit event
    CollisionComponent->OnComponentHit.AddDynamic(this, &ABomb::ChocarBomba);

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBeginOverlap);
    // Create and initialize the Static Mesh Component
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(RootComponent); // Attach the mesh to the root component

    // Set default mesh for the bomb (replace path with actual asset)
    //static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Path/To/Your/BombMesh.BombMesh'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (MeshAsset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(MeshAsset.Object); // Set the mesh if found
    }

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ExplosionDelayHandle, this, &ABomb::EnableExplosion, 0.3f, false);
}
void ABomb::EnableExplosion()
{
    bCanExplode = true;
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABomb::Explode()
{
    UE_LOG(LogTemp, Warning, TEXT("Bomb exploded!"));
    Destroy();
}
// Function called when the bomb collides with an object
void ABomb::ChocarBomba(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
    if (!bCanExplode) return;
    UE_LOG(LogTemp, Warning, TEXT("Bomb is hitting something"));
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Bomb hit a wall and will disappear!"));
        Explode();
    }
}


void ABomb::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //UE_LOG(LogTemp, Warning, TEXT("Overlapping"));
    UE_LOG(LogTemp, Warning, TEXT("Bomb overlapped with: %s"), *OtherActor->GetName());
}