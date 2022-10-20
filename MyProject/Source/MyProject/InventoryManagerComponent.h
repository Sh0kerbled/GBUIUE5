// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "EquipInventoryComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryComponent;
class UInventoryWidget;
class UInventoryCellWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryManagerComponent();
	
	void Init(UInventoryComponent * InInventoryComponent);
	
	void InitLocalInventory(UInventoryComponent* InInventoryComponent);

	FInventoryItemInfo* GetItemData(FName ItemID);
	
	void InitEquipment(UInventoryComponent * InInventoryComponent);
	void MoveItem(UInventoryCellWidget* FromCell, UInventoryCellWidget* ToCell);

	FOnItemDrop OnItemDropped;

protected:
	
	UPROPERTY()
	UInventoryComponent * LocalInventoryComponent;
	
	UPROPERTY(EditAnywhere)
	UDataTable * InventoryItemsData;
	
	UPROPERTY()
	UInventoryWidget * InventoryWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	
	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 5;

	UPROPERTY()
	UInventoryWidget * EquipInventoryWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> EquipInventoryWidgetClass;
	
};
