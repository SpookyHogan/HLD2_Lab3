// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Component/BoxComponent.h"
//#include ""
//#include "BoxComponent.generated.h"
#include "RadialForceComponent.generated.h"
#include "FPSBomb.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSBomb : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	float ExplodeDelay;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* ExplosionTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UStaticMeshComponent* BombMesh;

	UPROPERTY(VisibleAnywhere, Category = "BombActor")
	UBoxComponent* BombBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* RadialForceComp;

	
public:	
	// Sets default values for this actor's properties
	AFPSBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BeginCountdown();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void Explode();

	UFUNCTION()
	void DestroyBomb();

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult& Hit);

	void Hold(USkeletalMeshComponent* HoldingCOmponent);

	void Throw(FVector direction);

protected:
	float fuseTimer;
	bool isArmed = true;
	bool isCountingDown = false;
	float explosionDuration = 2.0f;
	bool isExploding = false;

};
