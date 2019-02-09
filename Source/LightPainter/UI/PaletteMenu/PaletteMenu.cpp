// Fill out your copyright notice in the Description page of Project Settings.

#include "PaletteMenu.h"
#include "GameFramework/PlayerController.h"
#include "AVRPawn.h"
#include "PaintBrushHandController.h"

bool UPaletteMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	SetupColorSelectionButtons();

	return true;
}

void UPaletteMenu::UpdateStrokeColor(FLinearColor ColorSelection)
{
	AAVRPawn* VRPawn = Cast<AAVRPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (VRPawn == nullptr) { return; }

	APaintBrushHandController* PaintBrush = Cast<APaintBrushHandController>(VRPawn->GetRightHand());
	if (PaintBrush == nullptr) { return; }

	PaintBrush->ChangeBrushColor(ColorSelection);
}

bool UPaletteMenu::SetupColorSelectionButtons()
{
	if (!Color_BlackButton) return false;
	Color_BlackButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorBlackSelected);

	if (!Color_BlueButton) return false;
	Color_BlueButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorBlueSelected);

	if (!Color_GreenButton) return false;
	Color_GreenButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorGreenSelected);

	if (!Color_PinkButton) return false;
	Color_PinkButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorPinkSelected);

	if (!Color_PurpleButton) return false;
	Color_PurpleButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorPurpleSelected);

	if (!Color_YellowButton) return false;
	Color_YellowButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorYellowSelected);

	if (!Color_WhiteButton) return false;
	Color_WhiteButton->OnReleased.AddDynamic(this, &UPaletteMenu::ColorWhiteSelected);

	return true;
}