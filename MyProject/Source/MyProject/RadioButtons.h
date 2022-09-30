// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtonsWidgetStyle.h"
#include "Components/Widget.h"
#include "RadioButtons.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioChoiceChangedEvent, int32, NewRadioChoise);

class SRadioButtons;

UCLASS()
class MYPROJECT_API URadioButtons : public UWidget
{
	GENERATED_BODY()

public:

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(BlueprintAssignable, Category = "RadioButtons|Event")
		FOnRadioChoiceChangedEvent OnRadioChoiceChanged;

	UPROPERTY(EditAnyWhere)
		int32 Count;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FRadioButtonsStyle WidgetStyle;


protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	int32 GetCount() const { return Count; }

	TSharedPtr<SRadioButtons> RadioButtons;

	void HandleOnRadioChoiceChanged(int32 NewRadioChoise) const;
};
