// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpActor.generated.h"

UCLASS()
class TUTORIAL_CPP_API AJumpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* JumpMesh;

	//Settings
	UPROPERTY(EditAnywhere, Category = "Jumping Settings")
	float JumpHeight = 200.0f;
	UPROPERTY(EditAnywhere, Category = "Jumping Settings")
	float JumpSpeed = 60.0f;
	UPROPERTY(EditAnywhere, Category = "Jumping Settings")
	float JumpOffset = 0.0f;

private:
	FVector m_startPos;
	float current_offset = 0.0f;
	int current_direction = 1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
