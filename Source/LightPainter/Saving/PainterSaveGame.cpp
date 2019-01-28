// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "PainterSaveGameIndex.h"
#include "Stroke.h"
#include "HAL/FileManager.h"
#include "Paths.h"
#include "saving/SnapshotCamera.h"

UPainterSaveGame * UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr;

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();
	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame * UPainterSaveGame::Load(FString SlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld * World)
{
	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
	TakeScreenshot(World);
}

void UPainterSaveGame::DeserializeToWorld(UWorld * World)
{
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld * World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}

void UPainterSaveGame::TakeScreenshot(UWorld * World)
{
	for (TActorIterator<ASnapshotCamera> SnapshotCamera(World); SnapshotCamera; ++SnapshotCamera)
	{
		FString ThumbnailDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Thumbs"));
		IFileManager::Get().MakeDirectory(*ThumbnailDir, true);
		FString FileName = SlotName + ".png";

		SnapshotCamera->CaptureScreenshot(ThumbnailDir, FileName);
		break; // Only snapshot the first camera in a scene.
	}
}

FString UPainterSaveGame::GetImagePath(const FString & SlotName)
{
	FString ThumbnailDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Thumbs"));
	FString FileName = SlotName + ".png";

	return FPaths::Combine(ThumbnailDir, FileName);
}