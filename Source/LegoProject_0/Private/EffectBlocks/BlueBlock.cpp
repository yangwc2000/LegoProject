// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBlocks/BlueBlock.h"
#include "GameFramework/Character.h"

ABlueBlock::ABlueBlock()
{
	BlockLifeTime = 3.0f;
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
			// TODO : ���� ���� �����

			FTimerHandle EffectTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(EffectTimerHandle, [PlayerCharacter]()
				{
					if (PlayerCharacter)
					{
						// TODO : ���� ���·� ���ƿ�
					}
				}, EffectDuration, false);
		}
	}
}
