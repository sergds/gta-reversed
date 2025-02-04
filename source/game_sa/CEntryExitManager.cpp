#include "StdInc.h"

CEntryExit* (&CEntryExitManager::ms_entryExitStack)[4] = *reinterpret_cast<CEntryExit * (*)[4]>(0x96A720);
bool& CEntryExitManager::ms_bBurglaryHousesEnabled = *reinterpret_cast<bool*>(0x96A730);
int& CEntryExitManager::ms_oldAreaCode = *reinterpret_cast<int*>(0x96A734);
CEntity* (&CEntryExitManager::ms_visibleEntityList)[32] = *reinterpret_cast<CEntity * (*)[32]>(0x96A738);
int& CEntryExitManager::ms_entryExitStackPosn = *reinterpret_cast<int*>(0x96A7C4);
bool& CEntryExitManager::ms_bDisabled = *reinterpret_cast<bool*>(0x96A7C8);
int& CEntryExitManager::ms_exitEnterState = *reinterpret_cast<int*>(0x96A7CC);
CQuadTreeNode*& CEntryExitManager::mp_QuadTree = *reinterpret_cast<CQuadTreeNode**>(0x96A7D0);
CEntryExit*& CEntryExitManager::mp_Active = *reinterpret_cast<CEntryExit**>(0x96A7D4);
CPool<CEntryExit>*& CEntryExitManager::mp_poolEntryExits = *reinterpret_cast<CPool<CEntryExit>**>(0x96A7D8);
unsigned int& CEntryExitManager::ms_numVisibleEntities = *reinterpret_cast<unsigned int*>(0x96A7DC);

void CEntryExitManager::InjectHooks() {
//    ReversibleHooks::Install("CEntryExitManager", "Init", 0x43F880, &CEntryExitManager::Init);
//    ReversibleHooks::Install("CEntryExitManager", "Update", 0x440D10, &CEntryExitManager::Update);
//    ReversibleHooks::Install("CEntryExitManager", "Shutdown", 0x440B90, &CEntryExitManager::Shutdown);
//    ReversibleHooks::Install("CEntryExitManager", "ShutdownForRestart", 0x440C40, &CEntryExitManager::ShutdownForRestart);
}

// 0x43F880
void CEntryExitManager::Init() {
    plugin::Call<0x43F880>();
}

// 0x440D10
void CEntryExitManager::Update() {
    plugin::Call<0x440D10>();
}

// 0x440B90
void CEntryExitManager::Shutdown() {
    plugin::Call<0x440D10>();
}

// 0x440C40
void CEntryExitManager::ShutdownForRestart() {
    plugin::Call<0x440C40>();
}

int CEntryExitManager::AddOne(float entranceX, float entranceY, float entranceZ, float entranceAngle, float entranceRangeX, float entranceRangeY, float fUnused, float exitX, float exitY, float exitZ, float exitAngle, int area, int flags, int skyColor, int timeOn, int timeOff, int numberOfPeds, char const* name)
{
    return plugin::CallAndReturn<int, 0x43FA00, float, float, float, float, float, float, float, float, float, float, float, int, int, int, int, int, int, char const*>
        (entranceX, entranceY, entranceZ, entranceAngle, entranceRangeX, entranceRangeY, fUnused, exitX, exitY, exitZ, exitAngle, area, flags, skyColor, timeOn, timeOff, numberOfPeds, name);
}

void CEntryExitManager::DeleteOne(int index)
{
    plugin::Call<0x43FD50, int>(index);
}

int CEntryExitManager::FindNearestEntryExit(CVector2D const& position, float range, int ignoreArea)
{
    return plugin::CallAndReturn<int, 0x43F4B0, CVector2D const&, float, int>(position, range, ignoreArea);
}

// 0x43F0A0
void CEntryExitManager::PostEntryExitsCreation() {
    plugin::Call<0x43F0A0>();
}
