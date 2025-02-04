#include "StdInc.h"

#include "CSimpleVariablesSaveStructure.h"
#include "GxtChar.h"

#define SAVEGAME_MAX_NAME_LEN 22

void CSimpleVariablesSaveStructure::InjectHooks() {
    ReversibleHooks::Install("CSimpleVariablesSaveStructure", "Construct", 0x5D1B80, &CSimpleVariablesSaveStructure::Construct);
    ReversibleHooks::Install("CSimpleVariablesSaveStructure", "Extract", 0x5D1EA0, &CSimpleVariablesSaveStructure::Extract);
}

// 0x5D1B80
void CSimpleVariablesSaveStructure::Construct() {
    const char* saveName;
    if (CStats::LastMissionPassedName[0]) {
        saveName = TheText.Get(CStats::LastMissionPassedName);
    } else if (CGame::bMissionPackGame) {
        saveName = TheText.Get("MPACKID");
    } else {
        saveName = TheText.Get("ITBEG");
    }

    char dots[8];
    AsciiToGxtChar("...'", dots); // dot dot dot apostrophe
    TextCopy(m_szSaveName, saveName);
    unsigned int strLen = GxtCharStrlen(m_szSaveName);
    if (strLen > SAVEGAME_MAX_NAME_LEN) {
        TextCopy(&m_szSaveName[SAVEGAME_MAX_NAME_LEN - 3 - 1], dots);
    }
    m_szSaveName[SAVEGAME_MAX_NAME_LEN + 1] = '\0';

    m_nVersionId = CGenericGameStorage::GetCurrentVersionNumber();

    m_bLARiots = gbLARiots;
    m_bLARiots_NoPoliceCar = gbLARiots_NoPoliceCars;
    m_bCineyCamMessageDisplayed = gbCineyCamMessageDisplayed;

    m_nCurrArea = CGame::currArea;
    m_nCurrLevel = CGame::currLevel;
    m_bMissionPackGame = CGame::bMissionPackGame;

    m_vecCamPosn = TheCamera.m_mCameraMatrix.GetPosition();
    m_nCameraCarZoom = TheCamera.m_nCarZoom;
    m_nCameraPedZoom = TheCamera.m_nPedZoom;

    m_nMsPerMinute = CClock::ms_nMillisecondsPerGameMinute;
    m_nLastClockTick = CClock::ms_nLastClockTick;
    m_nGameMonth = CClock::ms_nGameClockMonth;
    m_nGameDays = CClock::ms_nGameClockDays;
    m_nGameHours = CClock::ms_nGameClockHours;
    m_nGameMinutes = CClock::ms_nGameClockMinutes;
    m_nGameDayOfWeek = CClock::CurrentDay;
    m_nStoredGameMonth = CClock::ms_Stored_nGameClockMonths;
    m_nStoredGameMonthDay = CClock::ms_Stored_nGameClockDays;
    m_nStoredGameHours = CClock::ms_Stored_nGameClockHours;
    m_nStoredGameMinutes = CClock::ms_Stored_nGameClockMinutes;
    m_bClockHasBeenStored = CClock::bClockHasBeenStored;

    m_nTimeInMilliseconds = CTimer::m_snTimeInMilliseconds;
    m_fTimeScale = CTimer::ms_fTimeScale;
    m_fTimeStep = CTimer::ms_fTimeStep;
    m_fTimeStepNonClipped = CTimer::ms_fTimeStepNonClipped;
    m_nFrameCounter = CTimer::m_FrameCounter;

    m_nOldWeatherType = CWeather::OldWeatherType;
    m_nNewWeatherType = CWeather::NewWeatherType;
    m_nForcedWeatherType = CWeather::ForcedWeatherType;
    m_fWeatherInterpolationValue = CWeather::InterpolationValue;
    m_nWeatherTypeInList = CWeather::WeatherTypeInList;
    m_fWeatherRain = CWeather::Rain;

    m_nExtraColour = CTimeCycle::m_ExtraColour;
    m_bExtraColourOn = CTimeCycle::m_bExtraColourOn != false;
    m_fExtraColourInter = CTimeCycle::m_ExtraColourInter;
    m_nExtraColourWeatherType = CTimeCycle::m_ExtraColourWeatherType;

    m_nPadMode = CPad::GetPad(0)->Mode;
    m_bInvertLook4Pad = CPad::bInvertLook4Pad;

    m_nMaximumWantedLevel = CWanted::MaximumWantedLevel;
    m_nMaxChaos = CWanted::nMaximumWantedLevel;

    m_bGermanGame = CLocalisation::germanGame;
    m_bFrenchGame = CLocalisation::frenchGame;
    m_bNastyGame = CLocalisation::nastyGame;

    GetLocalTime(&m_systemTime);
    m_nWaterConfiguration = CWaterLevel::m_nWaterConfiguration;
    m_nTargetBlipIndex = FrontEndMenuManager.m_nTargetBlipIndex;
    m_bHasDisplayedPlayerQuitEnterCarHelpText = CPlayerPed::bHasDisplayedPlayerQuitEnterCarHelpText;

    m_bHasPlayerCheated = CCheat::m_bHasPlayerCheated;
    m_bAllTaxisNitro = CCheat::m_aCheatsActive[CHEAT_ALL_TAXIS_NITRO];
    m_bProstitutesPayYou = CCheat::m_aCheatsActive[CHEAT_PROSTITUTES_PAY_YOU];
}

