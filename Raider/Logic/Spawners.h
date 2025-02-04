#pragma once
#include "../UE4.h"
#include "Abilities.h"

static int GetReloadedAmmoData(auto definition)
{
    auto WeaponWid = (UFortWeaponItemDefinition*)definition;
    auto fullwid = WeaponWid->GetFullName();

    if (fullwid.find("WID_Assault_Auto"))
    {
        return 30;
    }
    if (fullwid.find("WID_Assault_SemiAuto"))
    {
        return 30;
    }
    if (fullwid.find("WID_Shotgun_Standard"))
    {
        return 5;
    }
    if (fullwid.find("WID_Shotgun_SemiAuto"))
    {
        return 5;
    }
    if (fullwid.find("WID_Shotgun_SlugFire"))
    {
        return 7;
    }
    if (fullwid.find("WID_Sniper_BoltAction"))
    {
        return 1;
    }
    if (fullwid.find("WID_Sniper_Standard"))
    {
        return 7;
    }
    if (fullwid.find("WID_Pistol_HandCannon"))
    {
        return 7;
    }
    if (fullwid.find("WID_Pistol_Scavenger"))
    {
        return 30;
    }
    if (fullwid.find("WID_Pistol_AutoHeavy"))
    {
        return 35;
    }
    if (fullwid.find("WID_Pistol_SemiAuto"))
    {
        return 16;
    }
    if (fullwid.find("WID_Pistol_SixShooter"))
    {
        return 16;
    }
    if (fullwid.find("WID_Launcher_Rocket"))
    {
        return 1;
    }
    if (fullwid.find("WID_Launcher_Grenade"))
    {
        return 6;
    }
}

