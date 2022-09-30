// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SRadioButtons.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

class SButton;
class UNativeWidgetHost;	

UCLASS()
class MYPROJECT_API UMainMenuWidget : public UUserWidget
{
public:
	virtual void NativeConstruct() override;
	void DoAnyInitialization();

	/*virtual void NativeDestruct() override;*/
protected:
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidgetOptional))
		UButton* NewGameBtn;

		UPROPERTY(meta = (BindWidgetOptional))
		UButton* QuitBtn;

		UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
			UWidgetAnimation* NewGameAnimation;

		UFUNCTION()
		void OnNewGameClicked();

		UFUNCTION()
		void QuitClicked();

		UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UNativeWidgetHost* RadioButtonsHost;

};
