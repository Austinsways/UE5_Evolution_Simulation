// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEntity::AEntity()
{
    //give random traits and movespeed and sight distance
    for (int i = 0; i < NumberOfTraits; i++) {
        int input_trait = FMath::RandRange(1, 9);
        input_traits.Add(input_trait);
    }
    for (int i = 0; i < NumberOfTraits; i++) { 
        int output_trait = FMath::RandRange(1, 4);
        output_traits.Add(output_trait);
    }
    color = FMath::RandRange(1, 9);
    movementSpeed = FMath::RandRange(0.1f, 5.9f);
    SeeingDistance = FMath::RandRange(1.0f, 2000.f);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //set up a mesh so the entity is moveable and has a location
    EntityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

    //attaching components nd setting physics
    Sphere->SetupAttachment(RootComponent);
    Sphere->SetSimulatePhysics(true);
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    EntityMesh->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
    EntityMesh->SetRelativeScale3D(FVector(0.5,0.5,0.5));
    
    //use constructor helper to set our static mesh to a sphere shape
    static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("Staticmesh'/Engine/EditorMeshes/ArcadeEditorSphere.ArcadeEditorSphere'"));
    EntityMesh->SetStaticMesh(SphereMeshAsset.Object);

    //set the color of the mesh based on the color of the entity
    
    switch (color)
    {
    default: {
        break;
    }

    case 1: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/green.green'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 2: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/purple.purple'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 3: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/red.red'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 4: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/white.white'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 5: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/blue.blue'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 6: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/cyan.cyan'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 7: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/hot_pink.hot_pink'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 8: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/orange.orange'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 9: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/pink.pink'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    case 10: {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface>SphereMeshMaterial(TEXT("Material'/Game/colors/yellow.yellow'"));
        SphereColor = SphereMeshMaterial.Object;
        EntityMesh->SetMaterial(0, SphereColor);
        break;
    }
    }


    



    

    


}

bool AEntity::triggered_input(int entity_input_trait, float entity_SeeingDistance) {
    
    switch (entity_input_trait)
    {
    case 0: {
        //this will be removed once the 0 trait is taken out.
        break;
    }
    case 1: {
        //this always returns true  
        
        return true;
    }
    case 2: {
        //return true if there is another creature in front of the entity
        //start by checking forwards and defining the orgiin for the ray
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        FVector End = GetActorLocation();
        End.X += entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //check behind
        End = GetActorLocation();
        End.X -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //check right
        End = GetActorLocation();
        End.Y += entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //check left  
        End = GetActorLocation();
        End.Y -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //this returns false if there's no creatures within 5 units.
        return false;
    }


    case 3: {
        //return true if there is a creature directly forward
        //this checks every location in front of the creature until it reaches the length of the sim environment
        //return true if something is to the left of the entity
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        //FVector ForwardVector = this->GetActorForwardVector();

        //Start = Start + ForwardVector;
        //FVector End = Start + (ForwardVector * 500.f);
        FVector End = GetActorLocation();
        End.X += entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        

        //return false if nothings in front of it.
        return false;

    }
    case 4:
    {
        //return true if there is a creature directly behind
        //this checks all spots behind the creature and returns true if any are found directly behind it.
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        //FVector ForwardVector = this->GetActorForwardVector();

        //Start = Start + ForwardVector;
        //FVector End = Start + (ForwardVector * 500.f);
        FVector End = GetActorLocation();
        End.X -= entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //return false if nothings behind it
        return false;
    }
    case 5:
    {
        //return true if something is to the left of the entity
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        //FVector ForwardVector = this->GetActorForwardVector();

        //Start = Start + ForwardVector;
        //FVector End = Start + (ForwardVector * 500.f);
        FVector End = GetActorLocation();
        End.Y -= entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //return false if nothin is to the left
        return false;
    }
    case 6:
    {
        //return true if something is to the right of the entity
        //return true if something is to the left of the entity
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        //FVector ForwardVector = this->GetActorForwardVector();

        //Start = Start + ForwardVector;
        //FVector End = Start + (ForwardVector * 500.f);
        FVector End = GetActorLocation();
        End.Y += entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return true;
        }

        //return false if nothin is to the right
        return false;
    }
    case 7:
    {
        //return true if touching another creature
        //return true;

        //return false if not touching
        return false;
    }
    case 8:
    {
        //return true if no creatures around  
       
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        FVector End = GetActorLocation();
        End.X += entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return false;
        }

        //check behind
        End = GetActorLocation();
        End.X -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return false;
        }

        //check right
        End = GetActorLocation();
        End.Y += entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return false;
        }

        //check left  
        End = GetActorLocation();
        End.Y -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            return false;
        }

        //this returns true if there's no creatures within 5 units.
        return true;
    
    }
    case 9:
    {
        //count the amount of entitys collided with.
        int counter = 0;
        FHitResult Outhit;
        FVector Start = GetActorLocation();
        FVector End = GetActorLocation();
        End.X += entity_SeeingDistance;
        FCollisionQueryParams CollisionParameters;
        CollisionParameters.AddIgnoredActor(this->GetOwner());
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        bool IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            counter += 1;
        }

        //check behind
        End = GetActorLocation();
        End.X -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            counter += 1;
        }

        //check right
        End = GetActorLocation();
        End.Y += entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            counter += 1;
        }

        //check left  
        End = GetActorLocation();
        End.Y -= entity_SeeingDistance;
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

        IsHit = GetWorld()->LineTraceSingleByChannel(Outhit, Start, End, ECC_Visibility, CollisionParameters);

        if (IsHit) {
            counter += 1;
        }

        //this returns false if there's no creatures within 5 units.
        if (counter >=4) {
            return true;
    }
        else {
            return false;
        }
    }
    default:
        //this case should never be used, it works like an assert for now.
    {
        return false;
    };
    }
    return false;
};

void AEntity::apply_output(int entity_output_trait, float entity_movementSpeed) 
    {
        //applying the output trait goes here.
    FVector newLocation = GetActorLocation();
    switch (entity_output_trait)
    {
    case 0: {
        //this should never happen

        break;
    }
    case 1: {
        //move forward
        newLocation.X += movementSpeed;
        SetActorLocation(newLocation);
        break;
    }

    case 2: {
        //move backward
        newLocation.X -= movementSpeed;
        SetActorLocation(newLocation);
        break;
    }

    case 3: {
        //move left
        newLocation.Y -= movementSpeed;
        SetActorLocation(newLocation);
        break;
    }
    case 4: {
        //move right
        newLocation.Y += movementSpeed;
        SetActorLocation(newLocation);
        break;
    }

          //this will house the kill gene which is not going to be written yet.
    default: {
        break;
    };
           return;
    }
}


// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //see if the input is met
    for (int i = 0; i < NumberOfTraits; i++) {
        int input_trait = input_traits[i];
        if (triggered_input(input_trait, SeeingDistance))
        {
            //execute the output ("move the entity")
            int output_trait = output_traits[i];
            apply_output(output_trait, movementSpeed);
        }

    }
}

