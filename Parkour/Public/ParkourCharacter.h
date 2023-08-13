// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParkourCharacter.generated.h"

UCLASS()
class PARKOUR_API AParkourCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParkourCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent * FPSCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamania = 100;
	
	float WaitForStamaina = 0;

	void RefillStamania();
	void Velocity();
	void HeightCheck();
	void ForwardCheck();
	void WallRun();
	
	int8 WallRunningState = 0; //0 -> isnt running on wall, 1 -> Running to the right side, -1 -> Running to the left side
	
	class AParkourController * controller;
};
