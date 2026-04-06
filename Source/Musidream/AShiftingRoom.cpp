// Fill out your copyright notice in the Description page of Project Settings.


#include "AShiftingRoom.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AAShiftingRoom::AAShiftingRoom()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	EntryToLock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntryToLock"));
	EntryToLock->SetupAttachment(RootComponent);

	LockToExit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockToExit"));
	LockToExit->SetupAttachment(RootComponent);

	WallEntry = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallEntry"));
	WallEntry->SetupAttachment(RootComponent);
	WallEntry->SetVisibility(false);
	WallEntry->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DoorExit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorExit"));
	DoorExit->SetupAttachment(RootComponent);
	DoorExit->SetVisibility(false);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Trigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAShiftingRoom::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAShiftingRoom::OnTriggerBeginOverlap);
	
}

void AAShiftingRoom::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (Cast<ACharacter>(OtherActor) && OverlappedComp == Trigger)
	{
		SetActorTickEnabled(true);
		Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

// Called every frame
void AAShiftingRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!Player) { return; }

	EntryDirVector = EntryToLock->GetComponentLocation() - Player->GetActorLocation();
	EntryDirVector.Normalize();

	DotEntryCamera = FVector::DotProduct(EntryDirVector, Player->GetActorForwardVector());

	UE_LOG(LogTemp, Warning, TEXT("Dot: %f, entryTransformed: %d"), DotEntryCamera, entryTransformed);

	if (DotEntryCamera <= 0.2f && !entryTransformed) {
		WallEntry->SetVisibility(true);
		WallEntry->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		EntryToLock->SetVisibility(false);
		entryTransformed = true;
	}
	else {
		if (entryTransformed) {
			if (DotEntryCamera >= 0.75f) {
				LockToExit->SetVisibility(false);
				LockToExit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				DoorExit->SetVisibility(true);
				SetActorTickEnabled(false);
			}
		}
	}
}

