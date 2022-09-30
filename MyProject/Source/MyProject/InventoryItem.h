// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItem.generated.h"
/**
 * 
 */
class MYPROJECT_API InventoryItem
{
public:
	InventoryItem();
	~InventoryItem();
};

UENUM()
enum class EItemType : uint8
{
	It_Misc,
	It_Currency,
	It_Equip,
	It_Consumable,
};

UENUM()
enum class EItemRarity : uint8
{
	IR_Common,
	IR_Rare,
	IR_Epic,
};

class UInventoryCellsWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellsWidget*, UInventoryCellsWidget*)

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "General")
		FName Id;

	UPROPERTY(EditAnywhere, Category = "General")
		FText Name;

	UPROPERTY(EditAnywhere, Category = "Type")
		EItemType Type;

	UPROPERTY(EditAnywhere, Category = "Type")
		EItemType Rare;

	UPROPERTY(EditAnywhere, Category = "Visual")
		TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Visual")
		TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Damage;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Armor;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 Intelligence;
};

USTRUCT(BlueprintType)
struct FInventoryItemSlotInfo //FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName Id = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Count;
};