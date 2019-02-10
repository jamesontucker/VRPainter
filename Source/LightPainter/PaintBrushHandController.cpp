// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintBrushHandController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"


// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	Point = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point"));
	Point->SetupAttachment(GetRootComponent());

	Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tip"));
	Tip->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();

	if (PointerMaterial != nullptr) {
		DynPointerMaterial = UMaterialInstanceDynamic::Create(PointerMaterial, this);
		Point->SetMaterial(0, DynPointerMaterial);
	}
	
}

// Called every frame
void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		CurrentStroke->Update(Tip->GetComponentLocation());
	}

}

void APaintBrushHandController::TriggerPressed()
{
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
	CurrentStroke->SetActorLocation(Tip->GetComponentLocation());
	CurrentStroke->UpdatePaintingMaterial(StrokeColor);
	
}

void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}


void APaintBrushHandController::ChangeBrushColor(FLinearColor NewColor)
{
	StrokeColor = NewColor;
	UpdatePointerMaterial(StrokeColor);
}

void APaintBrushHandController::UpdatePointerMaterial(FLinearColor NewColor)
{
	if (DynPointerMaterial != NULL) {
		DynPointerMaterial->SetVectorParameterValue(PointerColorParam, NewColor);
	}
}