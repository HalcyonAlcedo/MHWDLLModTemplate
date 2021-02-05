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
    float duration = (float)lua_tonumber(pL, 3);
    Base::PlayerData::SetVisual(x,y,z, duration);
    return 0;
}
static int Gmae_Player_UnbindPlayerVisualCoordinate(lua_State* pL) {
    Base::PlayerData::UnbindVisual();
    return 0;
}
static int Gmae_Player_GetPlayerActionId(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::ActionId);
    return 1;
}
static int Gmae_Player_GetPlayerAngle(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Angle);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponId(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponId);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponType(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponType);
    return 1;
}
static int Gmae_Player_GetFsmData(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Fsm.Target);
    lua_pushnumber(pL, Base::PlayerData::Fsm.Id);
    return 2;
}
static int Gmae_Player_RunFsmAction(lua_State* pL) {
    int type = (int)lua_tonumber(pL, 1);
    int id = (int)lua_tonumber(pL, 2);
    Base::PlayerData::RunDerivedAction(type, id);
    return 0;
}
static int Gmae_Player_CheckRunFsmActionOver(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::CheckDerivedAction());
    return 1;
}
static int Gmae_World_GetMapId(lua_State* pL) {
    lua_pushnumber(pL, Base::World::MapId);
    return 1;
}
static int Game_Monster_SetFilter(lua_State* pL) {
    int id = (int)lua_tonumber(pL, 1);
    int subId = (int)lua_tonumber(pL, 2);
    Component::SetMonsterFilter(id,subId);
    return 0;
}
static int Game_Monster_DisableFilter(lua_State* pL) {
    Component::DisableMonsterFilter();
    return 0;
}
static int Game_Monster_SetBehaviorOfNavigationMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::NavigationMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNavigationMarkMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillNavigationMonster());
    return 1;
}
static int Game_Monster_SetBehaviorOfNearestMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::NearestMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNearestMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillNearestMonster());
    return 1;
}
static int Game_Monster_KillNearestMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushnumber(pL, Component::KillNearestMonster(min, max));
    return 1;
}
static int Game_Monster_SetBehaviorOfLastHitMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::LastHitMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillLastHitMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillLastHitMonster());
    return 1;
}
static int Game_Monster_AddDebuffToNavigationMarkMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetNavigationMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetNearestMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    lua_pushnumber(pL, Component::SetNearestMonsterBuff(buff, min, max));
    return 1;
}
static int Game_Monster_AddDebuffLastHitMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetLastHitMonsterBuff(buff));
    return 1;
}

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
    //��ȡ��������
    lua_register(L, "Gmae_Player_GetPlayerIncrementCoordinate", Gmae_Player_GetPlayerIncrementCoordinate);
    //��ȡ��������
    lua_register(L, "Gmae_Player_GetPlayerNavigationCoordinate", Gmae_Player_GetPlayerNavigationCoordinate);
    //��ȡ�������
    lua_register(L, "Gmae_Player_GetPlayerVisualCoordinate", Gmae_Player_GetPlayerVisualCoordinate);
    //����������꣨xyz�ͳ���ʱ��4��������
    lua_register(L, "Gmae_Player_SetPlayerVisualCoordinate", Gmae_Player_SetPlayerVisualCoordinate);
    //�����������
    lua_register(L, "Gmae_Player_UnbindPlayerVisualCoordinate", Gmae_Player_UnbindPlayerVisualCoordinate);
    //��ȡ��Ҷ���id
    lua_register(L, "Gmae_Player_GetPlayerActionId", Gmae_Player_GetPlayerActionId);
    //��ȡ����Ƕ�
    lua_register(L, "Gmae_Player_GetPlayerAngle", Gmae_Player_GetPlayerAngle);
    //�����Ч
    lua_register(L, "Gmae_Player_AddEffect", Gmae_Player_AddEffect);
    //��ȡ�������Id
    lua_register(L, "Gmae_Player_Weapon_GetWeaponId", Gmae_Player_Weapon_GetWeaponId);
    //��ȡ�����������
    lua_register(L, "Gmae_Player_Weapon_GetWeaponType", Gmae_Player_Weapon_GetWeaponType);
    //��ȡ���������Ϣ
    lua_register(L, "Gmae_Player_GetFsmData", Gmae_Player_GetFsmData);
    //ִ��ָ������������
    lua_register(L, "Gmae_Player_RunFsmAction", Gmae_Player_RunFsmAction);
    //���ִ�е����������Ƿ����
    lua_register(L, "Gmae_Player_CheckRunFsmActionOver", Gmae_Player_CheckRunFsmActionOver);

    //��ȡ��ǰ��ͼId
    lua_register(L, "Gmae_World_GetMapId", Gmae_World_GetMapId);
    
    //���ù���ɸѡ��
    lua_register(L, "Game_Monster_SetFilter", Game_Monster_SetFilter);
    //�������ɸѡ��
    lua_register(L, "Game_Monster_DisableFilter", Game_Monster_DisableFilter);
    //���Ƶ����������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfNavigationMonsters", Game_Monster_SetBehaviorOfNavigationMonsters);
    //ɱ��������ǵĹ���
    lua_register(L, "Game_Monster_KillNavigationMarkMonster", Game_Monster_KillNavigationMarkMonster);
    //��������ǵĹ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffToNavigationMarkMonster", Game_Monster_AddDebuffToNavigationMarkMonster);
    //���ƾ�������Ĺ������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfNearestMonsters", Game_Monster_SetBehaviorOfNearestMonsters);
    //ɱ����������Ĺ���
    lua_register(L, "Game_Monster_KillNearestMonster", Game_Monster_KillNearestMonster);
    //ɱ����Χ�ھ�������Ĺ���
    lua_register(L, "Game_Monster_KillNearestMonsterInRange", Game_Monster_KillNearestMonsterInRange);
    //����������Ĺ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffNearestMonster", Game_Monster_AddDebuffNearestMonster);
    //����Χ�ھ�������Ĺ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffNearestMonsterInRange", Game_Monster_AddDebuffNearestMonsterInRange);
    //�������һ�λ��еĹ������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfLastHitMonsters", Game_Monster_SetBehaviorOfLastHitMonsters);
    //ɱ�����һ�λ��еĹ���
    lua_register(L, "Game_Monster_KillLastHitMonster", Game_Monster_KillLastHitMonster);
    //�����һ�λ��еĹ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffLastHitMonster", Game_Monster_AddDebuffLastHitMonster);
    
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
    //����Ϸ�ڷ�����Ϣ
    lua_register(L, "System_Message_ShowMessage", System_Message_ShowMessage);
    //�����̨������Ϣ
    lua_register(L, "System_Console_Info", System_Console_Info);
    //�����̨���ʹ�����Ϣ
    lua_register(L, "System_Console_Error", System_Console_Error);
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