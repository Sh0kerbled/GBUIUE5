// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaPlayerController.h"
#include "ActorSpawnerWidget.h"

AMetaPlayerController::AMetaPlayerController()
{

	PrimaryActorTick.bCanEverTick = true;
}

void AMetaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMetaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bEnableClickEvents = true;
}

void AMetaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(InputComponent)
	{
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);
	}
}

void AMetaPlayerController::OnLeftMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

