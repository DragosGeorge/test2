/* File: GameLib/RaceManager.h */

//Search -> Inside CRaceManager class:
		BOOL GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData);

//Replace with:
#ifdef INGAME_WIKI
		BOOL GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData, bool printTrace = true);
#else
		BOOL GetRaceDataPointer(DWORD dwRaceIndex, CRaceData ** ppRaceData);
#endif
