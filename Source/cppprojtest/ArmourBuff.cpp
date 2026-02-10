// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmourBuff.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

UArmourBuff::UArmourBuff()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UArmourBuff::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{

    if (ArmourBuffEffect)
    {
        FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(ArmourBuffEffect, 1);
        if (SpecHandle.IsValid())
        {
            ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
            UE_LOG(LogTemp, Display , TEXT("Armour buff applied!"));
            
        }
    }

    FGameplayTagContainer CooldownTags;
    CooldownTags.AddTag(FGameplayTag::RequestGameplayTag("Cooldown.Ability.ArmourBuff"));
    ActorInfo->AbilitySystemComponent->AddLooseGameplayTags(CooldownTags);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ActorInfo, CooldownTags]()
        {
            ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTags(CooldownTags);
        }, 10.0f, false);

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}