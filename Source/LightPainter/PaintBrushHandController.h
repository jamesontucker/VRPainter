// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintBrushHandController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TriggerPressed() override;
	void TriggerReleased() override;

	UFUNCTION()
	void ChangeBrushColor(FLinearColor NewColor);

private:

	// State
	AStroke* CurrentStroke;

	// Config
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> StrokeClass;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Point;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Tip;

	UPROPERTY(VisibleAnywhere)
	FLinearColor VectorParameter = FLinearColor(0.730461f, 0.407240f, 1.0f);
	
};
