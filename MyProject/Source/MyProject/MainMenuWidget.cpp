// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "SRadioButtons.h"
#include "Components/NativeWidgetHost.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (NewGameBtn)
	{
		NewGameBtn->OnClicked.AddDynamic(this,&ThisClass::OnNewGameClicked);
	}

	if (QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &ThisClass::QuitClicked);
	}

	if (RadioButtonsHost)
	{
		RadioButtonsHost->SetContent(SNew(SRadioButtons).Count(10));
	}
}

void UMainMenuWidget::OnNewGameClicked()
{
	if(NewGameAnimation)
	{
		PlayAnimation(NewGameAnimation);
	}
} 

void UMainMenuWidget::QuitClicked()
{
	GEngine->Exec(GetWorld(), TEXT("EXIT"));
}