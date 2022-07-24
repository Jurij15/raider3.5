#pragma once

#include <functional>

#include "Logic/Game.h"
#include "Logic/Spawners.h"
#include "Logic/Abilities.h"
#include "UE4.h"
#include "Logger.hpp"
#include <unordered_set>
#include <random>

#include "Util.h"
#include "json.hpp"
#include "Native.h"

/*
std::vector<std::string> Consumables = {
    "Athena_Shields.Athena_Shields",
    "Athena_ShieldSmall.Athena_ShieldSmall",
    "Athena_PurpleStuff.Athena_PurpleStuff",
    "Athena_SuperMedkit.Athena_SuperMedkit",
    "Athena_Grenade.Athena_Grenade",
    "Athena_KnockGrenade.Athena_KnockGrenade",
    "Athena_SmokeGrenade.Athena_SmokeGrenade",
    "Athena_StickyGrenade.Athena_StickyGrenade",
    "Athena_Bush.Athena_Bush",
    "Athena_Medkit.Athena_Medkit",
    "Athena_DanceGrenade.Athena_DanceGrenade",
    "Athena_SmokeGrenade.Athena_SmokeGrenade"
};
std::vector<std::string> Weapons = {
    "WID_Assault_AutoHigh_Athena_SR_Ore_T03.WID_Assault_AutoHigh_Athena_SR_Ore_T03",
    "WID_Assault_AutoHigh_Athena_VR_Ore_T03.WID_Assault_AutoHigh_Athena_VR_Ore_T03",
    "WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03",
    "WID_Assault_Auto_Athena_UC_Ore_T03.WID_Assault_Auto_Athena_UC_Ore_T03",
    "WID_Assault_Auto_Athena_C_Ore_T02.WID_Assault_Auto_Athena_C_Ore_T02",
    "WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
    "WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
    "WID_Shotgun_Standard_Athena_UC_Ore_T03.WID_Shotgun_Standard_Athena_UC_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_UC_Ore_T03.WID_Shotgun_SemiAuto_Athena_UC_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_R_Ore_T03.WID_Shotgun_SemiAuto_Athena_R_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_VR_Ore_T03.WID_Shotgun_SemiAuto_Athena_VR_Ore_T03",
    "WID_Shotgun_SlugFire_Athena_VR.WID_Shotgun_SlugFire_Athena_VR",
    "WID_Shotgun_SlugFire_Athena_SR.WID_Shotgun_SlugFire_Athena_SR",
    "WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03",
    "WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03",
    "WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03",
    "WID_Sniper_Standard_Scope_Athena_VR_Ore_T03.WID_Sniper_Standard_Scope_Athena_VR_Ore_T03",
    "WID_Sniper_Standard_Scope_Athena_SR_Ore_T03.WID_Sniper_Standard_Scope_Athena_SR_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
    "WID_Pistol_Scavenger_Athena_UC_Ore_T03.WID_Pistol_Scavenger_Athena_UC_Ore_T03",
    "WID_Pistol_Scavenger_Athena_R_Ore_T03.WID_Pistol_Scavenger_Athena_R_Ore_T03",
    "WID_Pistol_Scavenger_Athena_VR_Ore_T03.WID_Pistol_Scavenger_Athena_VR_Ore_T03",
    "WID_Assault_LMG_Athena_VR_Ore_T03.WID_Assault_LMG_Athena_VR_Ore_T03",
    "WID_Assault_LMG_Athena_SR_Ore_T03.WID_Assault_LMG_Athena_SR_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_C_Ore_T02.WID_Pistol_SemiAuto_Athena_C_Ore_T02",
    "WID_Pistol_SemiAuto_Athena_UC_Ore_T03.WID_Pistol_SemiAuto_Athena_UC_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_R_Ore_T03.WID_Pistol_SemiAuto_Athena_R_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_VR_Ore_T03.WID_Pistol_SemiAuto_Athena_VR_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_SR_Ore_T03.WID_Pistol_SemiAuto_Athena_SR_Ore_T03",
    "WID_Pistol_SixShooter_Athena_C_Ore_T02.WID_Pistol_SixShooter_Athena_C_Ore_T02",
    "WID_Pistol_SixShooter_Athena_UC_Ore_T03.WID_Pistol_SixShooter_Athena_UC_Ore_T03",
    "WID_Pistol_SixShooter_Athena_R_Ore_T03.WID_Pistol_SixShooter_Athena_R_Ore_T03",
    "WID_Pistol_HandCannon_Athena_VR_Ore_T03.WID_Pistol_HandCannon_Athena_VR_Ore_T03",
    "WID_Pistol_HandCannon_Athena_SR_Ore_T03.WID_Pistol_HandCannon_Athena_SR_Ore_T03",
    "WID_Launcher_Rocket_Athena_R_Ore_T03.WID_Launcher_Rocket_Athena_R_Ore_T03",
    "WID_Launcher_Rocket_Athena_VR_Ore_T03.WID_Launcher_Rocket_Athena_VR_Ore_T03",
    "WID_Launcher_Rocket_Athena_SR_Ore_T03.WID_Launcher_Rocket_Athena_SR_Ore_T03"
};
*/
/*
std::vector<std::string> Consumables = {
    "Athena_Shields",
    "Athena_ShieldSmall ",
    "Athena_PurpleStuff",
    "Athena_SuperMedkit",
    "Athena_Grenade",
    "Athena_KnockGrenade",
    "Athena_SmokeGrenade",
    "Athena_StickyGrenade",
    "Athena_Bush",
    "Athena_Medkit",
    "Athena_DanceGrenade",
    "Athena_SmokeGrenade"
};
std::vector<std::string> Weapons = {
    "WID_Assault_AutoHigh_Athena_SR_Ore_T03",
    "WID_Assault_AutoHigh_Athena_VR_Ore_T03",
    "WID_Assault_Auto_Athena_R_Ore_T03",
    "WID_Assault_Auto_Athena_UC_Ore_T03",
    "WID_Assault_Auto_Athena_C_Ore_T02",
    "WID_Shotgun_Standard_Athena_C_Ore_T03",
    "WID_Shotgun_Standard_Athena_C_Ore_T03",
    "WID_Shotgun_Standard_Athena_UC_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_UC_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_R_Ore_T03",
    "WID_Shotgun_SemiAuto_Athena_VR_Ore_T03",
    "WID_Shotgun_SlugFire_Athena_VR",
    "WID_Shotgun_SlugFire_Athena_SR",
    "WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03",
    "WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03",
    "WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03",
    "WID_Sniper_Standard_Scope_Athena_VR_Ore_T03",
    "WID_Sniper_Standard_Scope_Athena_SR_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03",
    "WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
    "WID_Pistol_Scavenger_Athena_UC_Ore_T03",
    "WID_Pistol_Scavenger_Athena_R_Ore_T03",
    "WID_Pistol_Scavenger_Athena_VR_Ore_T03",
    "WID_Assault_LMG_Athena_VR_Ore_T03",
    "WID_Assault_LMG_Athena_SR_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_C_Ore_T02",
    "WID_Pistol_SemiAuto_Athena_UC_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_R_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_VR_Ore_T03",
    "WID_Pistol_SemiAuto_Athena_SR_Ore_T03",
    "WID_Pistol_SixShooter_Athena_C_Ore_T02",
    "WID_Pistol_SixShooter_Athena_UC_Ore_T03",
    "WID_Pistol_SixShooter_Athena_R_Ore_T03",
    "WID_Pistol_HandCannon_Athena_VR_Ore_T03",
    "WID_Pistol_HandCannon_Athena_SR_Ore_T03",
    "WID_Launcher_Rocket_Athena_R_Ore_T03",
    "WID_Launcher_Rocket_Athena_VR_Ore_T03",
    "WID_Launcher_Rocket_Athena_SR_Ore_T03"
};
*/

