// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AShiftingRoom.generated.h"

UCLASS()
class MUSIDREAM_API AAShiftingRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	AAShiftingRoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes")
	UStaticMeshComponent* EntryToLock; // Entry that changes to WallEntry
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes")
	UStaticMeshComponent* LockToExit; // Wall that changes to DoorExit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes")
	UStaticMeshComponent* WallEntry; // Wall that appears in the place of EntryToLock

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes")
	UStaticMeshComponent* DoorExit; // Door that appears in the place of LockToExit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CollisionTrigger")
	UBoxComponent* Trigger; // Trigger to calculate vectors in tick

private:
	bool entryTransformed = false;
	float DotEntryCamera;
	FVector EntryDirVector;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
