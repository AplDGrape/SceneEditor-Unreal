// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneLoader.h"

//#include "ThirdParty/TinyXML2/tinyxml2.h"
#include "../../ThirdParty/TinyXML2/tinyxml2.h"
#include "../../ThirdParty/TinyXML2/tinyxml2.cpp"
//#include "tinyxml2.h"
using namespace tinyxml2;

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMeshActor.h"

#include <iostream>

// Sets default values
ASceneLoader::ASceneLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneLoader::BeginPlay()
{
	Super::BeginPlay();

	FString FilePath = FPaths::ProjectContentDir() + TEXT("Scenes/ExamTestingScene.xml");
	std::string StdPath = TCHAR_TO_UTF8(*FilePath);

	XMLDocument doc;
	if (doc.LoadFile(StdPath.c_str()) != XML_SUCCESS)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load XML file."));
		return;
	}

	XMLElement* root = doc.FirstChildElement("GameObjects");
	if (!root)
	{
		UE_LOG(LogTemp, Error, TEXT("No GameObjects root found."));
		return;
	}

	float PositionScale = 200.0f;
	float RotationScale = 200.0f;
	FVector GlobalOffset = FVector(0.0f, 0.0f, 50.0f);

	for (XMLElement* obj = root->FirstChildElement("GameObject"); obj != nullptr; obj = obj->NextSiblingElement("GameObject"))
	{
		const char* Name = obj->FirstChildElement("Name")->GetText();
		int Type = obj->FirstChildElement("Type")->IntText();

		auto GetVectorFromElement = [](XMLElement* parent) -> FVector {
			if (!parent) return FVector::ZeroVector;
			float x = parent->FirstChildElement("x") ? parent->FirstChildElement("x")->FloatText(0.0f) : 0.0f;
			float y = parent->FirstChildElement("y") ? parent->FirstChildElement("y")->FloatText(0.0f) : 0.0f;
			float z = parent->FirstChildElement("z") ? parent->FirstChildElement("z")->FloatText(0.0f) : 0.0f;
			return FVector(x, y, z);
			};

		FVector Position = GetVectorFromElement(obj->FirstChildElement("Position")) * PositionScale;

		if (Position.Z < 50.0f)
			Position.Z = 50.0f;

		FVector Scale = GetVectorFromElement(obj->FirstChildElement("Scale"));
		FVector RotationVec = GetVectorFromElement(obj->FirstChildElement("Rotation")) * RotationScale;
		//FVector RotationVec = FVector(0, 0, 0);
		
		// Local object rotation from XML (in degrees)
		FRotator LocalRotator = FRotator::MakeFromEuler(RotationVec);

		//// Convert both to quaternions
		//FQuat LocalQuat = LocalRotator.Quaternion();
		//FQuat GlobalQuat = FRotator(0.0f, 0.0f, -90.0f).Quaternion(); // Roll -90° around Z

		//// Combine global and local rotation
		//FQuat FinalQuat = GlobalQuat * LocalQuat; // Order matters: global * local
		//FRotator FinalRotation = FinalQuat.Rotator();

		TSubclassOf<AActor> SelectedClass = nullptr;
		switch (Type)
		{
		case 2: SelectedClass = CubeActor; break;
		case 3: SelectedClass = PlaneActor; break;
		case 4: SelectedClass = SphereActor; break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown type %d for %s"), Type, *FString(Name));
			continue;
		}

		if (SelectedClass)
		{
			FActorSpawnParameters SpawnParams;
			AActor* Spawned = GetWorld()->SpawnActor<AActor>(SelectedClass, Position, LocalRotator, SpawnParams);

			if (Spawned)
			{
				Spawned->SetActorScale3D(Scale);
				UE_LOG(LogTemp, Warning, TEXT("Spawned %s at (%f, %f, %f) with scale (%f, %f, %f)"),
					*FString(Name),
					Position.X, Position.Y, Position.Z,
					Scale.X, Scale.Y, Scale.Z
				);
			}
		}
	}
}

// Called every frame
void ASceneLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