std::vector<std::string> Consumables = {
    "/Game/Athena/Items/Consumables/Shields/Athena_Shields.Athena_Shields",
    "/Game/Athena/Items/Consumables/ShieldSmall/Athena_ShieldSmall.Athena_ShieldSmall",
    "/Game/Athena/Items/Consumables/PurpleStuff/Athena_PurpleStuff.Athena_PurpleStuff",
    "/Game/Athena/Items/Consumables/SuperMedkit/Athena_SuperMedkit.Athena_SuperMedkit",
    "/Game/Athena/Items/Consumables/Grenade/Athena_Grenade.Athena_Grenade",
    "/Game/Athena/Items/Consumables/KnockGrenade/Athena_KnockGrenade.Athena_KnockGrenade",
    "/Game/Athena/Items/Consumables/SmokeGrenade/Athena_SmokeGrenade.Athena_SmokeGrenade",
    "/Game/Athena/Items/Consumables/StickyGrenade/Athena_StickyGrenade.Athena_StickyGrenade",
    "/Game/Athena/Items/Consumables/Bush/Athena_Bush.Athena_Bush",
    "/Game/Athena/Items/Consumables/Medkit/Athena_Medkit.Athena_Medkit",
    "/Game/Athena/Items/Consumables/DanceGrenade/Athena_DanceGrenade.Athena_DanceGrenade",
    "/Game/Athena/Items/Consumables/SmokeGrenade/Athena_SmokeGrenade.Athena_SmokeGrenade"
};

