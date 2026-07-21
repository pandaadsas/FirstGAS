// Copyright Epic Games, Inc. All Rights Reserved.


#include "Public/MyGAS/Character/FirstGASCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "FirstGAS.h"
#include "Kismet/GameplayStatics.h"
#include "MyGAS/MyBlueprintLibrary.h"
#include "MyGAS/Data/CharacterClassInfo.h"
#include "Public/MyGAS/MyAbilitySystemComponent.h"
#include "Public/MyGAS/MyPlayerState.h"

AFirstGASCharacter::AFirstGASCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	
	
	
}

UAbilitySystemComponent* AFirstGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFirstGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
		
	if (HasAuthority())
    {
        InitAbilityActorInfo();
    }

	
	
}

void AFirstGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}


void AFirstGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstGASCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AFirstGASCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstGASCharacter::Look);
	}
	else
	{
		UE_LOG(LogFirstGAS, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFirstGASCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AFirstGASCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AFirstGASCharacter::InitAbilityActorInfo()
{
	if (AMyPlayerState *MyPlayerState = GetPlayerState<AMyPlayerState>())
	{
		AbilitySystemComponent=MyPlayerState->GetMyAbilitySystemComponent();
		Attributes=MyPlayerState->GetMyAttributeSet();
		if (IsValid(AbilitySystemComponent))
		{
			AbilitySystemComponent->InitAbilityActorInfo(MyPlayerState, this);
			BindCallbacksToDependencies();
			if (HasAuthority())
			{
				InitClassDefaults();
			}
		}
	}
	else
	{
		// 如果这里在客户端打印了，说明客户端运行此函数时，PlayerState 还没从网络传过来！
		UE_LOG(LogTemp, Error, TEXT("[%s] 警告：MyPlayerState 是空的！初始化失败！"), *UGameplayStatics::GetPlatformName());
	}
}

void AFirstGASCharacter::InitClassDefaults()
{
	if (!CharacterTag.IsValid())
	{
		UE_LOG(LogFirstGAS, Warning, TEXT("%s() CharacterTag is not valid. Please set a valid tag in the character's Blueprint."), *FString(__FUNCTION__));
	}
	else if (UCharacterClassInfo*ClassInfo=UMyBlueprintLibrary::GetCharacterClassDefaultInfo(this))
	{
		if (const FCharacterClassDefaultInfo*SelectedClassInfo=ClassInfo->CharacterClassInfoMap.Find(CharacterTag))
		{
			if (IsValid(AbilitySystemComponent))
			{
				 AbilitySystemComponent->AddCharacterAbilities(SelectedClassInfo->StartingAbilities);
				 AbilitySystemComponent->AddCharacterPassiveAbilities(SelectedClassInfo->StartingPassiveAbilities);
				 AbilitySystemComponent->InitializeDefaultAttributes( SelectedClassInfo->DefaultAttributeEffect);
			}
		}
	}
}

void AFirstGASCharacter::BindCallbacksToDependencies()
{
	if (IsValid(AbilitySystemComponent)&&IsValid(Attributes))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged(Data.NewValue, Attributes->GetMaxHealth());
		});
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged(Data.NewValue, Attributes->GetMaxMana());
		});
	}
}

void AFirstGASCharacter::BroadcastInitialValues()
{
	if (IsValid(Attributes))
	{
		OnHealthChanged(Attributes->GetHealth(), Attributes->GetMaxHealth());
		OnManaChanged(Attributes->GetMana(), Attributes->GetMaxMana());
	}
}

void AFirstGASCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AFirstGASCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AFirstGASCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AFirstGASCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
