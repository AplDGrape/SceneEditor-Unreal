// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneLoader.generated.h"

UCLASS()
class MYPROJECT_API ASceneLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Scene")
	TSubclassOf<AActor> CubeActor;

	UPROPERTY(EditAnywhere, Category = "Scene")
	TSubclassOf<AActor> SphereActor;

	UPROPERTY(EditAnywhere, Category = "Scene")
	TSubclassOf<AActor> PlaneActor;
};
