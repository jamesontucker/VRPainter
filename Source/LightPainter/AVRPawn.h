// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "HandControllerBase.h"
#include "AVRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AAVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void RightTriggerPressed() { if (RightHandController) RightHandController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightHandController) RightHandController->TriggerReleased(); }

	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurrentPage(int32 Offset);

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.9;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY()
	AHandControllerBase* LeftHandController;

	// State
	int32 LastPaginationOffset = 0;

public:

	// Reference
	UPROPERTY()
		AHandControllerBase* RightHandController;

	auto GetRightHand() {
		return RightHandController;
	}
	
};
