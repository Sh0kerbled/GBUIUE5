// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API IInventoryCharacterInterface
{
	GENERATED_BODY()

public:
	virtual void EquipItem(EEquipSlot Slot, FName ItemID) {}
	virtual void UnequipItem(EEquipSlot Slot, FName ItemID) {}
};
