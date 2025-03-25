// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBlocks/BlueBlock.h"
#include "GameFramework/Character.h"

ABlueBlock::ABlueBlock()
{
	EffectDuration = 3.0f;
	InvincibilityTime = 3.0f;
}

void ABlueBlock::ApplyEffect(ACharacter* Target)
{
	if (HasAuthority())
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(Target);
		if (PlayerCharacter)
		{
			// ���� ���� �����

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCharacter]()
				{
					if (PlayerCharacter)
					{
						// ���� ���·� ���ƿ�
					}
				}, EffectDuration, false);
		}
	}
}
