// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Shinto.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SHINTO_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

		UGameplayAbilityBase();
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		EShintoAbilityInputID AbilityInputID = EShintoAbilityInputID::None;
};
