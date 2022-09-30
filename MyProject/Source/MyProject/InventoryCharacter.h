// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponents.h"
#include "GameFramework/Character.h"
#include "InventoryCharacter.generated.h"

class UInventoryComponent;
class UInventoryManagerComponent;

UCLASS()
class MYPROJECT_API AInventoryCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UInventoryComponents* LocalInventory;

	UPROPERTY(EditDefaultsOnly)
	UInventoryComponents* InventoryManager;
};
