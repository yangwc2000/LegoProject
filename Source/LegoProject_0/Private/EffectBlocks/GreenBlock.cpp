// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBlocks/GreenBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

AGreenBlock::AGreenBlock()
{
	EffectDuration = 3.0f;
	JumpBoostValue = 1.5f;
}

void AGreenBlock::ApplyEffect(ACharacter* Target)
{
	if (HasAuthority())
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(Target);
		if (PlayerCharacter)
		{
			UCharacterMovementComponent* MovementComp = PlayerCharacter->GetCharacterMovement();
			if (MovementComp)
			{
				float OriginalJumpVelocity = MovementComp->JumpZVelocity;
				float NewJumpVelocity = OriginalJumpVelocity * JumpBoostValue;

				MovementComp->JumpZVelocity = NewJumpVelocity;

				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCharacter, OriginalJumpVelocity]()
					{
						if (PlayerCharacter)
						{
							UCharacterMovementComponent* ResetMovementComp = PlayerCharacter->GetCharacterMovement();
							if (ResetMovementComp)
							{
								ResetMovementComp->JumpZVelocity = OriginalJumpVelocity;
							}
						}
					}, EffectDuration, false);
			}
		}
	}
}
