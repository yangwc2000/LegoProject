// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LegoCharacter.h"
#include "Character/LegoPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ALegoCharacter::ALegoCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	PreviewBlock = nullptr;

}

// Called when the game starts or when spawned
void ALegoCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALegoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePreviewBlock();

}

// Called to bind functionality to input
void ALegoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ALegoPlayerController* PlayerController = Cast<ALegoPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ALegoCharacter::Move);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ALegoCharacter::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &ALegoCharacter::StopJump);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ALegoCharacter::Look);
			}
			if (PlayerController->StartPlaceBlockAction)
			{
				EnhancedInput->BindAction(PlayerController->StartPlaceBlockAction, ETriggerEvent::Started, this, &ALegoCharacter::StartPlacingBlock);
			}
			if (PlayerController->ConfirmPlaceBlockAction)
			{
				EnhancedInput->BindAction(PlayerController->ConfirmPlaceBlockAction, ETriggerEvent::Started, this, &ALegoCharacter::ConfirmPlacingBlock);
			}
			if (PlayerController->Block1Action)
			{
				EnhancedInput->BindAction(PlayerController->Block1Action, ETriggerEvent::Triggered, this, &ALegoCharacter::SelectBlock1);
			}
			if (PlayerController->Block2Action)
			{
				EnhancedInput->BindAction(PlayerController->Block2Action, ETriggerEvent::Triggered, this, &ALegoCharacter::SelectBlock2);
			}
			if (PlayerController->Block3Action)
			{
				EnhancedInput->BindAction(PlayerController->Block3Action, ETriggerEvent::Triggered, this, &ALegoCharacter::SelectBlock3);
			}

		}
	}

}

void ALegoCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ALegoCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void ALegoCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void ALegoCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ALegoCharacter::StartPlacingBlock(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("🟡 StartPlacingBlock 호출됨"));

	if (!PreviewBlock && BlockClasses.IsValidIndex(SelectedBlockIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("▶️ 블럭 생성 시도: Index = %d"), SelectedBlockIndex);

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PreviewBlock = GetWorld()->SpawnActor<AActor>(BlockClasses[SelectedBlockIndex], FVector::ZeroVector, FRotator::ZeroRotator, Params);

		if (PreviewBlock)
		{
			PreviewBlock->SetActorEnableCollision(false);
			PreviewBlock->SetActorHiddenInGame(false); // 혹시 모를 숨김 상태 방지
			UE_LOG(LogTemp, Warning, TEXT("✅ PreviewBlock 생성 성공"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ PreviewBlock 생성 실패"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("🔁 이미 PreviewBlock 이 있음 또는 잘못된 인덱스"));
	}
}


void ALegoCharacter::UpdatePreviewBlock()
{
	if (!PreviewBlock) return;

	FHitResult Hit;
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC && PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		if (Hit.bBlockingHit)
		{
			FVector HitLocation = Hit.ImpactPoint;
			PreviewBlock->SetActorLocation(HitLocation);

		}
	}
}

void ALegoCharacter::ConfirmPlacingBlock(const FInputActionValue& value)
{
	if (PreviewBlock && BlockClasses.IsValidIndex(SelectedBlockIndex))
	{
		FVector SpawnLocation = PreviewBlock->GetActorLocation();

		GetWorld()->SpawnActor<AActor>(BlockClasses[SelectedBlockIndex], SpawnLocation, FRotator::ZeroRotator);

		PreviewBlock->Destroy();
		PreviewBlock = nullptr;
	}
}



void ALegoCharacter::SelectBlock1(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		SelectedBlockIndex = 0;
	}
}
void ALegoCharacter::SelectBlock2(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		SelectedBlockIndex = 1;
	}
}
void ALegoCharacter::SelectBlock3(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		SelectedBlockIndex = 2;
	}
}