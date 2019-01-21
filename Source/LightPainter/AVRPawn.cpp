// Fill out your copyright notice in the Description page of Project Settings.

#include "AVRPawn.h"
#include "Engine/World.h"
#include "Saving/PainterSaveGame.h"

// Sets default values
AAVRPawn::AAVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}

// Called when the game starts or when spawned
void AAVRPawn::BeginPlay()
{
	Super::BeginPlay();

	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	if (Painting && Painting->Save())
	{
		CurrentSlotName = Painting->GetSlotName();
	}

	if (PaintBrushHandControllerClass)
	{
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

// Called every frame
void AAVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AAVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AAVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AAVRPawn::Save);
	PlayerInputComponent->BindAction(TEXT("Load"), EInputEvent::IE_Released, this, &AAVRPawn::Load);
}

void AAVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->SetState("Hello World!");
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void AAVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Painting State %s"), *Painting->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found"));
	}
}