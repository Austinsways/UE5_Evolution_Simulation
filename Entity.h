// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity.generated.h"


UCLASS()
class TUTORIAL_CPP_API AEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntity();
	UPROPERTY(EditAnywhere, Category = "Traits")
	int NumberOfTraits = 5;
	UPROPERTY(EditAnywhere, Category = "Traits")
	TArray<int32> input_traits;
	UPROPERTY(EditAnywhere, Category = "Traits")
	TArray<int32> output_traits;
	UPROPERTY(EditAnywhere, Category = "Traits")
	int color;
	UPROPERTY(EditAnywhere, Category = "Traits")
	float movementSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Traits")
	float SeeingDistance;
	bool triggered_input(int entity_input_trait, float entity_SeeingDistance);
	void apply_output(int entity_output_trait, float entity_movementSpeed);
	UMaterialInterface* SphereColor;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* EntityMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
