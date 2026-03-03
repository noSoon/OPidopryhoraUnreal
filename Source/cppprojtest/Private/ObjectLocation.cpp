#include "ObjectLocation.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UObjectLocation::UObjectLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObjectLocation::BeginPlay()
{
	Super::BeginPlay();

	ComponentOwnerActor = GetOwner();
}

// Called every frame
void UObjectLocation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
FVector UObjectLocation::GetDirectionToTarget(const FVector& TargetLocation){
	if (!ComponentOwnerActor) { return FVector::ZeroVector; }
	FVector OwnerLocation = ComponentOwnerActor->GetActorLocation();
	FVector TargetDirection = OwnerLocation - TargetLocation;
	return TargetDirection.GetSafeNormal();
}

float UObjectLocation::GetAngleToTarget(const FVector& TargetLocation){
	if (!ComponentOwnerActor) { return 0.f; }
	FVector DirectionToTarget = GetDirectionToTarget(TargetLocation);
	FVector ActorForwardVector = ComponentOwnerActor->GetActorForwardVector();
	float DotProduct = FVector::DotProduct(ActorForwardVector, DirectionToTarget);
	return FMath::Acos(DotProduct) * (180.f / PI);
}

bool UObjectLocation::IsTargetLeft(const FVector& TargetLocation){
	if (!ComponentOwnerActor) { return false; }
	FVector ActorLocation = ComponentOwnerActor->GetActorLocation();
	FVector DirectionToTarget = GetDirectionToTarget(TargetLocation);
	FVector ActorForwardVector = ComponentOwnerActor->GetActorForwardVector();
	FVector CrossProduct = FVector::CrossProduct(ActorForwardVector, DirectionToTarget);
	return CrossProduct.Z > 0;
}