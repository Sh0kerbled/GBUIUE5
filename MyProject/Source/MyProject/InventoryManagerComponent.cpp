// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "InventoryCharacter.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryManagerComponent::Init(UInventoryComponents* InInventoryComponent)
{
	if(LocalInventoryComponent && ItemsData && InventoryWidgetClass)
	{
		LocalInventoryComponent = InInventoryComponent;

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();

		InventoryWidget->Init(FMath::Max(MinInventorySize, LocalInventoryComponent->GetItemsNum));
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		for(const auto* [SlotIndex,SlotInfo] : LocalInventoryComponent->GetItems())
		{
			if (auto* Data = GetItemData(SlotInfo.Id))
			{
				InventoryWidget->AddItem(SlotInfo, *Data, SlotIndex);
			}
		}
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID, "") : nullptr;
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To)
{
	FInventoryItemInfo FromItem = From->GetItem();
	FInventoryItemInfo ToItem = To->GetItem();

	From->Clear();
	To->Clear();

	To->AddItem(FromItem, *GetItemData(FromItem.Id));

	if (!ToItem.Id.IsNone())
	{
		From->AddItem, * GetItemData(ToItem.Id);
	}
}

