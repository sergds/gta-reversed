#include "StdInc.h"

COccluder(&COcclusion::aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS] = *(COccluder(*)[MAX_INTERIOR_OCCLUDERS])0xC73CC8;
COccluder(&COcclusion::aOccluders)[MAX_MAP_OCCLUDERS] = *(COccluder(*)[MAX_MAP_OCCLUDERS])0xC73FA0;
CActiveOccluder(&COcclusion::aActiveOccluders)[MAX_ACTIVE_OCCLUDERS] = *(CActiveOccluder(*)[MAX_ACTIVE_OCCLUDERS])0xC78610;

int& COcclusion::NumInteriorOcculdersOnMap = *(int*)0xC73CC4;
int& COcclusion::NumOccludersOnMap = *(int*)0xC73F98;
int& COcclusion::NumActiveOccluders = *(int*)0xC73CC0;
short& COcclusion::FarAwayList = *(short*)0x8D5D68;
short& COcclusion::NearbyList = *(short*)0x8D5D6C;
short& COcclusion::ListWalkThroughFA = *(short*)0x8D5D70;
short& COcclusion::PreviousListWalkThroughFA = *(short*)0x8D5D74;

float& COcclusion::gMinXInOccluder = *(float*)0xC73CAC;
float& COcclusion::gMaxXInOccluder = *(float*)0xC73CA8;
float& COcclusion::gMinYInOccluder = *(float*)0xC73CA4;
float& COcclusion::gMaxYInOccluder = *(float*)0xC73CA0;

bool(&COcclusion::gOccluderCoorsValid)[8] = *(bool(*)[8])0xC73CB0;
CVector(&COcclusion::gOccluderCoors)[8] = *(CVector(*)[8])0xC798E0;
CVector(&COcclusion::gOccluderCoorsOnScreen)[8] = *(CVector(*)[8])0xC79950;
CVector& COcclusion::gCenterOnScreen = *(CVector*)0xC79940;

void COcclusion::InjectHooks()
{
    ReversibleHooks::Install("COcclusion", "Init", 0x71DCA0, &COcclusion::Init);
}

void COcclusion::Init()
{
    COcclusion::NumOccludersOnMap = 0;
    COcclusion::NumInteriorOcculdersOnMap = 0;
    COcclusion::FarAwayList = -1;
    COcclusion::NearbyList = -1;
    COcclusion::ListWalkThroughFA = -1;
    COcclusion::PreviousListWalkThroughFA = -1;
}

void COcclusion::AddOne(float dirMidX, float dirMidY, float dirMidZ, float widthX, float widthY, float height, float rotX, float rotY, float rotZ, float flags, bool isInterior)
{
    plugin::Call<0x71DCD0, float, float, float, float, float, float, float, float, float, float, bool>
        (dirMidX, dirMidY, dirMidZ, widthX, widthY, height, rotX, rotY, rotZ, flags, isInterior);
}

bool COcclusion::OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second)
{
    return plugin::CallAndReturn<bool, 0x71E080, CActiveOccluder*, CActiveOccluder*>(first, second);
}

bool COcclusion::IsPositionOccluded(CVector vecPos, float fRadius)
{
    return plugin::CallAndReturn<bool, 0x7200B0, CVector, float>(vecPos, fRadius);
}

void COcclusion::ProcessBeforeRendering()
{
    plugin::Call<0x7201C0>();
}

bool CActiveOccluder::IsPointWithinOcclusionArea(float fX, float fY, float fRadius)
{
    return plugin::CallMethodAndReturn<bool, 0x71E580, CActiveOccluder*, float, float, float>(this, fX, fY, fRadius);
}

bool CActiveOccluder::IsPointBehindOccluder(CVector vecPos, float fRadius)
{
    return plugin::CallMethodAndReturn<bool, 0x71FA40, CActiveOccluder*, CVector, float>(this, vecPos, fRadius);
}

void COccluder::ProcessOneOccluder(CActiveOccluder* pActiveOccluder)
{
    plugin::CallMethod<0x71E5D0, COccluder*, CActiveOccluder*>(this, pActiveOccluder);
}

void COccluder::ProcessLineSegment(int iInd1, int iInd2, CActiveOccluder* pActiveOccluder)
{
    plugin::CallMethod<0x71E130, COccluder*, int, int, CActiveOccluder*>(this, iInd1, iInd2, pActiveOccluder);
}
