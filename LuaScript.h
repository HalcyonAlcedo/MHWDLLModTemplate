#pragma once
#include <lua.hpp> 
#include "loader.h"
lua_State* L;
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
    Component::MovePlayerToPoint(Component::Coordinate{ x,y,z });
    return 0;
}
static int Gmae_Player_GetPlayerCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.z);
    return 3;
}
static int Gmae_Player_CheckAimingStatus(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::AimingState);
    return 1;
}
static int Gmae_Player_AddEffect(lua_State* pL) {
    int group = (int)lua_tointeger(pL, 1);
    int record = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Effects::GenerateSpecialEffects(group, record);
    return 0;
}

#pragma region WeaponFun
static int Gmae_Player_Weapon_GetWeaponType(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponType);
    return 1;
}
#pragma endregion

#pragma endregion
#pragma region SystemFun
static int System_Keyboard_CheckKey(lua_State* pL) {    
    int key = (int)lua_tointeger(pL, -1);
    lua_pushnumber(pL, Base::Keyboard::CheckKey(key));
    return 1;
}
static int System_Keyboard_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushnumber(pL, Base::Keyboard::CheckKey(key, 2));
    return 1;
}
static int System_Chronoscope_AddChronoscope(lua_State* pL) {
    float time = (float)lua_tonumber(pL, 1);
    string name = (string)lua_tostring(pL, 2);
    Base::Chronoscope::AddChronoscope(time, name, true);
    return 0;
}
static int System_Chronoscope_CheckChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Base::Chronoscope::CheckChronoscope(name));
    return 1;
}
#pragma endregion
//==============================================
// Main Functions
//==============================================
int Lua_Main()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);     // ����Lua������
    luaL_openlibs(L);
    //L = lua_open();   //�°汾������   

   /* load the script */
    #pragma region Game
    //��ȡ�������
    lua_register(L, "Gmae_Player_GetPlayerCoordinate", Gmae_Player_GetPlayerCoordinate);
    //�����������
    lua_register(L, "Gmae_Player_SetPlayerCoordinate", Gmae_Player_SetPlayerCoordinate);
    //��ȡ׼������
    lua_register(L, "Gmae_Player_GetPlayerCollimatorCoordinate", Gmae_Player_GetPlayerCollimatorCoordinate);
    //�����׼״̬
    lua_register(L, "Gmae_Player_CheckAimingStatus", Gmae_Player_CheckAimingStatus);
    //�����Ч
    lua_register(L, "Gmae_Player_AddEffect", Gmae_Player_AddEffect);

    #pragma region Weapon
    //��ȡ�����������
    lua_register(L, "Gmae_Player_Weapon_GetWeaponType", Gmae_Player_Weapon_GetWeaponType);
    #pragma endregion
    
    #pragma endregion
    #pragma region System
    //��鰴��
    lua_register(L, "System_Keyboard_CheckKey", System_Keyboard_CheckKey);
    //��鰴��˫��
    lua_register(L, "System_Keyboard_CheckDoubleKey", System_Keyboard_CheckDoubleKey);
    //��Ӽ�ʱ��
    lua_register(L, "System_Chronoscope_AddChronoscope", System_Chronoscope_AddChronoscope);
    //����ʱ��
    lua_register(L, "System_Chronoscope_CheckChronoscope", System_Chronoscope_CheckChronoscope);
    
    #pragma endregion

    int error = luaL_dofile(L, "nativePC/LuaScript/MainScript.lua");    // ��ȡLuaԴ�ļ����ڴ����
    if (error)
    {
        //LOG(ERR) << "dofile error";
        return -1;
    }
    lua_getglobal(L, "run");
    lua_pcall(L, 0, 0, 0);
    lua_close(L);
    return 1;
}