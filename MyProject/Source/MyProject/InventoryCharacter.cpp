// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryCharacter.h"
#include "InventoryComponent.h"
#include "EquipInventoryComponent.h"
#include "InventoryManagerComponent.h"

// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	EquipmentInventoryComponent = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
}

void AInventoryCharacter::EquipItem(EEquipSlot Slot, FName ItemID)
{
	UStaticMeshComponent * EquipComponent = GetEquipComponent(Slot);
	if (EquipComponent)
	{
		FInventoryItemInfo * ItemInfoPtr =
		InventoryManagerComponent->GetItemData(ItemID);
		if (ItemInfoPtr)
		{
			EquipComponent->SetStaticMesh(ItemInfoPtr->Mesh.LoadSynchronous());
			DamageStat += ItemInfoPtr->Damage;
			ArmorStat += ItemInfoPtr->Armor;
			IntelligenceStat += ItemInfoPtr->Intelligence;
		}
	}
}
void AInventoryCharacter::UnequipItem(EEquipSlot Slot, FName ItemID)
{
	UStaticMeshComponent * EquipComponent = GetEquipComponent(Slot);
	if (EquipComponent)
	{
		EquipComponent->SetStaticMesh(nullptr);
		FInventoryItemInfo * ItemInfoPtr =
		InventoryManagerComponent->GetItemData(ItemID);
		if (ItemInfoPtr)
		{
			DamageStat -= ItemInfoPtr->Damage;
			ArmorStat -= ItemInfoPtr->Armor;
			IntelligenceStat -= ItemInfoPtr->Intelligence;
		}
	}
}
UStaticMeshComponent * AInventoryCharacter::GetEquipComponent(EEquipSlot Slot)
{
	FName EquipTag = "";
	switch (Slot)
	{
	case EEquipSlot::ES_None:
		break;
	case EEquipSlot::ES_Head:
		EquipTag = "Equip_Head";
		break;
	case EEquipSlot::ES_Body:
		EquipTag = "Equip_Body";
		break;
	case EEquipSlot::ES_Hands:
		EquipTag = "Equip_Hands";
		break;
	case EEquipSlot::ES_MainHand:
		EquipTag = "Equip_MainHand";
		break;
	case EEquipSlot::ES_OffHand:
		EquipTag = "Equip_OffHand";
		break;
	case EEquipSlot::ES_Legs:
		EquipTag = "Equip_Legs";
		break;
	case EEquipSlot::ES_Misc:
		EquipTag = "Equip_Misc";
		break;
	default:
		break;
	}
	TArray<UActorComponent*> Components =GetComponentsByTag(UStaticMeshComponent::StaticClass(), EquipTag);
	return Components.Num() > 0 ?
	Cast<UStaticMeshComponent>(Components[0]) : nullptr;
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryManagerComponent->Init(InventoryComponent);
	InventoryManagerComponent->InitLocalInventory(InventoryComponent);
    InventoryManagerComponent->InitEquipment(EquipmentInventoryComponent);

}


