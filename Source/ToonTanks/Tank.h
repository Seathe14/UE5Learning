// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AToonTanksPlayerController;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

	AToonTanksPlayerController* GetTankPlayerController() const { return TankPlayerController; }
	bool GetAlive() const { return bAlive; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Movement");
	float Speed = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Movement");
	float TurnRate = 40.0f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float Value);
	void Turn(float Value);
	void Rotate(float Value);

	AToonTanksPlayerController* TankPlayerController;
	bool bAlive = true;
};
