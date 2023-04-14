// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	ABasePawn* BasePawn = Cast<ABasePawn>(DeadActor);
	if (BasePawn) {
		BasePawn->HandleDestruction();
	}
}