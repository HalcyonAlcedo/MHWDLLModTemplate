#pragma once
#include <Psapi.h>

namespace AobAddress {
    typedef unsigned char byte;

    struct vector<byte> Player_BasePtr = { 0xA0, 0x81, 0x1B, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x20 };
    struct vector<byte> Player_PlayerBasePlot = { 0x60, 0xD5, 0xB7, 0x3B, 0x00 };
    struct vector<byte> Player_ActionTrigger = { 0x46, 0x89, 0x4C, 0xD1, 0x1C };
    struct vector<byte> Player_Effects = { 0xE9, 0xFB, 0xC8, 0xFF, 0xFF };
    struct vector<byte> Player_Visual = { 0x11, 0x4B, 0x08, 0x48, 0x8B, 0x5C, 0x24, 0x60 };
    struct vector<byte> Player_PlayerDataPlot = { 0xF0, 0xD9, 0xAA, 0x3B, 0x00, 0x00, 0x00 };
    struct vector<byte> EnvironmentalBiological_ctor = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x83, 0xEC, 0x60, 0x8B, 0xDA };
    struct vector<byte> World_WaypointZLocal = { 0xF3, 0x0F, 0x10, 0x85, 0xD8, 0x02, 0x00, 0x00 };
    struct vector<byte> World_MapClockLocal = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x50, 0x48, 0x8B, 0xD9, 0x0F, 0x29, 0x7C };
    struct vector<byte> World_GmaeClock = { 0xD0, 0x58, 0x22, 0x3B, 0x00 };
    struct vector<byte> World_GmaeClockControl = { 0xF3, 0x0F, 0x11, 0x41, 0x38, 0x8B };
    struct vector<byte> Shlp_GetShlp = { 0x3B, 0x91, 0xB0, 0x00, 0x00, 0x00, 0x72, 0x03, 0x33, 0xC0, 0xC3, 0x8B, 0xC2, 0x48, 0xC1, 0xE0, 0x04 };
    struct vector<byte> Shlp_CallShlp = { 0x48, 0x8B, 0xC4, 0x57, 0x48, 0x81, 0xEC, 0x90, 0x01, 0x00, 0x00 };
    struct vector<byte> Monster_dtor = { 0x03, 0x48, 0x8B, 0x5C, 0x24, 0x30, 0x48, 0x83, 0xC4, 0x20, 0x5F, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C };
    struct vector<byte> Monster_ctor = { 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x44, 0x89, 0x44, 0x24, 0x18, 0x89 };
    struct vector<byte> Weapon_ChangeWeapon = { 0x48, 0x8B, 0xC4, 0x55, 0x41, 0x54, 0x48, 0x81 };
    struct vector<byte> Weapon_WeaponOrnaments = { 0x48, 0x81, 0xC4, 0x50, 0x01, 0x00, 0x00, 0x5F, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x8B };
    struct vector<byte> Weapon_MainWeaponPtr = { 0x48, 0x83, 0xC4, 0x50, 0x5B, 0xC3, 0xCC, 0x48, 0x89, 0x5C, 0x24, 0x10, 0x55 };
    struct vector<byte> Weapon_SecondaryWeaponPtr = { 0x1E, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x38, 0x49, 0x8B, 0xE3, 0x41, 0x5F, 0x41, 0x5E, 0x41, 0x5D };
    struct vector<byte> Chat_MainPtr = { 0x20, 0xF7, 0xB7, 0x3B, 0x00, 0x00 };
    struct vector<byte> Chat_ShowGameMessage = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00, 0x80 };

    static vector<byte*> scanmem(const vector<byte>& bytes)
    {
        vector<byte*> results;
        auto module = GetModuleHandle("MonsterHunterWorld.exe");
        if (module == nullptr) return results;

        MODULEINFO moduleInfo;
        if (!GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo)))
            return results;

        byte* startAddr = (byte*)module;
        byte* endAddr = startAddr + moduleInfo.SizeOfImage;
        byte* addr = startAddr;

        while (addr < endAddr)
        {
            MEMORY_BASIC_INFORMATION memInfo;
            if (!VirtualQuery(addr, &memInfo, sizeof(memInfo)) || memInfo.State != MEM_COMMIT || (memInfo.Protect & PAGE_GUARD))
                continue;
            byte* begin = (byte*)memInfo.BaseAddress;
            byte* end = begin + memInfo.RegionSize;


            byte* found = search(begin, end, bytes.begin(), bytes.end());
            while (found != end) {
                results.push_back(found);
                found = search(found + 1, end, bytes.begin(), bytes.end());
            }

            addr = end;
            memInfo = {};
        }

        return results;
    }

    static long long AobScanmem(vector<byte> AobData) {
        auto ScanmemData = scanmem(AobData);
        if (ScanmemData.size() == 1) {
            return (long long)ScanmemData[0];
        }
        else {
            return 0x0;
        }
    }

    static void InitAobAddress() {
        map<string, long long> AobScanmems;
        AobScanmems["Player_BasePtr"] = AobScanmem(Player_BasePtr);

        for (auto [name, address] : AobScanmems) {
            if (name == "Player_BasePtr" and address != 0x0)
                MH::Player::BasePtr = (void*)address;
        }
    }
}

