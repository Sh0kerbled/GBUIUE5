// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "InventoryCellWidget.h"
#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"


UInventoryManagerComponent::UInventoryManagerComponent()
{
	//
}

void UInventoryManagerComponent::Init(UInventoryComponent *
InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	if (LocalInventoryComponent && InventoryItemsData)
	{
		ensure(InventoryWidgetClass);
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));
		for (auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.ItemID);
			if (ItemData)
			{
				ItemData->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitLocalInventory(UInventoryComponent * InInventoryComponent)
{
	InventoryWidget->RepresentedInventory = LocalInventoryComponent;
	InventoryWidget->AddToViewport();
}

FInventoryItemInfo * UInventoryManagerComponent::GetItemData(FName ItemID)
{
	return InventoryItemsData ?
	InventoryItemsData->FindRow<FInventoryItemInfo>(ItemID, "") : nullptr;
}

void UInventoryManagerComponent::InitEquipment(UInventoryComponent * InInventoryComponent)
{
	ensure(EquipInventoryWidgetClass);
	EquipInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),
	EquipInventoryWidgetClass);
	EquipInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);
	EquipInventoryWidget->AddToViewport();
	EquipInventoryWidget->RepresentedInventory = InInventoryComponent;
    EquipInventoryWidget->AddToViewport();
}

void UInventoryManagerComponent::MoveItem(UInventoryCellWidget * FromCell,
UInventoryCellWidget * ToCell)
{
	if (!FromCell || !ToCell)
	{
		return;
	}
	UInventoryComponent * FromInventory = FromCell->ParentInventoryWidget->RepresentedInventory;
	UInventoryComponent * ToInventory = ToCell->ParentInventoryWidget->RepresentedInventory;
	if (!FromInventory || !ToInventory)
	{
		return;
	}

	FInventorySlotInfo ItemToDrop = Item;
	ItemToDrop.Amount = ToInventory->GetMaxItemAmount(ToCell->IndexInInventory,
	*ItemData);
	if (ItemToDrop.Amount == 0)
	{
		return;
	}
	if (ItemToDrop.Amount == -1)
	{
		ItemToDrop.Amount = Item.Amount;
	}
	Item.Amount -= ItemToDrop.Amount;
	FromCell->Clear();
	FromCell->AddItem(Item, *ItemData);
	ToCell->Clear();
	ToCell->AddItem(ItemToDrop, *ItemData);
	FromInventory->SetItem(FromCell->IndexInInventory, Item);
	ToInventory->SetItem(ToCell->IndexInInventory, ItemToDrop);
}
