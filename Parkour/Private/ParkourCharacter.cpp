// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourCharacter.h"

#include <string>

#include "ParkourController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AParkourCharacter::AParkourCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FPSCamera = CreateDefaultSubobject<UCameraComponent>("FPS Camera");
	FPSCamera->SetupAttachment(RootComponent);
	GetMesh()->SetupAttachment(FPSCamera);
}

// Called when the game starts or when spawned
void AParkourCharacter::BeginPlay()
{
	Super::BeginPlay();
	controller = Cast<AParkourController>(GetController());
	GetCharacterMovement()->MaxAcceleration = 1250;

}

// Called every frame
void AParkourCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RefillStamania();
	ForwardCheck();
	Velocity();
}

void AParkourCharacter::Velocity()
{
	
	if (controller)
	{
		float DeltaTime = GetWorld()->DeltaTimeSeconds;
		float Time = GetWorld()->GetTimeSeconds();
		
		if (controller->Sprinting == true)
		{
			WaitForStamaina = Time + 1;
			Stamania -= DeltaTime * 25;
			if (Stamania <= 0)
			{
				controller->Sprinting = false;
				GetCharacterMovement()->MaxWalkSpeed = 500;
			}
		}
	}

	if(GetCharacterMovement()->Velocity.Z > 500) GetCharacterMovement()->Velocity.Z = 500;

	
}


void AParkourCharacter::ForwardCheck()
{
	if(!GetCharacterMovement()->IsFalling()) return;
	if (Stamania <= 0) return;

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	FVector CharacterPos = GetActorLocation();
	FVector Forward = CharacterPos + GetActorForwardVector() * 100;
	const TArray<AActor*> Ignore;
	FHitResult result;

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	TArray<AActor*> ignoredactors;
	ignoredactors.Add(GetOwner());
	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), CharacterPos, Forward, 5, traceObjectTypes,
	                                                             false,
	                                                             ignoredactors, EDrawDebugTrace::ForDuration, result,
	                                                             true, FLinearColor::Green, FLinearColor::Red, 1);


	if (hit)
	{
		HeightCheck();
	}
}


void AParkourCharacter::HeightCheck()
{
	if (Stamania <= 0) return;

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	FVector Top = (GetActorLocation() + GetActorForwardVector() * 100) + FVector(0, 0, 100);
	FVector Bottom = (GetActorLocation() + GetActorForwardVector() * 100) + FVector(0, 0, -100);;
	const TArray<AActor*> Ignore;
	FHitResult result;

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	TArray<AActor*> ignoredactors;
	ignoredactors.Add(GetOwner());
	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Top, Bottom, 5, traceObjectTypes,
	                                                             false,
	                                                             ignoredactors, EDrawDebugTrace::ForDuration, result,
	                                                             true, FLinearColor::White, FLinearColor::Black, 2);

	if (hit)
	{
		float Time = GetWorld()->GetTimeSeconds();
		WaitForStamaina = Time + 1;
		Stamania -= DeltaTime * 50;
		LaunchCharacter((result.Location - GetActorLocation() + FVector(0,0,10)) * DeltaTime * 100, false, false);
	}
}


void AParkourCharacter::RefillStamania()
{
	if (Stamania >= 100) return;
	if (Stamania < 0) Stamania = 0;
	float time = GetWorld()->GetTimeSeconds();
	if (WaitForStamaina > time) return;
	float delta = GetWorld()->DeltaTimeSeconds;
	Stamania += delta * 60;
}
