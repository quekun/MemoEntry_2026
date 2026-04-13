// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/BoxComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    
    ChassisMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisMesh"));
    
    HatchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatchMesh"));
    
    wheelsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("heels_02_Mesh"));
    

    SetRootComponent(BoxComp);
    HatchMesh->SetupAttachment(ChassisMesh);
    wheelsMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::Fire()
{

}



