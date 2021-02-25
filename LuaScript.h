#pragma once
#include <lua.hpp> 
#include "loader.h"
#include "LuaData.h"
lua_State* L;
static string Nowlua;
static string Sublua;
#pragma region GameFun
static int Gmae_Player_GetPlayerCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.z);
    return 3;
}
static int Gmae_Player_SetPlayerCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Component::MovePlayerToPoint(Base::Vector3( x,y,z ));
    return 0;
}
static int Gmae_Player_GetPlayerCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.z);
    return 3;
}
static int Gmae_Player_GetPlayerParabolaCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.z);
    return 3;
}
static int Gmae_Player_GetPlayerWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.z);
    return 3;
}
static int Gmae_Player_CheckAimingStatus(lua_State* pL) {
    lua_pushboolean(pL, Base::PlayerData::AimingState);
    return 1;
}
static int Gmae_Player_AddEffect(lua_State* pL) {
    int group = (int)lua_tointeger(pL, 1);
    int record = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Effects::GenerateSpecialEffects(group, record);
    return 0;
}
static int Gmae_Player_GetPlayerIncrementCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.z);
    return 3;
}
static int Gmae_Player_GetPlayerNavigationCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.z);
    return 3;
}
static int Gmae_Player_GetPlayerVisualCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.z);
    return 3;
}
static int Gmae_Player_SetPlayerVisualCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::SetVisual(x,y,z);
    return 0;
}
static int Gmae_Player_UnbindPlayerVisualCoordinate(lua_State* pL) {
    Base::PlayerData::UnbindVisual();
    return 0;
}
static int Gmae_Player_GetPlayerActionId(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::ActionId);
    return 1;
}
static int Gmae_Player_GetPlayerAngle(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Angle);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponId(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::Weapons::WeaponId);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponType(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::Weapons::WeaponType);
    return 1;
}
static int Gmae_Player_Weapon_ChangeWeapons(lua_State* pL) {
    int type = (int)lua_tointeger(pL, 1);
    int id = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Weapons::ChangeWeapons(type, id);
    return 0;
}
static int Gmae_Player_Weapon_GetOrnamentsCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.z);
    return 3;
}
static int Gmae_Player_Weapon_GetOrnamentsSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.x);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.y);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.z);
    return 3;
}
static int Gmae_Player_Weapon_SetOrnamentsCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::WeaponOrnaments::SetOrnamentsCoordinate(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_SetOrnamentsSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::WeaponOrnaments::SetOrnamentsSize(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_DecontrolOrnamentsCoordinate(lua_State* pL) {
    Base::PlayerData::WeaponOrnaments::DecontrolOrnamentsCoordinate();
    return 0;
}
static int Gmae_Player_Weapon_DecontrolOrnamentsSize(lua_State* pL) {
    Base::PlayerData::WeaponOrnaments::DecontrolOrnamentsSize();
    return 0;
}
static int Gmae_Player_Weapon_GetMainWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.z);
    return 3;
}
static int Gmae_Player_Weapon_GetMainWeaponSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.z);
    return 3;
}
static int Gmae_Player_Weapon_SetMainWeaponCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetMainWeaponCoordinate(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_SetMainWeaponSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetMainWeaponSize(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_DecontrolMainWeaponCoordinate(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolMainWeaponCoordinate();
    return 0;
}
static int Gmae_Player_Weapon_DecontrolMainWeaponSize(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolMainWeaponSize();
    return 0;
}
static int Gmae_Player_Weapon_GetSecondaryWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.z);
    return 3;
}
static int Gmae_Player_Weapon_GetSecondaryWeaponSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.z);
    return 3;
}
static int Gmae_Player_Weapon_SetSecondaryWeaponCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetSecondaryWeaponCoordinate(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_SetSecondaryWeaponSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetSecondaryWeaponSize(x, y, z);
    return 0;
}
static int Gmae_Player_Weapon_DecontrolSecondaryWeaponCoordinate(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolSecondaryWeaponCoordinate();
    return 0;
}
static int Gmae_Player_Weapon_DecontrolSecondaryWeaponSize(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolSecondaryWeaponSize();
    return 0;
}
static int Gmae_Player_GetFsmData(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::Fsm.Target);
    lua_pushinteger(pL, Base::PlayerData::Fsm.Id);
    return 2;
}
static int Gmae_Player_RunFsmAction(lua_State* pL) {
    int type = (int)lua_tonumber(pL, 1);
    int id = (int)lua_tonumber(pL, 2);
    Base::PlayerData::RunDerivedAction(type, id);
    return 0;
}
static int Gmae_Player_CheckRunFsmActionOver(lua_State* pL) {
    lua_pushboolean(pL, Base::PlayerData::CheckDerivedAction());
    return 1;
}
static int Gmae_Player_GetPlayerHealth(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::BasicHealth);
    lua_pushnumber(pL, Base::PlayerData::MaxHealth);
    lua_pushnumber(pL, Base::PlayerData::CurrentHealth);
    return 3;
}
static int Gmae_Player_SetPlayerCurrentHealth(lua_State* pL) {
    float health = (float)lua_tonumber(pL, 1);
    Component::SetPlayerHealth(health);
    return 0;
}
static int Gmae_Player_SetPlayerBasicHealth(lua_State* pL) {
    float health = (float)lua_tonumber(pL, 1);
    Component::SetPlayerBasicHealth(health);
    return 0;
}
static int Gmae_Player_GetPlayerEndurance(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::MaxEndurance);
    lua_pushnumber(pL, Base::PlayerData::CurrentEndurance);
    return 2;
}
static int Gmae_Player_SetPlayerCurrentEndurance(lua_State* pL) {
    float endurance = (float)lua_tonumber(pL, 1);
    Component::SetPlayerEndurance(endurance);
    return 0;
}
static int Gmae_Player_SetPlayerMaxEndurance(lua_State* pL) {
    float endurance = (float)lua_tonumber(pL, 1);
    Component::SetPlayerMaxEndurance(endurance);
    return 0;
}
static int Gmae_Player_GetPlayerRoleInfo(lua_State* pL) {
    lua_pushstring(pL, Base::PlayerData::Name.c_str());
    lua_pushinteger(pL, Base::PlayerData::Hr);
    lua_pushinteger(pL, Base::PlayerData::Mr);
    return 3;
}
static int Gmae_World_GetMapId(lua_State* pL) {
    lua_pushinteger(pL, Base::World::MapId);
    return 1;
}
static int Game_Monster_SetFilter(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    int subId = (int)lua_tointeger(pL, 2);
    Component::SetMonsterFilter(id,subId);
    return 0;
}
static int Game_Monster_DisableFilter(lua_State* pL) {
    Component::DisableMonsterFilter();
    return 0;
}
static int Game_Monster_SetBehaviorOfNavigationMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::NavigationMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNavigationMarkMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillNavigationMonster());
    return 1;
}
static int Game_Monster_SetBehaviorOfNearestMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::NearestMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNearestMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillNearestMonster());
    return 1;
}
static int Game_Monster_KillNearestMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushboolean(pL, Component::KillNearestMonster(min, max));
    return 1;
}
static int Game_Monster_SetBehaviorOfLastHitMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::LastHitMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillLastHitMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillLastHitMonster());
    return 1;
}
static int Game_Monster_KillAllMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    Component::KillAllMonster(min, max);
    return 0;
}
static int Game_Monster_AddDebuffToNavigationMarkMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetNavigationMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetNearestMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    lua_pushboolean(pL, Component::SetNearestMonsterBuff(buff, min, max));
    return 1;
}
static int Game_Monster_AddDebuffLastHitMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetLastHitMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffToAllMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    Component::SetAllMonsterBuff(buff, min, max);
    return 0;
}
static int Game_Monster_GetNavigationMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetNavigationMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Monster_GetNearestMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetNearestMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Monster_GetLastHitMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetLastHitMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Environmental_SetFilter(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    int subId = (int)lua_tointeger(pL, 2);
    Component::SetEnvironmentalFilter(id, subId);
    return 0;
}
static int Game_Environmental_DisableFilter(lua_State* pL) {
    Component::DisableEnvironmentalFilter();
    return 0;
}
static int Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    Component::SetAllEnvironmentalCoordinates(Base::Vector3(x,y,z), min, max);
    return 0;
}
static int Gmae_Player_CreateWeaponProjectiles(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    float startx = (float)lua_tonumber(pL, 2);
    float starty = (float)lua_tonumber(pL, 3);
    float startz = (float)lua_tonumber(pL, 4);
    float endx = (float)lua_tonumber(pL, 5);
    float endy = (float)lua_tonumber(pL, 6);
    float endz = (float)lua_tonumber(pL, 7);
    lua_pushboolean(pL, Base::ProjectilesOperation::CreateProjectiles(
        id, Base::Vector3(startx, starty, startz), Base::Vector3(endx, endy, endz),0
    ));
    return 1;
}
static int Gmae_Player_CreateBowgunProjectiles(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    float startx = (float)lua_tonumber(pL, 2);
    float starty = (float)lua_tonumber(pL, 3);
    float startz = (float)lua_tonumber(pL, 4);
    float endx = (float)lua_tonumber(pL, 5);
    float endy = (float)lua_tonumber(pL, 6);
    float endz = (float)lua_tonumber(pL, 7);
    lua_pushboolean(pL, Base::ProjectilesOperation::CreateProjectiles(
        id, Base::Vector3(startx, starty, startz), Base::Vector3(endx, endy, endz),1
    ));
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinates(lua_State* pL)
{
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinates()) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealth(lua_State* pL)
{
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealth()) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinatesInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToPlayers(min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealthInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealthRelativeToPlayers(min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinatesInTargetPointRange(lua_State* pL)
{
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToTarget(Base::Vector3(x,y,z),min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealthInTargetPointRange(lua_State* pL)
{
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealthRelativeToTarget(Base::Vector3(x, y, z), min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Environmental_GetAllEnvironmentalCoordinatesInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, environmentalData] : Component::GetAllEnvironmentalCoordinates(min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, environmentalData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, environmentalData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, environmentalData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, environmentalData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, environmentalData.SubId);
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
    }
    return 1;
}
static int Gmae_Player_GetPlayerBuffDuration(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Base::PlayerData::GetPlayerBuff(buff));
    return 1;
}
static int Gmae_Player_SetPlayerBuffDuration(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float duration = (float)lua_tonumber(pL, 2);
    Base::PlayerData::SetPlayerBuff(buff, duration);
    return 0;
}
static int Gmae_Player_GetPlayerHookCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.z);
    return 3;
}
static int Gmae_Player_GetPlayerVisualDistance(lua_State* pL) {
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    lua_pushnumber(pL, *offsetPtr<float>(VisualOffset, 0x5E8));
    return 1;
}
static int Gmae_Player_GetPlayerVisualHeight(lua_State* pL) {
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    lua_pushnumber(pL, *offsetPtr<float>(VisualOffset, 0x5E4));
    return 1;
}
static int Gmae_Player_SetPlayerVisualDistance(lua_State* pL) {
    float distance = (float)lua_tonumber(pL, -1);
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    *offsetPtr<float>(VisualOffset, 0x5E8) = distance;
    return 0;
}
static int Gmae_Player_SetPlayerVisualHeight(lua_State* pL) {
    float height = (float)lua_tonumber(pL, -1);
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    *offsetPtr<float>(VisualOffset, 0x5E4) = height;
    return 0;
}

#pragma endregion
#pragma region SystemFun
static int System_Keyboard_CheckKey(lua_State* pL) {    
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::Keyboard::CheckKey(key));
    return 1;
}
static int System_Keyboard_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::Keyboard::CheckKey(key, 2));
    return 1;
}
static int System_Keyboard_CheckKeyIsPressed(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    bool ret = GetKeyState(key) < 0;
    if (!Base::Keyboard::CheckWindows())
        ret = false;
    lua_pushboolean(pL, ret);
    return 1;
}
static int System_Chronoscope_AddChronoscope(lua_State* pL) {
    float time = (float)lua_tonumber(pL, 1);
    string name = (string)lua_tostring(pL, 2);
    Base::Chronoscope::AddChronoscope(time, name, true);
    return 0;
}
static int System_Chronoscope_CheckPresenceChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Base::Chronoscope::CheckPresenceChronoscope(name));
    return 1;
}
static int System_Chronoscope_DelChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    Base::Chronoscope::DelChronoscope(name);
    return 0;
}
static int System_Chronoscope_CheckChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Base::Chronoscope::CheckChronoscope(name));
    return 1;
}
static int System_Message_ShowMessage(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    Component::ShowMessage(message);
    return 0;
}
static int System_Console_Info(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    LOG(INFO) << Base::ModConfig::ModName << " LUA INFO:" << message;
    return 0;
}
static int System_Console_Error(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    LOG(ERR) << Base::ModConfig::ModName << " LUA ERR:"<< message;
    return 0;
}
static int System_XboxPad_CheckKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::XboxPad::CheckKey(key));
    return 1;
}
static int System_XboxPad_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::XboxPad::CheckKey(key, 2));
    return 1;
}
static int System_XboxPad_CheckKeyIsPressed(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    bool ret = Base::XboxPad::KeyIdHandle(key);
    lua_pushboolean(pL, ret);
    return 1;
}
#pragma endregion
#pragma region LuaFun
//存入整数变量
static int Lua_Variable_SaveIntVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//存入全局整数变量
static int Lua_Variable_SaveGlobalIntVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//存入浮点数变量
static int Lua_Variable_SaveFloatVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//存入全局浮点数变量
static int Lua_Variable_SaveGlobalFloatVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//存入字符串变量
static int Lua_Variable_SaveStringVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//存入全局字符串变量
static int Lua_Variable_SaveGlobalStringVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//读取整数变量
static int Lua_Variable_ReadIntVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    int ret;
    if (LuaData::IntVariable.find(variableName) == LuaData::IntVariable.end())
        ret = 0;
    else
        ret = LuaData::IntVariable[variableName];
    lua_pushinteger(pL, ret);
    return 1;
}
//读取全局整数变量
static int Lua_Variable_ReadGlobalIntVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    int ret;
    if (LuaData::IntVariable.find(variableName) == LuaData::IntVariable.end())
        ret = 0;
    else
        ret = LuaData::IntVariable[variableName];
    lua_pushinteger(pL, ret);
    return 1;
}
//读取浮点数变量
static int Lua_Variable_ReadFloatVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    float ret;
    if (LuaData::FloatVariable.find(variableName) == LuaData::FloatVariable.end())
        ret = 0;
    else
        ret = LuaData::FloatVariable[variableName];
    lua_pushnumber(pL, ret);
    return 1;
}
//读取全局浮点数变量
static int Lua_Variable_ReadGlobalFloatVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    float ret;
    if (LuaData::FloatVariable.find(variableName) == LuaData::FloatVariable.end())
        ret = 0;
    else
        ret = LuaData::FloatVariable[variableName];
    lua_pushnumber(pL, ret);
    return 1;
}
//读取字符串变量
static int Lua_Variable_ReadStringVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    string ret;
    if (LuaData::StringVariable.find(variableName) == LuaData::StringVariable.end())
        ret = "";
    else
        ret = LuaData::StringVariable[variableName];
    lua_pushstring(pL, ret.c_str());
    return 1;
}
//读取全局字符串变量
static int Lua_Variable_ReadGlobalStringVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    string ret;
    if (LuaData::StringVariable.find(variableName) == LuaData::StringVariable.end())
        ret = "";
    else
        ret = LuaData::StringVariable[variableName];
    lua_pushstring(pL, ret.c_str());
    return 1;
}
//销毁变量
static int Lua_Variable_DestroyVariable(lua_State* pL) {
    string variableTpye = (string)lua_tostring(pL, 1);
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 2);
    if (variableTpye == "Int")
        LuaData::IntVariable.erase(variableName);
    else if (variableTpye == "Float")
        LuaData::FloatVariable.erase(variableName);
    else if (variableTpye == "String")
        LuaData::StringVariable.erase(variableName);
    return 0;
}
//销毁全局变量
static int Lua_Variable_DestroyGlobalVariable(lua_State* pL) {
    string variableTpye = "G_" + (string)lua_tostring(pL, 1);
    string variableName = (string)lua_tostring(pL, 2);
    if (variableTpye == "Int")
        LuaData::IntVariable.erase(variableName);
    else if (variableTpye == "Float")
        LuaData::FloatVariable.erase(variableName);
    else if (variableTpye == "String")
        LuaData::StringVariable.erase(variableName);
    return 0;
}
//设置子脚本变量前缀
static int Lua_Variable_SetSubScriptVariablePrefix(lua_State* pL) {
    string variablePrefix = (string)lua_tostring(pL, -1);
    Sublua = variablePrefix;
    return 0;
}
//获取随机数
static int Lua_Math_Rander(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushnumber(pL, Base::Calculation::myRander(min, max));
    return 1;
}
//获取网络数据
static int Lua_Http_GetHttpData(lua_State* pL) {
    string httpUrl = (string)lua_tostring(pL, -1);
    lua_pushstring(pL, NetworkServer::GetHttpData(httpUrl).c_str());
    return 1;
}
//获取LuaScript插件构建版本
static int System_LuaScript_Build(lua_State* pL) {
    lua_pushnumber(pL, Base::ModConfig::ModBuild);
    return 1;
}
//获取LuaScript插件发行版本
static int System_LuaScript_Version(lua_State* pL) {
    lua_pushstring(pL, Base::ModConfig::ModVersion.c_str());
    return 1;
}
#pragma endregion
//==============================================
// Main Functions
//==============================================
int Lua_Main(string LuaFile)
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaL_openlibs(L);
    int error = luaL_dofile(L, LuaFile.c_str());
    if (error)
    {
        //LOG(ERR) << "dofile error";
        return -1;
    }
    Nowlua = LuaFile;

