// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "HAL/FileManager.h"
#include "saving/PainterSaveGame.h"


void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
	PaintingName = NewPaintingName;

	FString ImagePath = UPainterSaveGame::GetImagePath(PaintingName);
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		// TODO: Parameter for size
		FSlateDynamicImageBrush Brush(*ImagePath, FVector2D(1000, 1000), FLinearColor::White);
		Thumbnail->SetBrush(Brush);
	}

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName);
}