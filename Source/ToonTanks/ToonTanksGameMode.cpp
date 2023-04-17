// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TargetTowers = GetTowerCount();
	StartGame();
	if (TankPlayerController) {
		TankPlayerController->SetPlayerEnabledState(false);
		FTimerHandle TimerHandle;
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(TimerHandle, InputDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	ABasePawn* BasePawn = Cast<ABasePawn>(DeadActor);
	if (BasePawn) {
		BasePawn->HandleDestruction();
	}
	if (Cast<ATank>(DeadActor)) {
		GameOver(false);
	}
	else if (Cast<ATower>(DeadActor)) {
		if (--TargetTowers == 0) {
			GameOver(true);
		}
	}
}