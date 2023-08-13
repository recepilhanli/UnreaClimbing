// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParkourController.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_API AParkourController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;


	void MoveForward(float value);
	void MoveRight(float value);
	void LookX(float value);
	void LookY(float value);
	void Jump();
	void Crouch();
	void Sprint();

	
	
public:
	bool Sprinting = false;

};
