/* File: Userinterface/PythonNonPlayer.cpp */

//Search -> Inside LoadNonPlayerData function:
		TMobTable* pNonPlayerData = new TMobTable;
		memcpy(pNonPlayerData, pTable, sizeof(TMobTable));
		m_NonPlayerDataMap.insert(TNonPlayerDataMap::value_type(pNonPlayerData->dwVnum, pNonPlayerData));

//Replace with:
#ifdef INGAME_WIKI
		auto ptr = std::make_unique <TMobTable>();
		*ptr = t;
		m_NonPlayerDataMap[t.dwVnum].mobTable = std::move(ptr);
		m_NonPlayerDataMap[t.dwVnum].isSet = false;
		m_NonPlayerDataMap[t.dwVnum].isFiltered = false;
		m_NonPlayerDataMap[t.dwVnum].dropList.clear();
#else
		TMobTable* pNonPlayerData = new TMobTable;
		memcpy(pNonPlayerData, pTable, sizeof(TMobTable));
		m_NonPlayerDataMap.insert(TNonPlayerDataMap::value_type(pNonPlayerData->dwVnum, pNonPlayerData));
#endif

//-----------------------------------//

//Search -> Inside GetTable function:
	return itor->second;

//Replace with:
#ifdef INGAME_WIKI
	return itor->second.mobTable.get();
#else
	return itor->second;
#endif

//-----------------------------------//

//Search:
void CPythonNonPlayer::Clear()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
#include "../GameLib/RaceManager.h"

bool CPythonNonPlayer::CanRenderMonsterModel(DWORD dwMonsterVnum)
{
	CRaceData * pRaceData;
	if (!CRaceManager::Instance().GetRaceDataPointer(dwMonsterVnum, &pRaceData, false))
		return false;
	
	return true;
}

size_t CPythonNonPlayer::WikiLoadClassMobs(BYTE bType, unsigned short fromLvl, unsigned short toLvl)
{
	m_vecTempMob.clear();
	for (auto it = m_NonPlayerDataMap.begin(); it != m_NonPlayerDataMap.end(); ++it)
	{
		if (!it->second.isFiltered && it->second.mobTable->bLevel >= fromLvl &&
			it->second.mobTable->bLevel < toLvl && CanRenderMonsterModel(it->second.mobTable->dwVnum))
		{
			if (bType == 0 && it->second.mobTable->bType == MONSTER && it->second.mobTable->bRank >= 4)
				m_vecTempMob.push_back(it->first);
			else if (bType == 1 && it->second.mobTable->bType == MONSTER && it->second.mobTable->bRank < 4)
				m_vecTempMob.push_back(it->first);
			else if (bType == 2 && it->second.mobTable->bType == STONE)
				m_vecTempMob.push_back(it->first);
		}
	}
	
	return m_vecTempMob.size();
}

void CPythonNonPlayer::WikiSetBlacklisted(DWORD vnum)
{
	auto it = m_NonPlayerDataMap.find(vnum);
		if (it != m_NonPlayerDataMap.end())
			it->second.isFiltered = true;
}

std::tuple<const char*, int> CPythonNonPlayer::GetMonsterDataByNamePart(const char* namePart)
{
	char searchName[CHARACTER_NAME_MAX_LEN + 1];
	memcpy(searchName, namePart, sizeof(searchName));
	for (size_t j = 0; j < sizeof(searchName); j++)
		searchName[j] = static_cast<char>(tolower(searchName[j]));
	std::string tempSearchName = searchName;

	TNonPlayerDataMap::iterator itor = m_NonPlayerDataMap.begin();
	for (; itor != m_NonPlayerDataMap.end(); ++itor)
	{
		TMobTable* pMobTable = itor->second.mobTable.get();
		
		if (itor->second.isFiltered)
			continue;
		
		const char * mobBaseName = CPythonNonPlayer::Instance().GetNameString(pMobTable->dwVnum).c_str();
		std::string tempName = mobBaseName;
		if (!tempName.size())
			continue;
		
		std::transform(tempName.begin(), tempName.end(), tempName.begin(), ::tolower);

		const size_t tempSearchNameLenght = tempSearchName.length();
		if (tempName.length() < tempSearchNameLenght)
			continue;

		if (!tempName.substr(0, tempSearchNameLenght).compare(tempSearchName))
			return std::make_tuple(mobBaseName, pMobTable->dwVnum);
	}

	return std::make_tuple("", -1);
}

void CPythonNonPlayer::BuildWikiSearchList()
{
	m_vecWikiNameSort.clear();
	for (auto it = m_NonPlayerDataMap.begin(); it != m_NonPlayerDataMap.end(); ++it)
		if (!it->second.isFiltered)
			m_vecWikiNameSort.push_back(it->second.mobTable.get());
	
	SortMobDataName();
}

void CPythonNonPlayer::SortMobDataName()
{
	std::qsort(&m_vecWikiNameSort[0], m_vecWikiNameSort.size(), sizeof(m_vecWikiNameSort[0]), [](const void* a, const void* b)
		{
			TMobTable* pItem1 = *(TMobTable**)(static_cast<const TMobTable*>(a));
			std::string stRealName1 = pItem1->szLocaleName;
			std::transform(stRealName1.begin(), stRealName1.end(), stRealName1.begin(), ::tolower);
			
			TMobTable* pItem2 = *(TMobTable**)(static_cast<const TMobTable*>(b));
			std::string stRealName2 = pItem2->szLocaleName;
			std::transform(stRealName2.begin(), stRealName2.end(), stRealName2.begin(), ::tolower);
			
			int iSmallLen = min(stRealName1.length(), stRealName2.length());
			int iRetCompare = stRealName1.compare(0, iSmallLen, stRealName2, 0, iSmallLen);
			
			if (iRetCompare != 0)
				return iRetCompare;
			
			if (stRealName1.length() < stRealName2.length())
				return -1;
			else if (stRealName2.length() < stRealName1.length())
				return 1;
			
			return 0;
		});
}

CPythonNonPlayer::TWikiInfoTable* CPythonNonPlayer::GetWikiTable(DWORD dwVnum)
{
	TNonPlayerDataMap::iterator itor = m_NonPlayerDataMap.find(dwVnum);

	if (itor == m_NonPlayerDataMap.end())
		return NULL;

	return &(itor->second);
}
#endif

//-----------------------------------//

//Search -> Inside Destroy routine:
		delete itor->second;

//Replace with:
#ifdef INGAME_WIKI
		m_NonPlayerDataMap.erase(itor);
#else
		delete itor->second;
#endif
