// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"

#include "Camera/Cameracomponent.h"
#include "Gameframework/SpringArmComponent.h"

#include "COAAvatar.generated.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.7/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h"

/**
 * 
 */
UCLASS()
class CLASHOFAVATARS_API ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()
public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	UCameraComponent* Camera;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();
public:
	virtual void Tick(float DeltaTime) override;
	void UpdateMovementParams();

};
