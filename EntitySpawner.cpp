// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawner.h"
#include "Entity.h"
#include "Components/BoxComponent.h"

// Sets default values
AEntitySpawner::AEntitySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void AEntitySpawner::SpawnEntity() {
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<AEntity>(SpawnLocation, SpawnRotation);
}

void AEntitySpawner::SpawnEntityFromParent(AActor* parent) {
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	FActorSpawnParameters parent_structured;
	parent_structured.Template = parent;
	GetWorld()->SpawnActor<AEntity>(SpawnLocation, SpawnRotation,parent_structured );
}

// Called when the game starts or when spawned
void AEntitySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

