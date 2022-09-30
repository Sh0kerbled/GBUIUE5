// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryComponents;
class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryManagerComponent();

	void Init(UInventoryComponents* InInventoryComponent);

	const FInventoryItemInfo* GetItemData(const FName& InID) const;

protected:

	UPROPERTY()
	UInventoryComponents* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
		UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
		int32 MinInventorySize = 20;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
		UInventoryWidget* InventoryWidget;

	void OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To);

};
