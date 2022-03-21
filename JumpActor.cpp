// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpActor.h"

// Sets default values
AJumpActor::AJumpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create components
	JumpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JumpMesh"));

}

// Called when the game starts or when spawned
void AJumpActor::BeginPlay()
{
	Super::BeginPlay();

	//store initial position
	m_startPos = GetActorLocation();
	current_offset = JumpOffset;
	
}

// Called every frame
void AJumpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//increment the offset
	current_offset += DeltaTime * JumpSpeed * current_direction;

	//clamp to bound and change direction if needed 
	if (current_direction == 1 && current_offset >= JumpHeight)
	{
		current_offset = JumpHeight;
		current_direction = -1;
	}
	else if (current_direction == -1 && current_offset <= 0.0f)
	{
		current_offset = 0.0f;
		current_direction = 1;
	}

	//set actor position 
	FVector newPos = m_startPos;
	newPos.Z += current_offset;
	SetActorLocation(newPos);
}

