// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryCellsWidget;
class UUniformGridPanel;

UCLASS()
class MYPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventoryItemInfo& Info, const FInventoryItemSlotInfo& InSlot, int32 SlotIndex);

	FOntItemDrop OnItemDrop;

protected:

	UPROPERTY(EditDefaultsOnly)
		int32 ItemsInRaw = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellsWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly,Meta = (BindWidget))
	UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly,Meta = (BindWidget))
		UUniformGridPanel* GoldCells;

	UPROPERTY()
		TArray<UInventoryCellsWidget*> CellWidgets;

	UInventoryCellsWidget* CreateCell();

	void OnItemdropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To);
};
