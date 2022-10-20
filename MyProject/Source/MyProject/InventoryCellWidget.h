// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCellWidget.generated.h"

class UInventoryManagerComponent;
class UImage;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget * /*DraggedFrom*/, UInventoryCellWidget * /*DroppedTo*/);

UCLASS(Abstract)
class MYPROJECT_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	bool HasItem() { return bHasItem; }
	
	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo);
	
	/*void Clear();*/

	const FInventorySlotInfo& GetItem();
	
    int32 IndexInInventory = -1;

	FOnItemDrop OnItemDrop;
	
protected:
	
	bool bHasItem;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* ItemImage;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CountText;
	
	UPROPERTY()
	FInventorySlotInfo StoredItem;
	
    UPROPERTY(EditDefaultsOnly)
    bool bIsDraggable = true;
};

