// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EntitySpawner.h"
#include "Entity.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create components
	CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	//setup
	Camera->FieldOfView = 120.0f;
	Camera->SetupAttachment(CameraMesh);
	Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 150.0f));

}

void AMyPlayer::MoveLR(float movementDelta) {
	FVector newLocation = GetActorLocation();
	newLocation.Y += movementDelta*MovementSpeed;
	SetActorLocation(newLocation);
}

void AMyPlayer::MoveUD(float movementDelta) {
	FVector newLocation = GetActorLocation();
	newLocation.X += movementDelta * MovementSpeed;
	SetActorLocation(newLocation);
}

void AMyPlayer::SpawnActors() {
	//find the entity spawner in the world, and invoke its Spawn Entity function
	AActor* EntitySpawnerToFind = UGameplayStatics::GetActorOfClass(GetWorld(), AEntitySpawner::StaticClass());
	AEntitySpawner* EntitySpawnerRefrence = Cast<AEntitySpawner>(EntitySpawnerToFind);
	if (EntitySpawnerRefrence)
	{
		EntitySpawnerRefrence->SpawnEntity();
	}
}

void AMyPlayer::DestroyActors() {
	//destroys entitys that were spawned
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntity::StaticClass(), FoundActors);
	for (AActor* ActorFound : FoundActors)
	{
		FVector ActorLocation = ActorFound->GetActorLocation();

		//if the entity is in the safe zone this relocates them and reproduces it
		if (ActorLocation.X <= -300 && ActorLocation.X > -1030 && ActorLocation.Y > -830.f && ActorLocation.Y < 1030.f) {
			ActorFound->SetActorLocation(FVector(0.0f, 0.0f, 100.0f));
			//find the entity spawner and spawn a child of this entity
			AActor* EntitySpawnerToFind = UGameplayStatics::GetActorOfClass(GetWorld(), AEntitySpawner::StaticClass());
			AEntitySpawner* EntitySpawnerRefrence = Cast<AEntitySpawner>(EntitySpawnerToFind);
			if (EntitySpawnerRefrence)
			{
				EntitySpawnerRefrence->SpawnEntityFromParent(ActorFound);
			}

		}
		else {
			ActorFound->Destroy();
		}
	}
}

void AMyPlayer::DestroyAllEntitys() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntity::StaticClass(), FoundActors);
	for (AActor* ActorFound : FoundActors)
	{
		

	//this just kills all actors
		
		
	ActorFound->Destroy();
		
	}

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (Counter == 900) {
		DestroyActors();
		for (int f = 0; f < 10; f++)
			{
				SpawnActors();
			}
		Counter = 0;
		}

	Counter+= 1;

	

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Register LR movements
	PlayerInputComponent->BindAxis(TEXT("Move_LR"), this, &AMyPlayer::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Move_UD"), this, &AMyPlayer::MoveUD);

	//add the keybinds to spawn and destroy entitys
	PlayerInputComponent->BindAction("SpawnEntitys", IE_Pressed, this, &AMyPlayer::SpawnActors);
	PlayerInputComponent->BindAction("DestroyEntitys", IE_Pressed, this, &AMyPlayer::DestroyActors);
	PlayerInputComponent->BindAction("DestroyAllEntitys", IE_Pressed, this, &AMyPlayer::DestroyAllEntitys);

}

