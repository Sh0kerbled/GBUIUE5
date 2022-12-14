// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (UInventoryCellWidget* CellWidget : CellWidgets)
    {
		InitCellWidget(CellWidget);
    }
}

void UInventoryWidget::Init(int32 ItemsNum)
{
	if (ItemCellsGrid)
	{
		ItemCellsGrid->ClearChildren();
		for (int32 i = 0; i < ItemsNum; i++)
		{
			UInventoryCellWidget * Widget = CreateCellWidget();
			Widget->IndexInInventory = i;
			ItemCellsGrid->AddChildToUniformGrid(Widget,
			i / ItemsInPow, i % ItemsInPow);
		}
	}
}
UInventoryCellWidget * UInventoryWidget::CreateCellWidget()
{
	if (CellWidgetClass)
	{
		UInventoryCellWidget * CellWidget = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(CellWidget);
		CellWidget->OnItemDrop.AddUObject(this,&UInventoryWidget::OnItemDropped);
		InitCellWidget(CellWidget);
		return CellWidget;

	}
	return nullptr;
}

void UInventoryWidget::InitCellWidget(UInventoryCellWidget * Widget)
{
	if (Widget)
	{
		Widget->OnItemDrop.AddUObject(this, &UInventoryWidget::OnItemDropped);
		Widget->ParentInventoryWidget = this;
	}
}

void UInventoryWidget::OnItemDropped(UInventoryCellWidget * DraggedFrom, UInventoryCellWidget * DroppedTo)
{
	if (OnItemDrop.IsBound())
	{
		OnItemDrop.Broadcast(DraggedFrom, DroppedTo);
	}
}


bool UInventoryWidget::AddItem(const FInventorySlotInfo & Item,
const FInventoryItemInfo& ItemInfo, int32 SlotPosition)
{
	if (ItemInfo.Type == EItemType::IT_Currency)
	{
		if (GoldCell)
		{
			return GoldCell->AddItem(Item, ItemInfo);
		}
		return false;
	}
	if (ItemCellsGrid)
	{
		UInventoryCellWidget * WidgetToAddItem = nullptr;
		UInventoryCellWidget ** WidgetToAddItemPtr =
		CellWidgets.FindByPredicate([SlotPosition](UInventoryCellWidget * Widget)
		{
		return Widget && Widget->IndexInInventory == SlotPosition;
		});
		if (WidgetToAddItemPtr)
		{
			WidgetToAddItem = *WidgetToAddItemPtr;
		}
		else
		{
			for (UInventoryCellWidget * CellWidget : CellWidgets)
			{
				if (!CellWidget->HasItem())
				{
					WidgetToAddItem = CellWidget;
					break;
				}
			}
		}
		if (WidgetToAddItem)
		{
			return WidgetToAddItem->AddItem(Item, ItemInfo);
		}
	}
	return false;
}