#pragma region Game
    #pragma region Player
    //获取玩家坐标
    lua_register(L, "Gmae_Player_GetPlayerCoordinate", Gmae_Player_GetPlayerCoordinate);
    //设置玩家坐标
    lua_register(L, "Gmae_Player_SetPlayerCoordinate", Gmae_Player_SetPlayerCoordinate);
    //获取准星坐标
    lua_register(L, "Gmae_Player_GetPlayerCollimatorCoordinate", Gmae_Player_GetPlayerCollimatorCoordinate);
    //获取抛物线准星坐标
    lua_register(L, "Gmae_Player_GetPlayerParabolaCollimatorCoordinate", Gmae_Player_GetPlayerParabolaCollimatorCoordinate);
    //获取武器坐标
    lua_register(L, "Gmae_Player_GetPlayerWeaponCoordinate", Gmae_Player_GetPlayerWeaponCoordinate);
    //检查瞄准状态
    lua_register(L, "Gmae_Player_CheckAimingStatus", Gmae_Player_CheckAimingStatus);
    //获取增量坐标
    lua_register(L, "Gmae_Player_GetPlayerIncrementCoordinate", Gmae_Player_GetPlayerIncrementCoordinate);
    //获取导航坐标
    lua_register(L, "Gmae_Player_GetPlayerNavigationCoordinate", Gmae_Player_GetPlayerNavigationCoordinate);
    //获取相机坐标
    lua_register(L, "Gmae_Player_GetPlayerVisualCoordinate", Gmae_Player_GetPlayerVisualCoordinate);
    //设置相机坐标（xyz和持续时间4个参数）
    lua_register(L, "Gmae_Player_SetPlayerVisualCoordinate", Gmae_Player_SetPlayerVisualCoordinate);
    //解除相机坐标绑定
    lua_register(L, "Gmae_Player_UnbindPlayerVisualCoordinate", Gmae_Player_UnbindPlayerVisualCoordinate);
    //获取相机距离
    lua_register(L, "Gmae_Player_GetPlayerVisualDistance", Gmae_Player_GetPlayerVisualDistance);
    //获取相机高度
    lua_register(L, "Gmae_Player_GetPlayerVisualHeight", Gmae_Player_GetPlayerVisualHeight);
    //设置相机距离
    lua_register(L, "Gmae_Player_SetPlayerVisualDistance", Gmae_Player_SetPlayerVisualDistance);
    //设置相机高度
    lua_register(L, "Gmae_Player_SetPlayerVisualHeight", Gmae_Player_SetPlayerVisualHeight);
    //获取玩家动作id
    lua_register(L, "Gmae_Player_GetPlayerActionId", Gmae_Player_GetPlayerActionId);
    //获取面向角度
    lua_register(L, "Gmae_Player_GetPlayerAngle", Gmae_Player_GetPlayerAngle);
    //添加特效
    lua_register(L, "Gmae_Player_AddEffect", Gmae_Player_AddEffect);

    //获取玩家武器Id
    lua_register(L, "Gmae_Player_Weapon_GetWeaponId", Gmae_Player_Weapon_GetWeaponId);
    //获取玩家武器类型
    lua_register(L, "Gmae_Player_Weapon_GetWeaponType", Gmae_Player_Weapon_GetWeaponType);
    //更换玩家的武器
    lua_register(L, "Gmae_Player_Weapon_ChangeWeapons", Gmae_Player_Weapon_ChangeWeapons);
    //获取玩家武器装饰物坐标
    lua_register(L, "Gmae_Player_Weapon_GetOrnamentsCoordinate", Gmae_Player_Weapon_GetOrnamentsCoordinate);
    //获取玩家武器装饰物模型大小
    lua_register(L, "Gmae_Player_Weapon_GetOrnamentsSize", Gmae_Player_Weapon_GetOrnamentsSize);
    //设置玩家武器装饰物坐标
    lua_register(L, "Gmae_Player_Weapon_SetOrnamentsCoordinate", Gmae_Player_Weapon_SetOrnamentsCoordinate);
    //设置玩家武器装饰物模型大小
    lua_register(L, "Gmae_Player_Weapon_SetOrnamentsSize", Gmae_Player_Weapon_SetOrnamentsSize);
    //解除玩家武器装饰物坐标设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolOrnamentsCoordinate", Gmae_Player_Weapon_DecontrolOrnamentsCoordinate);
    //解除玩家武器装饰物模型大小设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolOrnamentsSize", Gmae_Player_Weapon_DecontrolOrnamentsSize);
    //获取玩家主武器坐标
    lua_register(L, "Gmae_Player_Weapon_GetMainWeaponCoordinate", Gmae_Player_Weapon_GetMainWeaponCoordinate);
    //获取玩家主武器模型大小
    lua_register(L, "Gmae_Player_Weapon_GetMainWeaponSize", Gmae_Player_Weapon_GetMainWeaponSize);
    //设置玩家主武器坐标
    lua_register(L, "Gmae_Player_Weapon_SetMainWeaponCoordinate", Gmae_Player_Weapon_SetMainWeaponCoordinate);
    //设置玩家主武器模型大小
    lua_register(L, "Gmae_Player_Weapon_SetMainWeaponSize", Gmae_Player_Weapon_SetMainWeaponSize);
    //解除玩家主武器坐标设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolMainWeaponCoordinate", Gmae_Player_Weapon_DecontrolMainWeaponCoordinate);
    //解除玩家主武器模型大小设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolMainWeaponSize", Gmae_Player_Weapon_DecontrolMainWeaponSize);
    //获取玩家副武器坐标
    lua_register(L, "Gmae_Player_Weapon_GetSecondaryWeaponCoordinate", Gmae_Player_Weapon_GetSecondaryWeaponCoordinate);
    //获取玩家副武器模型大小
    lua_register(L, "Gmae_Player_Weapon_GetSecondaryWeaponSize", Gmae_Player_Weapon_GetSecondaryWeaponSize);
    //设置玩家副武器坐标
    lua_register(L, "Gmae_Player_Weapon_SetSecondaryWeaponCoordinate", Gmae_Player_Weapon_SetSecondaryWeaponCoordinate);
    //设置玩家副武器模型大小
    lua_register(L, "Gmae_Player_Weapon_SetSecondaryWeaponSize", Gmae_Player_Weapon_SetSecondaryWeaponSize);
    //解除玩家副武器坐标设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolSecondaryWeaponCoordinate", Gmae_Player_Weapon_DecontrolSecondaryWeaponCoordinate);
    //解除玩家副武器模型大小设置
    lua_register(L, "Gmae_Player_Weapon_DecontrolSecondaryWeaponSize", Gmae_Player_Weapon_DecontrolSecondaryWeaponSize);
    
    //获取玩家派生信息
    lua_register(L, "Gmae_Player_GetFsmData", Gmae_Player_GetFsmData);
    //执行指定的派生动作
    lua_register(L, "Gmae_Player_RunFsmAction", Gmae_Player_RunFsmAction);
    //检查执行的派生动作是否结束
    lua_register(L, "Gmae_Player_CheckRunFsmActionOver", Gmae_Player_CheckRunFsmActionOver);
    //获取玩家血量信息
    lua_register(L, "Gmae_Player_GetPlayerHealth", Gmae_Player_GetPlayerHealth);
    //设置玩家当前血量
    lua_register(L, "Gmae_Player_SetPlayerCurrentHealth", Gmae_Player_SetPlayerCurrentHealth);
    //设置玩家基础血量
    lua_register(L, "Gmae_Player_SetPlayerBasicHealth", Gmae_Player_SetPlayerBasicHealth);
    //获取玩家耐力信息
    lua_register(L, "Gmae_Player_GetPlayerEndurance", Gmae_Player_GetPlayerEndurance);
    //设置玩家当前耐力
    lua_register(L, "Gmae_Player_SetPlayerCurrentEndurance", Gmae_Player_SetPlayerCurrentEndurance);
    //设置玩家最大耐力
    lua_register(L, "Gmae_Player_SetPlayerMaxEndurance", Gmae_Player_SetPlayerMaxEndurance);
    //获取玩家角色信息
    lua_register(L, "Gmae_Player_GetPlayerRoleInfo", Gmae_Player_GetPlayerRoleInfo);
    //生成玩家武器投射物
    lua_register(L, "Gmae_Player_CreateWeaponProjectiles", Gmae_Player_CreateWeaponProjectiles);
    //生成玩家手弩投射物
    lua_register(L, "Gmae_Player_CreateBowgunProjectiles", Gmae_Player_CreateBowgunProjectiles);
    //获取玩家Buff剩余时间
    lua_register(L, "Gmae_Player_GetPlayerBuffDuration", Gmae_Player_GetPlayerBuffDuration);
    //设置玩家Buff剩余时间
    lua_register(L, "Gmae_Player_SetPlayerBuffDuration", Gmae_Player_SetPlayerBuffDuration);
    //获取玩家钩爪坐标
    lua_register(L, "Gmae_Player_GetPlayerHookCoordinate", Gmae_Player_GetPlayerHookCoordinate);
    
    #pragma endregion
    //获取当前地图Id
    lua_register(L, "Gmae_World_GetMapId", Gmae_World_GetMapId);
    #pragma region Monster
    //设置怪物筛选器
    lua_register(L, "Game_Monster_SetFilter", Game_Monster_SetFilter);
    //清除怪物筛选器
    lua_register(L, "Game_Monster_DisableFilter", Game_Monster_DisableFilter);
    //控制导航怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfNavigationMonsters", Game_Monster_SetBehaviorOfNavigationMonsters);
    //杀死导航标记的怪物
    lua_register(L, "Game_Monster_KillNavigationMarkMonster", Game_Monster_KillNavigationMarkMonster);
    //给导航标记的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffToNavigationMarkMonster", Game_Monster_AddDebuffToNavigationMarkMonster);
    //控制距离最近的怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfNearestMonsters", Game_Monster_SetBehaviorOfNearestMonsters);
    //杀死距离最近的怪物
    lua_register(L, "Game_Monster_KillNearestMonster", Game_Monster_KillNearestMonster);
    //杀死范围内距离最近的怪物
    lua_register(L, "Game_Monster_KillNearestMonsterInRange", Game_Monster_KillNearestMonsterInRange);
    //给距离最近的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffNearestMonster", Game_Monster_AddDebuffNearestMonster);
    //给范围内距离最近的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffNearestMonsterInRange", Game_Monster_AddDebuffNearestMonsterInRange);
    //控制最后一次击中的怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfLastHitMonsters", Game_Monster_SetBehaviorOfLastHitMonsters);
    //杀死最后一次击中的怪物
    lua_register(L, "Game_Monster_KillLastHitMonster", Game_Monster_KillLastHitMonster);
    //给最后一次击中的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffLastHitMonster", Game_Monster_AddDebuffLastHitMonster);
    //杀死范围内所有怪物
    lua_register(L, "Game_Monster_KillAllMonsterInRange", Game_Monster_KillAllMonsterInRange);
    //给范围内所有怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffToAllMonsterInRange", Game_Monster_AddDebuffToAllMonsterInRange);
    //获取导航的怪物的坐标
    lua_register(L, "Game_Monster_GetNavigationMonsterCoordinates", Game_Monster_GetNavigationMonsterCoordinates);
    //获取距离最近的怪物的坐标
    lua_register(L, "Game_Monster_GetNearestMonsterCoordinates", Game_Monster_GetNearestMonsterCoordinates);
    //获取最后一次击中的怪物的坐标
    lua_register(L, "Game_Monster_GetLastHitMonsterCoordinates", Game_Monster_GetLastHitMonsterCoordinates);
    //获取所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinates", Game_Monster_GetAllMonsterCoordinates);
    //获取所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealth", Game_Monster_GetAllMonsterHealth);
    //获取所有怪物的异常状态(计划中)
    //lua_register(L, "Game_Monster_GetAllMonsterDebuff", Game_Monster_GetAllMonsterDebuff);
    //获取范围内所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInRange", Game_Monster_GetAllMonsterCoordinatesInRange);
    //获取范围内所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealthInRange", Game_Monster_GetAllMonsterHealthInRange);
    //获取范围内所有怪物的异常状态(计划中)
    //lua_register(L, "Game_Monster_GetAllMonsterDebuffInRange", Game_Monster_GetAllMonsterDebuffInRange);
    //获取目标点范围内所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInTargetPointRange", Game_Monster_GetAllMonsterCoordinatesInTargetPointRange);
    //获取目标点范围内所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealthInTargetPointRange", Game_Monster_GetAllMonsterHealthInTargetPointRange);
    //获取目标点范围内所有怪物的异常状态(计划中)
    //lua_register(L, "Game_Monster_GetAllMonsterDebuffInTargetPointRange", Game_Monster_GetAllMonsterDebuffInTargetPointRange);
    #pragma endregion
    #pragma region Environmental
    //设置环境生物筛选器
    lua_register(L, "Game_Environmental_SetFilter", Game_Environmental_SetFilter);
    //清除环境生物筛选器
    lua_register(L, "Game_Environmental_DisableFilter", Game_Environmental_DisableFilter);
    //设置范围内所有环境生物的坐标
    lua_register(L, "Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange", Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange);
    //获取范围内所有环境生物的坐标
    lua_register(L, "Game_Environmental_GetAllEnvironmentalCoordinatesInRange", Game_Environmental_GetAllEnvironmentalCoordinatesInRange);
    #pragma endregion
