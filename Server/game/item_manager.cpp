/* File: game/item_manager.cpp */

//Search:
#include "cube.h"

//Add after:
#ifdef __INGAME_WIKI__
	#include "refine.h"
#endif

//-----------------------------------//

//Add on the end of file:
#ifdef __INGAME_WIKI__
DWORD ITEM_MANAGER::GetWikiItemStartRefineVnum(DWORD dwVnum)
{
	auto baseItemName = GetWikiItemBaseRefineName(dwVnum);
	if (!baseItemName.size())
		return 0;
	
	DWORD manage_vnum = dwVnum;
	while (!(strcmp(baseItemName.c_str(), GetWikiItemBaseRefineName(manage_vnum).c_str())))
		--manage_vnum;
	
	return (manage_vnum + 1);
}

std::string ITEM_MANAGER::GetWikiItemBaseRefineName(DWORD dwVnum)
{
	auto* tbl = GetTable(dwVnum);
	if (!tbl)
		return "";

	auto* p = const_cast<char*>(strrchr(tbl->szLocaleName, '+'));
	if (!p)
		return "";
	
	std::string sFirstItemName(tbl->szLocaleName,
				(tbl->szLocaleName + (p - tbl->szLocaleName)));
	
	return sFirstItemName;
}

int ITEM_MANAGER::GetWikiMaxRefineLevel(DWORD dwVnum)
{
	DWORD manage_vnum = (GetWikiItemStartRefineVnum(dwVnum) + 1);
	if (manage_vnum <= 1)
		return CommonWikiData::MAX_REFINE_COUNT;
	
	int refine_count = 0;
	std::string firstName, secondName;
	
	while (GetRefineFromVnum(manage_vnum) != 0)
	{
		firstName = GetWikiItemBaseRefineName(manage_vnum);
		secondName = GetWikiItemBaseRefineName(dwVnum);
		
		if (strcmp(firstName.c_str(), secondName.c_str()))
			break;
		
		++manage_vnum;
		++refine_count;
	}
	
	return MAX(refine_count, CommonWikiData::MAX_REFINE_COUNT);
}

CommonWikiData::TWikiInfoTable* ITEM_MANAGER::GetItemWikiInfo(DWORD vnum)
{
	auto it = m_wikiInfoMap.find(vnum);
	if (it != m_wikiInfoMap.end())
		return it->second.get();
	
	auto* tbl = GetTable(vnum);
	if (!tbl)
		return nullptr;
	
	auto newTable = new CommonWikiData::TWikiInfoTable();
	newTable->is_common = false;
	
	for (int it = 0; it < MOB_RANK_MAX_NUM && !newTable->is_common; ++it)
		for (auto it2 = g_vec_pkCommonDropItem[it].begin(); it2 != g_vec_pkCommonDropItem[it].end() && !newTable->is_common; ++it2)
			if (it2->m_dwVnum == vnum)
				newTable->is_common = true;
	
	newTable->origin_vnum = 0;
	newTable->chest_info_count = 0;
	m_wikiInfoMap.insert(std::make_pair(vnum, std::unique_ptr<CommonWikiData::TWikiInfoTable>(newTable)));
	
	if ((tbl->bType == ITEM_WEAPON || tbl->bType == ITEM_ARMOR || tbl->bType == ITEM_BELT) && vnum % 10 == 0 && tbl->dwRefinedVnum)
		newTable->refine_infos_count = GetWikiMaxRefineLevel(vnum);
	else if (tbl->bType == ITEM_GIFTBOX || (tbl->bType == ITEM_USE && tbl->bSubType == USE_SPECIAL))
	{
		CSpecialItemGroup* ptr = nullptr;
		auto it = m_map_pkSpecialItemGroup.find(vnum);
		if (it == m_map_pkSpecialItemGroup.end())
		{
			it = m_map_pkQuestItemGroup.find(vnum);
			if (it != m_map_pkQuestItemGroup.end())
				ptr = it->second;
		}
		else
			ptr = it->second;
		
		if (ptr)
			newTable->chest_info_count = ptr->m_vecItems.size();
	}

	return newTable;
}

std::vector<CommonWikiData::TWikiRefineInfo> ITEM_MANAGER::GetWikiRefineInfo(DWORD vnum)
{
	std::vector<CommonWikiData::TWikiRefineInfo> _rV;
	_rV.clear();
	
	auto* tbl = GetTable(vnum);
	if (!tbl)
		return _rV;
	
	const TRefineTable* refTbl;
	auto* tblTemp = tbl;
	bool success = true;
	const int maxRefineLevelCount = GetWikiMaxRefineLevel(vnum);
	
	for (BYTE i = 0; i < maxRefineLevelCount; ++i)
	{
		if (!tblTemp) {
			success = false;
			break;
		}
		
		refTbl = CRefineManager::instance().GetRefineRecipe(tblTemp->wRefineSet);
		if (!refTbl) {
			success = false;
			break;
		}
		
		CommonWikiData::TWikiRefineInfo tmpStruct;
		tmpStruct.index = i;
		tmpStruct.mat_count = refTbl->material_count;
		tmpStruct.price = refTbl->cost;
		
		for (auto j = 0; j < CommonWikiData::REFINE_MATERIAL_MAX_NUM; ++j)
		{
			tmpStruct.materials[j].vnum = refTbl->materials[j].vnum;
			tmpStruct.materials[j].count = refTbl->materials[j].count;
		}
		
		_rV.emplace_back(tmpStruct);
		tblTemp = GetTable(tblTemp->dwVnum + 1);
	}
	
	return (success ? _rV : std::vector<CommonWikiData::TWikiRefineInfo>());
}

std::vector<CSpecialItemGroup::CSpecialItemInfo> ITEM_MANAGER::GetWikiChestInfo(DWORD vnum)
{
	std::vector<CSpecialItemGroup::CSpecialItemInfo> _rV;
	_rV.clear();
	
	auto* tbl = GetTable(vnum);
	if (!tbl)
		return _rV;
	
	if (tbl->bType == ITEM_GIFTBOX && (tbl->bType == ITEM_USE && tbl->bSubType == USE_SPECIAL))
	{
		CSpecialItemGroup* ptr = nullptr;
		auto it = m_map_pkSpecialItemGroup.find(vnum);
		if (it == m_map_pkSpecialItemGroup.end())
		{
			it = m_map_pkQuestItemGroup.find(vnum);
			if (it != m_map_pkQuestItemGroup.end())
				ptr = it->second;
		}
		else
			ptr = it->second;

		_rV.assign(ptr->m_vecItems.begin(), ptr->m_vecItems.end());
	}
	
	return _rV;
}
#endif