// 0x5D1EA0
void CSimpleVariablesSaveStructure::Extract(unsigned int& versionId) const {
    versionId = m_nVersionId;

    gbLARiots = m_bLARiots;
    gbLARiots_NoPoliceCars = m_bLARiots_NoPoliceCar;
    gbCineyCamMessageDisplayed = m_bCineyCamMessageDisplayed;

    CGame::currArea = m_nCurrArea;
    CGame::currLevel = m_nCurrLevel;
    CGame::bMissionPackGame = m_bMissionPackGame;

    TheCamera.m_mCameraMatrix.SetTranslate(m_vecCamPosn);
    TheCamera.m_nCarZoom = m_nCameraCarZoom;
    TheCamera.m_nPedZoom = m_nCameraPedZoom;

    CClock::ms_nMillisecondsPerGameMinute = m_nMsPerMinute;
    CClock::ms_nLastClockTick = m_nLastClockTick;
    CClock::ms_nGameClockMonth = m_nGameMonth;
    CClock::ms_nGameClockDays = m_nGameDays;
    CClock::ms_nGameClockHours = m_nGameHours;
    CClock::ms_nGameClockMinutes = m_nGameMinutes;
    CClock::CurrentDay = m_nGameDayOfWeek;
    CClock::ms_Stored_nGameClockMonths = m_nStoredGameMonth;
    CClock::ms_Stored_nGameClockDays = m_nStoredGameMonthDay;
    CClock::ms_Stored_nGameClockHours = m_nStoredGameHours;
    CClock::ms_Stored_nGameClockMinutes = m_nStoredGameMinutes;
    CClock::bClockHasBeenStored = m_bClockHasBeenStored != 0;

    CTimer::m_snTimeInMilliseconds = m_nTimeInMilliseconds;
    if (m_nTimeInMilliseconds > 4140000000) { // UTC time & date: Tue Feb 17 1970 22:00:00
        CClock::ms_nLastClockTick = 1;
        CTimer::m_snTimeInMilliseconds = 1;
    }
    CTimer::ms_fTimeScale = m_fTimeScale;
    CTimer::ms_fTimeStep = m_fTimeStep;
    CTimer::ms_fTimeStepNonClipped = m_fTimeStepNonClipped;
    CTimer::m_FrameCounter = m_nFrameCounter;

    CWeather::OldWeatherType = m_nOldWeatherType;
    CWeather::NewWeatherType = m_nNewWeatherType;
    CWeather::ForcedWeatherType = m_nForcedWeatherType;
    CWeather::InterpolationValue = m_fWeatherInterpolationValue;
    CWeather::WeatherTypeInList = m_nWeatherTypeInList;
    CWeather::Rain = m_fWeatherRain;

    CTimeCycle::m_ExtraColour = m_nExtraColour;
    CTimeCycle::m_bExtraColourOn = m_bExtraColourOn;
    CTimeCycle::m_ExtraColourInter = m_fExtraColourInter;
    CTimeCycle::m_ExtraColourWeatherType = m_nExtraColourWeatherType;

    CPad::GetPad(0)->Mode = m_nPadMode;
    CPad::bInvertLook4Pad = m_bInvertLook4Pad;

    CWanted::MaximumWantedLevel = m_nMaximumWantedLevel;
    CWanted::nMaximumWantedLevel = m_nMaxChaos;

    CLocalisation::germanGame = m_bGermanGame;
    CLocalisation::frenchGame = m_bFrenchGame;
    CLocalisation::nastyGame = m_bNastyGame;

    CWaterLevel::m_nWaterConfiguration = m_nWaterConfiguration;
    FrontEndMenuManager.m_nTargetBlipIndex = m_nTargetBlipIndex;
    CPlayerPed::bHasDisplayedPlayerQuitEnterCarHelpText = m_bHasDisplayedPlayerQuitEnterCarHelpText;

    static constexpr void (*pTaxiNitroCheat)() = nullptr;
    static constexpr void (*pProstitutesPayYouCheat)() = nullptr;

    CCheat::m_bHasPlayerCheated = m_bHasPlayerCheated;
    if (m_bAllTaxisNitro) {
        if (pTaxiNitroCheat)
            pTaxiNitroCheat();
        else
            CCheat::m_aCheatsActive[CHEAT_ALL_TAXIS_NITRO] ^= true;
    }
    if (m_bProstitutesPayYou) {
        if (pProstitutesPayYouCheat)
            pProstitutesPayYouCheat();
        else
            CCheat::m_aCheatsActive[CHEAT_PROSTITUTES_PAY_YOU] ^= true;
    }
}
