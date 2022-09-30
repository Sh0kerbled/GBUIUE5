// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "InventoryComponents.h"
#include "InventoryManagerComponent.h"

// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory = CreateDefaultSubobject<UInventoryComponents>("LocalInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryComponents>("InventoryManager");
}

// Called when the game starts or when spawned
void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryManager->Init(LocalInventory);
}

