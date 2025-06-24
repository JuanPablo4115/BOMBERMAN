// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombActor.h"
#include "CoinActor.h"
#include "CoinManager.h"
#include "Bomb.h"
#include "BombManager.h"
#include "FactoryBomb.h"
#include "BlackFactoryBomb.h"
#include "SilverFactoryBomb.h"
#include "GoldFactoryBomb.h"
#include "SimpleBomb.h"
#include "GrowBomb.h"
#include "MyBomb.h"
#include "MyProject6Character.generated.h"

UCLASS(Blueprintable)
class AMyProject6Character : public ACharacter
{
	GENERATED_BODY()

public:
	AMyProject6Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	void CollectCoin(ACoinActor* coin);
	// Obtiene el número de monedas recolectadas de un tipo específico (para UI, etc.)
	UFUNCTION(BlueprintCallable, Category = "Coin")
	int32 GetMonedasPorTipo(ECoinType Tipo) const;

	// Obtiene el total de puntos acumulados (suma de CoinValue de todas las monedas)
	UFUNCTION(BlueprintCallable, Category = "Coin")
	int32 GetTotalPuntos() const { return TotalPuntos; }

	// Muestra en pantalla las monedas recolectadas (Debug)
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void MostrarMonedasRecolectadas();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	UPROPERTY(EditAnywhere, Category = "Bomba")
	TArray<ABombActor*> SpawnedBombs;
	UPROPERTY(EditAnywhere, Category = "Bomba")
	UMaterial* CharacterMaterial;


	// Mapa que agrupa monedas por tipo
	TMap<ECoinType, TArray<ACoinActor*>> MonedasPorTipo;
	virtual void BeginDestroy() override;

	// Puntos totales acumulados
	UPROPERTY(VisibleAnywhere, Category = "Coin")
	int32 TotalPuntos = 0;
public:
	void PlaceBomb();
	void ChangeBombMaterials();
	void PlaceCoin();
	void SetBombFactory(UFactoryBomb* NewFactory);
	void SpawnBombWithMaterial(EBombType BombType, TSubclassOf<UFactoryBomb> FactoryClass);
	//void SpawnBomb(EBombType BombType);
	void SpawnBomb(EBombType BombType, TSubclassOf<UFactoryBomb> FactoryClass = nullptr);
private:
	UPROPERTY()
	UFactoryBomb* CurrentBombFactory;
};

