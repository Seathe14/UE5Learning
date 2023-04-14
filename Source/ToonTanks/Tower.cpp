// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::CheckFireCondition, 2.f, true);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (HasTarget()) {
		Fire();
	}
}

bool ATower::HasTarget()
{
	return Tank && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasTarget()) {
		RotateTurret(Tank->GetActorLocation());
	}
}