namespace Spawners
{
    static AActor* SpawnActor(UClass* StaticClass, FTransform SpawnTransform, AActor* Owner = nullptr, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
    {
        AActor* FirstActor = GetGameplayStatics()->STATIC_BeginDeferredActorSpawnFromClass(GetWorld(), StaticClass, SpawnTransform, Flags, Owner);

        if (FirstActor)
        {
            AActor* FinalActor = GetGameplayStatics()->STATIC_FinishSpawningActor(FirstActor, SpawnTransform);

            if (FinalActor)
            {
                return FinalActor;
            }
        }

        return nullptr;
    }

    static AActor* SpawnActor(UClass* ActorClass, FVector Location = { 0.0f, 0.0f, 0.0f }, FRotator Rotation = { 0, 0, 0 }, AActor* Owner = nullptr, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
    {
        FTransform SpawnTransform;

        SpawnTransform.Translation = Location;
        SpawnTransform.Scale3D = FVector { 1, 1, 1 };
        SpawnTransform.Rotation = Utils::RotToQuat(Rotation);

        return SpawnActor(ActorClass, SpawnTransform, Owner, Flags);
    }

    template <typename RetActorType = AActor>
    static RetActorType* SpawnActor(FVector Location = { 0.0f, 0.0f, 0.0f }, AActor* Owner = nullptr, FQuat Rotation = { 0, 0, 0 }, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
    {
        FTransform SpawnTransform;

        SpawnTransform.Translation = Location;
        SpawnTransform.Scale3D = FVector { 1, 1, 1 };
        SpawnTransform.Rotation = Rotation;

        return static_cast<RetActorType*>(SpawnActor(RetActorType::StaticClass(), SpawnTransform, Owner, Flags));
    }

    static ABuildingSMActor* SpawnBuilding(UClass* BGAClass, FVector& Location, FRotator& Rotation, APlayerPawn_Athena_C* Pawn)
    {
        FTransform Transform;
        Transform.Translation = Location;
        Transform.Scale3D = FVector { 1, 1, 1 };
        Transform.Rotation = Utils::RotToQuat(Rotation);

        return (ABuildingSMActor*)GetFortKismet()->STATIC_SpawnBuildingGameplayActor(BGAClass, Transform, Pawn);
    }

    static AFortPickup* SummonPickup(AFortPlayerPawn* Pawn, auto ItemDef, int Count, FVector Location)
    {
        auto FortPickup = SpawnActor<AFortPickup>(Location, Pawn);

        FortPickup->bReplicates = true; // should be autmoatic but eh

        FortPickup->PrimaryPickupItemEntry.Count = Count;
        FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

        FortPickup->OnRep_PrimaryPickupItemEntry();
        FortPickup->TossPickup(Location, Pawn, 6, true);

        return FortPickup;
    }

    static void SummonPickupFromChest(auto ItemDef, int Count, FVector Location)
    {
        auto FortPickup = SpawnActor<AFortPickup>(Location);

        FortPickup->bReplicates = true; // should be autmoatic but eh
        // FortPickup->bTossedFromContainer = true;

        FortPickup->PrimaryPickupItemEntry.Count = Count;
        FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

        //credits to ozraider for this
        auto WeaponWid = (UFortWeaponItemDefinition*)FortPickup->PrimaryPickupItemEntry.ItemDefinition;
        auto ActorClass = (AFortWeapon*)WeaponWid->GetWeaponActorClass();
        FortPickup->PrimaryPickupItemEntry.LoadedAmmo = GetReloadedAmmoData(ItemDef);
        FortPickup->bRandomRotation = true;
        FortPickup->OnRep_PrimaryPickupItemEntry();

        FortPickup->PickupLocationData.FlyTime = 0.40f;
        FortPickup->PickupLocationData.bPlayPickupSound = true; // idk what this does
        FortPickup->OnRep_PickupLocationData();
        FortPickup->TossPickup(Location, nullptr, 6, true);
        //FortPickup->OnRep_TossedFromContainer();
    }

    static void SpawnPickupFromFloorLoot(auto ItemDef, int Count, FVector Location)
    {
        auto FortPickup = SpawnActor<AFortPickup>(Location);

        FortPickup->bReplicates = true; // should be autmoatic but eh

        FortPickup->PrimaryPickupItemEntry.Count = Count;
        FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

        FortPickup->OnRep_PrimaryPickupItemEntry();
    }

    static void SpawnDeco(AFortDecoTool* Tool, void* _Params)
    {
        if (!_Params)
            return;

        auto Params = static_cast<AFortDecoTool_ServerSpawnDeco_Params*>(_Params);

        FTransform Transform {};
        Transform.Scale3D = FVector(1, 1, 1);
        Transform.Rotation = Utils::RotToQuat(Params->Rotation);
        Transform.Translation = Params->Location;

        auto TrapDef = static_cast<UFortTrapItemDefinition*>(Tool->ItemDefinition);

        if (TrapDef)
        {
            auto Trap = static_cast<ABuildingTrap*>(SpawnActor(TrapDef->GetBlueprintClass(), Transform));

            if (Trap)
            {
                Trap->TrapData = TrapDef;

                auto Pawn = static_cast<APlayerPawn_Athena_C*>(Tool->Owner);

                Trap->InitializeKismetSpawnedBuildingActor(Trap, static_cast<AFortPlayerController*>(Pawn->Controller));

                Trap->AttachedTo = Params->AttachedActor;
                Trap->OnRep_AttachedTo();

                auto PlayerState = (AFortPlayerStateAthena*)Pawn->Controller->PlayerState;
                Trap->Team = PlayerState->TeamIndex;

                auto TrapAbilitySet = Trap->AbilitySet;

                for (int i = 0; i < TrapAbilitySet->GameplayAbilities.Num(); i++) // this fixes traps crashing the game // don't ask how
                {
                    auto Ability = TrapAbilitySet->GameplayAbilities[i];

                    if (!Ability)
                        continue;

                    Abilities::GrantGameplayAbility(Pawn, Ability);
                }
            }
        }
    }
}