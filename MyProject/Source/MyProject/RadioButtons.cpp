// Fill out your copyright notice in the Description page of Project Settings.
#include "RadioButtons.h" 
#include "SRadioButtons.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	RadioButtons.Reset();
}
TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	RadioButtons = SNew(SRadioButtons)
		.Count_UObject(this, &ThisClass::GetCount)
		.Style(&WidgetStyle);
	//.OnCheckStateChanged_UObject(this, &ThisClass ,HandleOnRadioChoiceChanged);

	return RadioButtons.ToSharedRef();

}




void URadioButtons::HandleOnRadioChoiceChanged(int32 NewRadioChoise) const
{
	if (OnRadioChoiceChanged.IsBound())
	{
		OnRadioChoiceChanged.Broadcast(NewRadioChoise);
	}
}