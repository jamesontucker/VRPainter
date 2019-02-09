#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Saving/PainterSaveGame.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()

public:
	AStroke();

	void Update(FVector CursorLocation);
	FStrokeState SerializeToStruct() const;
	static AStroke* SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState);

	UPROPERTY(EditAnywhere)
	UMaterialInterface* PaintMaterial;

	UFUNCTION()
	void UpdatePaintingMaterial(FLinearColor VectorParameter);

protected:

	virtual void BeginPlay() override;

private:

	FTransform GetNextSegmentTransform(FVector CurrentLocation) const;
	FTransform GetNextJointTransform(FVector CurrentLocation) const;
	FVector GetNextSegmentScale(FVector CurrentLocation) const;
	FQuat GetNextSegmentRotation(FVector CurrentLocation) const;
	FVector GetNextSegmentLocation(FVector CurrentLocation) const;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* StrokeMeshes;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* JointMeshes;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY(VisibleAnywhere)
	FName VectorParameterName = FName(TEXT("Color"));

	void SetPaintingMaterial(UMaterialInstanceDynamic *Material);

	// State
	FVector PreviousCursorLocation;
	TArray<FVector> ControlPoints;

};