std::vector<std::string> Weapons = {
    "/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_SR_Ore_T03.WID_Assault_AutoHigh_Athena_SR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_VR_Ore_T03.WID_Assault_AutoHigh_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_UC_Ore_T03.WID_Assault_Auto_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_C_Ore_T02.WID_Assault_Auto_Athena_C_Ore_T02",
    "/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_UC_Ore_T03.WID_Shotgun_Standard_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_UC_Ore_T03.WID_Shotgun_SemiAuto_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_R_Ore_T03.WID_Shotgun_SemiAuto_Athena_R_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_VR_Ore_T03.WID_Shotgun_SemiAuto_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_VR.WID_Shotgun_SlugFire_Athena_VR",
    "/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_SR.WID_Shotgun_SlugFire_Athena_SR",
    "/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_VR_Ore_T03.WID_Sniper_Standard_Scope_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_SR_Ore_T03.WID_Sniper_Standard_Scope_Athena_SR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_UC_Ore_T03.WID_Pistol_Scavenger_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_R_Ore_T03.WID_Pistol_Scavenger_Athena_R_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_VR_Ore_T03.WID_Pistol_Scavenger_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_LMG_Athena_VR_Ore_T03.WID_Assault_LMG_Athena_VR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Assault_LMG_Athena_SR_Ore_T03.WID_Assault_LMG_Athena_SR_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_C_Ore_T02.WID_Pistol_SemiAuto_Athena_C_Ore_T02",
    "/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_UC_Ore_T03.WID_Pistol_SemiAuto_Athena_UC_Ore_T03",
    "/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_R_Ore_T03.WID_Pistol_SemiAuto_Athena_R_Ore_T03",
};

static auto DropRandomConsumable(auto location)
{
    using namespace Spawners;
    srand((unsigned int)time(NULL));
    auto def = Consumables[rand() % Consumables.size()];
    SummonPickupFromChest(FindWIDForChestFast<UFortItemDefinition>(def), 1, location);
}
static auto DropRandomWeapon(auto location) 
{
    using namespace Spawners;
    srand((unsigned int)time(NULL));
    auto def = Weapons[rand() % Weapons.size()];
    SummonPickupFromChest(FindWIDForChestFast<UFortItemDefinition>(def), 1, location);
}