// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventoryCellsWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS(Abstract)
class MYPROJECT_API UInventoryCellsWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	FORCEINLINE bool HasItem() const { return bHasItem; }

	bool AddItem(const FInventoryItemInfo& InSlot, const FInventoryItemSlotInfo& Info);

	bool AddItem(const FInventoryItemSlotInfo& InSlot, const FInventoryItemInfo& Info);
	void Clear();

	FORCEINLINE const FInventoryItemInfo& GetItem() const { return Item; }

	int32 IndexInInventory = INDEX_NONE;

	FOnItemDrop OnItemDrop;

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:

	UPROPERTY(EditAnywhere)
		bool bCanDrag = true;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UTextBlock* CountText;

	bool bHasItem;

	UPROPERTY()
		FInventoryItemInfo Item;
};
