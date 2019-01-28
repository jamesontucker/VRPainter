// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "PaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetPaintingName(FString NewPaintingName);
	
protected:

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UButton* CardButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UImage* Thumbnail;

private:

	UFUNCTION()
	void CardButtonClicked();
	
	// State
	FString PaintingName;
};