#pragma endregion
#pragma region System
    //检查按键
    lua_register(L, "System_Keyboard_CheckKey", System_Keyboard_CheckKey);
    //检查按键双击
    lua_register(L, "System_Keyboard_CheckDoubleKey", System_Keyboard_CheckDoubleKey);
    //检查按键是否处于按下状态
    lua_register(L, "System_Keyboard_CheckKeyIsPressed", System_Keyboard_CheckKeyIsPressed);
    //检查Xbox按键
    lua_register(L, "System_XboxPad_CheckKey", System_XboxPad_CheckKey);
    //检查Xbox按键双击
    lua_register(L, "System_XboxPad_CheckDoubleKey", System_XboxPad_CheckDoubleKey);
    //检查Xbox按键是否处于按下状态
    lua_register(L, "System_XboxPad_CheckKeyIsPressed", System_XboxPad_CheckKeyIsPressed);
    //添加计时器
    lua_register(L, "System_Chronoscope_AddChronoscope", System_Chronoscope_AddChronoscope);
    //检查计时器
    lua_register(L, "System_Chronoscope_CheckChronoscope", System_Chronoscope_CheckChronoscope);
    //检查计时器是否存在
    lua_register(L, "System_Chronoscope_CheckPresenceChronoscope", System_Chronoscope_CheckPresenceChronoscope);
    //删除计时器
    lua_register(L, "System_Chronoscope_DelChronoscope", System_Chronoscope_DelChronoscope);
    //向游戏内发送消息
    lua_register(L, "System_Message_ShowMessage", System_Message_ShowMessage);
    //向控制台发送消息
    lua_register(L, "System_Console_Info", System_Console_Info);
    //向控制台发送错误消息
    lua_register(L, "System_Console_Error", System_Console_Error);
    //获取LuaScript插件构建版本
    lua_register(L, "System_LuaScript_Build", System_LuaScript_Build);
    //获取LuaScript插件构建版本
    lua_register(L, "System_LuaScript_Version", System_LuaScript_Version);
