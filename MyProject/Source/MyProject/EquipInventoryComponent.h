// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "EquipInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	
    UEquipInventoryComponent();
	
    int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) override;
	void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

protected:
	
    UPROPERTY(EditAnywhere)
    TMap<int32, EEquipSlot> EquipSlots;
};
