// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourController.h"
#include "InputAction.h"
#include "ParkourCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AParkourController::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AParkourController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AParkourController::MoveRight);
	InputComponent->BindAxis("LookX", this, &AParkourController::LookX);
	InputComponent->BindAxis("LookY", this, &AParkourController::LookY);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AParkourController::Jump);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AParkourController::Crouch);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AParkourController::Sprint);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AParkourController::Sprint);


	
	
}

void AParkourController::MoveForward(const float Value)
{
	auto fwd = GetPawn()->GetActorForwardVector();
	GetPawn()->AddMovementInput(fwd, Value);
}

void AParkourController::MoveRight(const float Value)
{
	auto rwd = GetPawn()->GetActorRightVector();
	GetPawn()->AddMovementInput(rwd, Value);
}

void AParkourController::LookX(const float Value)
{
	GetPawn()->AddControllerYawInput(Value);
}

void AParkourController::LookY(const float Value)
{
	GetPawn()->AddControllerPitchInput(-Value);
}

void AParkourController::Jump()
{
	AParkourCharacter * MyCharacter = Cast<AParkourCharacter>(GetPawn());
	if(MyCharacter)
	{
		MyCharacter->Jump(); 
	}
}
void AParkourController::Crouch()
{
	AParkourCharacter * MyCharacter = Cast<AParkourCharacter>(GetPawn());
	if(MyCharacter)
	{
		if(MyCharacter->bIsCrouched) MyCharacter->Crouch();
		else MyCharacter->UnCrouch();
	}
}

void AParkourController::Sprint()
{
	Sprinting = !Sprinting;
	AParkourCharacter * MyCharacter = Cast<AParkourCharacter>(GetPawn());
	if(MyCharacter)
	{
		if(MyCharacter->Stamania > 0 && Sprinting)
		{
			MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 900;
		}
		else MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 500;
	}
}