#pragma endregion
#pragma region Lua
    //存入整数变量
    lua_register(L, "Lua_Variable_SaveIntVariable", Lua_Variable_SaveIntVariable);
    //存入浮点数变量
    lua_register(L, "Lua_Variable_SaveFloatVariable", Lua_Variable_SaveFloatVariable);
    //存入字符串变量
    lua_register(L, "Lua_Variable_SaveStringVariable", Lua_Variable_SaveStringVariable);
    //读取整数变量
    lua_register(L, "Lua_Variable_ReadIntVariable", Lua_Variable_ReadIntVariable);
    //读取浮点数变量
    lua_register(L, "Lua_Variable_ReadFloatVariable", Lua_Variable_ReadFloatVariable);
    //读取字符串变量
    lua_register(L, "Lua_Variable_ReadStringVariable", Lua_Variable_ReadStringVariable);
    //销毁变量
    lua_register(L, "Lua_Variable_DestroyVariable", Lua_Variable_DestroyVariable);
    //设置子脚本变量名
    lua_register(L, "Lua_Variable_SetSubScriptVariablePrefix", Lua_Variable_SetSubScriptVariablePrefix);
    //获取随机数
    lua_register(L, "Lua_Math_Rander", Lua_Math_Rander);
    //存入全局整数变量
    lua_register(L, "Lua_Variable_SaveGlobalIntVariable", Lua_Variable_SaveGlobalIntVariable);
    //存入全局浮点数变量
    lua_register(L, "Lua_Variable_SaveGlobalFloatVariable", Lua_Variable_SaveGlobalFloatVariable);
    //存入全局字符串变量
    lua_register(L, "Lua_Variable_SaveGlobalStringVariable", Lua_Variable_SaveGlobalStringVariable);
    //读取全局整数变量
    lua_register(L, "Lua_Variable_ReadGlobalIntVariable", Lua_Variable_ReadGlobalIntVariable);
    //读取全局浮点数变量
    lua_register(L, "Lua_Variable_ReadGlobalFloatVariable", Lua_Variable_ReadGlobalFloatVariable);
    //读取全局字符串变量
    lua_register(L, "Lua_Variable_ReadGlobalStringVariable", Lua_Variable_ReadGlobalStringVariable);
    //销毁全局变量
    lua_register(L, "Lua_Variable_DestroyGlobalVariable", Lua_Variable_DestroyGlobalVariable);
    //获取网络数据
    lua_register(L, "Lua_Http_GetHttpData", Lua_Http_GetHttpData);
#pragma endregion

    lua_getglobal(L, "run");
    lua_pcall(L, 0, 0, 0);
    lua_close(L);
    Sublua = "";
    return 1;
}