#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectLocation.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPPPROJTEST_API UObjectLocation : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UObjectLocation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	FVector GetDirectionToTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	float GetAngleToTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	bool IsTargetLeft(const FVector& TargetLocation);

private:
	AActor* ComponentOwnerActor;
};