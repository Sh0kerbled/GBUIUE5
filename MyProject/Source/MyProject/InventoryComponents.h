// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCharacter.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponents.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryComponents : public UActorComponent
{
	GENERATED_BODY()

public:

	const FInventoryItemInfo* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); }

	virtual void SetItem(int32 SlotIndex, const FInventoryItemInfo& Item);

	virtual void ClrearItem(int32 SlotIndex);

	FORCEINLINE const TMap<int32, FInventoryItemInfo>& GetItems() const { return Items; }

	FORCEINLINE int32 GetItemSum() const { return Items.Num(); }

	void Init(UInventoryComponents* LocalInventory);

protected:

	UPROPERTY(EditAnywhere)
		TMap<int32, FInventoryItemInfo> Items;

};
