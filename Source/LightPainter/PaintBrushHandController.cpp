// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintBrushHandController.h"

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
	CurrentStroke->UpdatePaintingMaterial(VectorParameter);
	CurrentStroke->SetActorLocation(Tip->GetComponentLocation());
}

void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}


void APaintBrushHandController::ChangeBrushColor(FLinearColor NewColor)
{
	VectorParameter = NewColor;
}