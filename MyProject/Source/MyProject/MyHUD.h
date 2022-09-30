// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	MainMenu = 0x0,
	PauseMenu = 0x1,
};
UCLASS()
class MYPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClases;

	UPROPERTY()
		UUserWidget* CurrentWidget;
	EWidgetID CurrentWidgetID;

public:
	void BeginPlay() override;
	UUserWidget* UseWidget(EWidgetID widgetID, bool RemovePrevious = true,
		int32 ZOrder = 0);
	UUserWidget* GetCurrentWidget();

	void RemoveCurrentWidgetFromViewport();
	UUserWidget* AddWidgetToViewportByClass(
		TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);
};
