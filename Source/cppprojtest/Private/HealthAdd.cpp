// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAdd.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

UHealthAdd::UHealthAdd()
{

}

void UHealthAdd::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (HealthAddEffect)
    {
        FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(HealthAddEffect, 1);
        if (SpecHandle.IsValid())
        {
            ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
            UE_LOG(LogTemp, Display, TEXT("HealthAdd applied!"));

        }
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
