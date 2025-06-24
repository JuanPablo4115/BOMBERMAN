// Copyright Epic Games, Inc. All Rights Reserved.
#include "MyProject6PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyProject6Character.h"
#include "Pared.h"
#include "Engine/World.h"

AMyProject6PlayerController::AMyProject6PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyProject6PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMyProject6PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMyProject6PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMyProject6PlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyProject6PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyProject6PlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProject6PlayerController::OnResetVR);
	InputComponent->BindAction("CambiarMesh", IE_Pressed, this, &AMyProject6PlayerController::OnCambiarMalla);
	InputComponent->BindAction("CambiarMaterial", IE_Pressed, this, &AMyProject6PlayerController::OnCambiarMaterial);
	InputComponent->BindAction("DejarBomba", IE_Pressed, this, &AMyProject6PlayerController::OnDejarBomba);
	InputComponent->BindAction("DejarMonedas", IE_Pressed, this, &AMyProject6PlayerController::OnDejarMonedas);
	/*InputComponent->BindAction("PlaceSimpleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnPlaceSimpleBomb);
	InputComponent->BindAction("PlaceGrowBomb", IE_Pressed, this, &AMyProject6PlayerController::OnPlaceGrowBomb);
	InputComponent->BindAction("PlaceParticleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnPlaceParticleBomb);*/
	InputComponent->BindAction("BlackSimpleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnBlackSimpleBomb);
	InputComponent->BindAction("BlackGrowBomb", IE_Pressed, this, &AMyProject6PlayerController::OnBlackGrowBomb);
	InputComponent->BindAction("BlackParticleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnBlackParticleBomb);

	InputComponent->BindAction("GoldSimpleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnGoldSimpleBomb);
	InputComponent->BindAction("GoldGrowBomb", IE_Pressed, this, &AMyProject6PlayerController::OnGoldGrowBomb);
	InputComponent->BindAction("GoldParticleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnGoldParticleBomb);

	InputComponent->BindAction("SilverSimpleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnSilverSimpleBomb);
	InputComponent->BindAction("SilverGrowBomb", IE_Pressed, this, &AMyProject6PlayerController::OnSilverGrowBomb);
	InputComponent->BindAction("SilverParticleBomb", IE_Pressed, this, &AMyProject6PlayerController::OnSilverParticleBomb);

}
void AMyProject6PlayerController::OnCambiarMalla() {
	for (AActor* Actor : ActoresRegistrados) {
		APared* MiActor = Cast<APared>(Actor);
		if (MiActor) {
			MiActor->CambiarMesh();
		}
	}
}
void AMyProject6PlayerController::OnCambiarMaterial() {
	for (AActor* Actor : ActoresRegistrados) {
		APared* MiActor = Cast<APared>(Actor);
		if (MiActor) {
			MiActor->CambiarMaterial();
		}
	}
}
void AMyProject6PlayerController::OnDejarBomba()
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	// Cast al personaje si es necesario
	AMyProject6Character* PlayerCharacter = Cast<AMyProject6Character>(ControlledPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->PlaceBomb();
	}
}
void AMyProject6PlayerController::OnDejarMonedas() {
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;
	AMyProject6Character* PlayerCharacter = Cast<AMyProject6Character>(ControlledPawn);
	if (PlayerCharacter) {
		PlayerCharacter->PlaceCoin();
	}
}
/*void AMyProject6PlayerController::OnPlaceSimpleBomb()
{
	if (AMyProject6Character* Character1 = Cast<AMyProject6Character>(GetPawn()))
	{
		Character1->SpawnBomb(EBombType::Simple);
	}
}
void AMyProject6PlayerController::OnPlaceGrowBomb()
{
	if (AMyProject6Character* Character2 = Cast<AMyProject6Character>(GetPawn()))
	{
		Character2->SpawnBomb(EBombType::Grow);
	}
}
void AMyProject6PlayerController::OnPlaceParticleBomb()
{
	if (AMyProject6Character* Character3 = Cast<AMyProject6Character>(GetPawn()))
	{
		Character3->SpawnBomb(EBombType::Particle);
	}
}*/
void AMyProject6PlayerController::OnBlackSimpleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Simple, UBlackFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnBlackGrowBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Grow, UBlackFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnBlackParticleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Particle, UBlackFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnGoldSimpleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Simple, UGoldFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnGoldGrowBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Grow, UGoldFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnGoldParticleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Particle, UGoldFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnSilverSimpleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Simple, USilverFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnSilverGrowBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Grow, USilverFactoryBomb::StaticClass());
	}
}

void AMyProject6PlayerController::OnSilverParticleBomb()
{
	if (AMyProject6Character* MyCharacter = Cast<AMyProject6Character>(GetPawn()))
	{
		MyCharacter->SpawnBomb(EBombType::Particle, USilverFactoryBomb::StaticClass());
	}
}
void AMyProject6PlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMyProject6PlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AMyProject6Character* MyPawn = Cast<AMyProject6Character>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AMyProject6PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMyProject6PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMyProject6PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMyProject6PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
