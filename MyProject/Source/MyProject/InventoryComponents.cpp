


#include "InventoryComponents.h"

void UInventoryComponents::SetItem(int32 SlotIndex, const FInventoryItemInfo& Item)
{
	//ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponents::ClrearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}
