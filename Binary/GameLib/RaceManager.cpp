/* File: GameLib/RaceManager.h */

//Search:
BOOL CRaceManager::GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData)

//Replace with:
#ifdef INGAME_WIKI
BOOL CRaceManager::GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData, bool printTrace)
#else
BOOL CRaceManager::GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData)
#endif

//-----------------------------------//

//Search -> Inside GetRaceDataPointer function:
		TraceError("CRaceManager::GetRaceDataPointer: cannot load data by dwRaceIndex %lu", dwRaceIndex);

//Replace with:
#ifdef INGAME_WIKI
		if (printTrace)
			TraceError("CRaceManager::GetRaceDataPointer: cannot load data by dwRaceIndex %lu", dwRaceIndex);
#else
		TraceError("CRaceManager::GetRaceDataPointer: cannot load data by dwRaceIndex %lu", dwRaceIndex);
#endif