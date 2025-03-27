// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectBlocks/BlockBase.h"
#include "GreenBlock.generated.h"

/**
 * 
 */
UCLASS()
class LEGOPROJECT_0_API AGreenBlock : public ABlockBase
{
	GENERATED_BODY()
	
public:
	AGreenBlock();

	float JumpBoostValue;
	virtual void ApplyEffect(ACharacter* Target) override;
};
