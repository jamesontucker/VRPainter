// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Stroke.h"
#include "PaletteMenu.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaletteMenu : public UUserWidget
{
	GENERATED_BODY()


public:

	bool Initialize() override;
	
protected:

	//Color buttons

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_BlackButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_BlueButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_GreenButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_PinkButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_PurpleButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_YellowButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* Color_WhiteButton;

private:

	void UpdateStrokeColor(FLinearColor ColorSelection);

	bool SetupColorSelectionButtons();

	//Color button released functions

	UFUNCTION()
	void ColorBlackSelected() { UpdateStrokeColor(ColorBlack); };

	UFUNCTION()
	void ColorBlueSelected() { UpdateStrokeColor(ColorBlue); };

	UFUNCTION()
	void ColorGreenSelected() { UpdateStrokeColor(ColorGreen); };

	UFUNCTION()
	void ColorPinkSelected() { UpdateStrokeColor(ColorPink); };

	UFUNCTION()
	void ColorPurpleSelected() { UpdateStrokeColor(ColorPurple); };

	UFUNCTION()
	void ColorYellowSelected() { UpdateStrokeColor(ColorYellow); };

	UFUNCTION()
	void ColorWhiteSelected() { UpdateStrokeColor(ColorWhite); };


	//Colors

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorBlack = FLinearColor(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorBlue = FLinearColor(0.003922f, 0.803922f, 0.996078f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorGreen = FLinearColor(0.019608f, 1.0f, 0.631373f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorPink = FLinearColor(1.0f, 0.443137f, 0.807843f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorPurple = FLinearColor(0.730461f, 0.40724f, 1.0f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorYellow = FLinearColor(1.0f, 0.984314f, 0.588235f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ColorWhite = FLinearColor(1.0f, 1.0f, 1.0f);


};
