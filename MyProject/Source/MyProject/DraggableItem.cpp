// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"

#include "MetaDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(MetaText)
	{
		MetaText->SetText(FText::FromString(MetaName));
	}

}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(Cast<UVerticalBox>(GetParent())&&InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UMetaDragDropOperation::StaticClass());
	UMetaDragDropOperation* MetaOperation = Cast<UMetaDragDropOperation>(OutOperation);

	if(MetaOperation)
	{
		MetaOperation->DefaultDragVisual = this;

		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		MetaOperation->OnDragCancelled.AddDynamic(this, &ThisClass::RestoreVisuals);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UVerticalBox* VerticalBox = Cast<UVerticalBox>(GetParent());
	UMetaDragDropOperation* MetaOperation = Cast<UMetaDragDropOperation>(InOperation);

	if (VerticalBox && MetaOperation && MetaOperation->DefaultDragVisual && this != MetaOperation->DefaultDragVisual)
	{
		const int32 OverIndex = VerticalBox->GetChildIndex(MetaOperation->DefaultDragVisual);

		if (OverIndex >= 0)
		{
			VerticalBox->RemoveChildAt(OverIndex);

			const TArray<UWidget*> Children = VerticalBox->GetAllChildren();
			VerticalBox->ClearChildren();

			for (int32 i = 0; i < Children.Num(); i++)
			{
				VerticalBox->AddChildToVerticalBox(Children[i])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

				if(Children[i] == this)
				{
					VerticalBox->AddChildToVerticalBox(MetaOperation->DefaultDragVisual)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				}
			}

			return true;
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if(InOperation && InOperation->DefaultDragVisual)
	{
		RestoreVisuals(InOperation);
		return true;
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDraggableItem::RestoreVisuals(UDragDropOperation* Operation)
{
	if(UDraggableItem* Item = Cast<UDraggableItem>(Operation->DefaultDragVisual))
	{
		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		SetVisibility(ESlateVisibility::Visible);
	}
}




