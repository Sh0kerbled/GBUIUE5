// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMetaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMetaPlayerController();

	FSimpleMulticastDelegate OnMouseButtonUp;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void OnLeftMouseButtonUp();
};
