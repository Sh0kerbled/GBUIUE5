// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"

UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::ES_Head);
	EquipSlots.Add(1, EEquipSlot::ES_Body);
	EquipSlots.Add(2, EEquipSlot::ES_Hands);
	EquipSlots.Add(3, EEquipSlot::ES_MainHand);
	EquipSlots.Add(4, EEquipSlot::ES_OffHand);
	EquipSlots.Add(5, EEquipSlot::ES_Legs);
	EquipSlots.Add(6, EEquipSlot::ES_Misc);
	EquipSlots.Add(7, EEquipSlot::ES_Misc);
}
int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex,
const FInventoryItemInfo& Item)
{
	if (Item.Type != EItemType::IT_Equipment ||
	!EquipSlots.Contains(SlotIndex) ||
	EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot)
	{
		return 0;
	}
	return 1;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex,const FInventorySlotInfo& Item)
{
	FInventorySlotInfo * EquippedItem = GetItem(SlotIndex);
	EEquipSlot EquipSlot = EquipSlots.Contains(SlotIndex) ?
	EquipSlots.FindChecked(SlotIndex) : EEquipSlot::ES_None;
	if (EquippedItem && InventoryCharacter)
	{
		InventoryCharacter->UnequipItem(EquipSlot, EquippedItem->ItemID);
	}
	Super::SetItem(SlotIndex, Item);
	if (InventoryCharacter)
	{
		InventoryCharacter->EquipItem(EquipSlot, Item.ItemID);
	}
}