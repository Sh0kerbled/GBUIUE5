// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellsWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UInventoryCellsWidget::AddItem(const FInventoryItemSlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if(bHasItem)
	{
		return false;
	}

	if(ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
	}
	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}

	bHasItem = true;
	Item = InSlot;

	return true;
}

void UInventoryCellsWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if(ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	if(CountText)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	bHasItem = false;
}

FReply UInventoryCellsWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UInventoryCellsWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	if(OutOperation)
	{
		OutOperation->DefaultDragVisual = this;
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UInventoryCellsWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual && InOperation->DefaultDragVisual != this)
	{
		if (auto* FromCell = Cast<UInventoryCellsWidget>(InOperation->DefaultDragVisual))
		{
			OnItemDrop.Broadcast(FromCell, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
