// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "InventoryCellWidget.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryCellWidget;

UCLASS(Abstract)
class MYPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;
	
	void Init(int32 ItemsNum);
	
	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo,
		
	int32 SlotPosition = -1);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
    class UInventoryComponent * RepresentedInventory;

protected:
	
	UPROPERTY(meta = (BindWidgetOptional))
	UUniformGridPanel* ItemCellsGrid;
	
	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInPow = 5;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;
	
	UPROPERTY()
	TArray<UInventoryCellWidget*> CellWidgets;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UInventoryCellWidget* GoldCell;
	
	UInventoryCellWidget * CreateCellWidget();
	void InitCellWidget(UInventoryCellWidget* Widget);

	void OnItemDropped(UInventoryCellWidget * DraggedFrom, UInventoryCellWidget * DroppedTo);
	
};
