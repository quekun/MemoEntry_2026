// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldComponent.h"
#include "Tank.h"


// Sets default values for this component's properties
UShieldComponent::UShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NewShieldMesh_V3"));
}


// Called when the game starts
void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = Cast<ATank>(GetOwner());
	if (MyTank)
	{
		// 2. 这里第一个参数传 this (组件自己)，第二个传组件的函数地址
		MyTank->OnOpenShield.AddDynamic(this, &UShieldComponent::OpenShield);
		MyTank->OnCloseShield.AddDynamic(this, &UShieldComponent::CloseShield);
	}
	
}


// Called every frame
void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UShieldComponent::OpenShield()
{
	if (ShieldMesh)
	{
		ShieldMesh->SetVisibility(true);
	}
}

void UShieldComponent::CloseShield()
{
	if (ShieldMesh)
	{
		ShieldMesh->SetVisibility(false);
	}
}

