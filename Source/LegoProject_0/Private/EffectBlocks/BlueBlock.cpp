// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBlocks/BlueBlock.h"

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
			// 무적 상태 만들기

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCharacter]()
				{
					if (PlayerCharacter)
					{
						// 원래 상태로 돌아옴
					}
				}, EffectDuration, false);
		}
	}
}
