// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/BoxComponent.h"
#include "FPSBomb.h"

// Sets default values
AFPSBomb::AFPSBomb()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BombBox = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    BombBox->SetCollisionProfileName("BlockAll");
    BombBox->SetNotifyRigidBodyCollision(true);
    BombBox->SetSimulatePhysics(true);
    BombBox->OnComponentHit.AddDynamic(this, &AFPSBomb::OnHit);

    BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOMB"));
    //BombMesh->SetSimulatePhysics(true);

    //BombMesh->SetCollisionProfileName("BlockAll");
    //BombMesh->SetNotifyRigidBodyCollision(true);
    //BombMesh->SetSimulatePhysics(true);
    //BombMesh->OnComponentHit.AddDynamic(this, &AFPSBomb::OnHit);


    ExplodeDelay = 2.0f;

}

// Called when the game starts or when spawned
void AFPSBomb::BeginPlay()
{
    Super::BeginPlay();
    fuseTimer = ExplodeDelay;
}

void AFPSBomb::BeginCountdown()
{
    isCountingDown = true;
}

// Called every frame
void AFPSBomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (isCountingDown)
    {
        fuseTimer -= DeltaTime;

        if (fuseTimer <= 0)
        {
            Explode();
            isCountingDown = false;
        }
    }
    else if (isExploding)
    {
        explosionDuration -= DeltaTime;
        if (explosionDuration < +0)
        {
            DestroyBomb();
        }
    }

}

void AFPSBomb::Explode()
{
    isExploding = true;
}

void AFPSBomb::DestroyBomb()
{
    Destroy();
}

void AFPSBomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult& Hit)
{
    int bp = 5;
    if (isArmed)
    {
        isCountingDown = true;
    }
}

void AFPSBomb::Hold(USkeletalMeshComponent* HoldingCOmponent)
{
    isArmed = false;
    isCountingDown = false;
    fuseTimer = ExplodeDelay;
}

void AFPSBomb::Throw(FVector direction)
{
    isArmed = true;
}

