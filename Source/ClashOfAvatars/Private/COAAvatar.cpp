// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
		
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	RunSpeed = 600.0f;

	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	StaminaDrainRate = 20.0f;
	StaminaGainRate = 15.0f;
	bStaminaDrained = false;
	bRunning = false;
}


// Called to bind functionality to input
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);
}

void ACOAAvatar::MoveForward(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACOAAvatar::MoveRight(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACOAAvatar::RunPressed()
{
    if (bStaminaDrained || Stamina <= 0.0f)
        return;

    bRunning = true;
    UpdateMovementParams();
}

void ACOAAvatar::RunReleased()
{
    bRunning = false;
    UpdateMovementParams();
}






void ACOAAvatar::UpdateMovementParams()
{
    if (bRunning && !bStaminaDrained)
    {
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

void ACOAAvatar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
    {
        if (bRunning && !bStaminaDrained)
        {
            Stamina -= StaminaDrainRate * DeltaTime;

            if (Stamina <= 0.0f)
            {
                Stamina = 0.0f;
                bStaminaDrained = true;
                bRunning = false;
            }
        }
        else
        {
            Stamina += StaminaGainRate * DeltaTime;

            if (Stamina >= MaxStamina)
            {
                Stamina = MaxStamina;
                bStaminaDrained = false;
            }
        }
    }

    UpdateMovementParams();
}