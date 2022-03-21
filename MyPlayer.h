// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MyPlayer.generated.h"


UCLASS()
class TUTORIAL_CPP_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

	//delta  movement
	void MoveLR(float movementDelta);
	void MoveUD(float movementDelta);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//create a camera component so the player can see
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CameraMesh;
	
	//movement speed
	UPROPERTY(EditAnywhere, category = "Character Settings")
	float MovementSpeed = 1.0f;

	//add functions to spawn and despawn entitys 
	void SpawnActors();
	void DestroyActors();
	void DestroyAllEntitys();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Counter")
	int Counter = 0;

};
