// Copyright Ivan Tsarkov Rockdevels


#include "Player/NinjaController.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/NinjaCharacter.h"
#include "GameFramework/Character.h"

ANinjaController::ANinjaController()
{
}

void ANinjaController::BeginPlay()
{
	Super::BeginPlay();

	check(NinjaContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(NinjaContext, 0);
}

void ANinjaController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANinjaController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANinjaController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ANinjaController::Jump);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ANinjaController::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ANinjaController::Attack);
	}
}

void ANinjaController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ANinjaController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y);
		ControlledPawn->AddControllerYawInput(InputAxisVector.X);
	}
}

void ANinjaController::Jump()
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->Jump();
	}
}

void ANinjaController::EKeyPressed()
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ANinjaCharacter* NinjaCharacter = Cast<ANinjaCharacter>(ControlledCharacter);
		if(NinjaCharacter)
		{
			NinjaCharacter->EquipCurrentWeapon();
		}
	}
}

void ANinjaController::Attack()
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ANinjaCharacter* NinjaCharacter = Cast<ANinjaCharacter>(ControlledCharacter);
		if(NinjaCharacter)
		{
			NinjaCharacter->Attack();
		}
	}
}
