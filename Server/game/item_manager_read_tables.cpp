/* File: game/item_manager_read_tables.cpp */

//Search:
#include "group_text_parse_tree.h"

//Add after:
#ifdef __INGAME_WIKI__
	#include "../../common/in_game_wiki.h"
	#include "mob_manager.h"
#endif

//-----------------------------------//

//Search -> Inside ReadSpecialDropItemFile function:
					int iRarePct = 0;
					if (pTok->size() > 3)
					{
						str_to_number(iRarePct, pTok->at(3).c_str());
					}

					sys_log(0,"        name %s count %d prob %d rare %d", name.c_str(), iCount, iProb, iRarePct);
					pkGroup->AddItem(dwVnum, iCount, iProb, iRarePct);

//Add after:
#ifdef __INGAME_WIKI__
					auto pTableTemp = GetTable(dwVnum);
					DWORD addVnum = dwVnum;
					DWORD startRefineVnum = GetWikiItemStartRefineVnum(dwVnum);
					
					if (pTableTemp && (pTableTemp->bType == ITEM_WEAPON || pTableTemp->bType == ITEM_ARMOR) && startRefineVnum != addVnum)
						addVnum = (startRefineVnum != 0 ? startRefineVnum : addVnum);
					
					CommonWikiData::TWikiItemOriginInfo origin_info;
					origin_info.set_vnum(iVnum);
					origin_info.set_is_mob(false);
					
					m_itemOriginMap[addVnum].push_back(origin_info);
#endif

//-----------------------------------//

//Search -> Inside ReadMonsterDropItemGroup function:
					if (iPartPct == 0)
					{
						sys_err("ReadMonsterDropItemGroup : there is no drop percent for item %s : node %s : vnum %d, count %d, pct %d", name.c_str(), stName.c_str(), iPartPct);
						return false;
					}

					int iRarePct = 0;
					str_to_number(iRarePct, pTok->at(3).c_str());
					iRarePct = MINMAX(0, iRarePct, 100);

					sys_log(0,"        %s count %d rare %d", name.c_str(), iCount, iRarePct);
					pkGroup->AddItem(dwVnum, iCount, iPartPct, iRarePct);

//Add after:
#ifdef __INGAME_WIKI__
					CommonWikiData::TWikiInfoTable* tbl;
					if ((tbl = GetItemWikiInfo(dwVnum)) && !tbl->origin_vnum)
						tbl->origin_vnum = iMobVnum;

					auto pTableTemp = GetTable(dwVnum);
					DWORD currVnum = dwVnum;
					DWORD startRefineVnum = GetWikiItemStartRefineVnum(dwVnum);
					
					if (pTableTemp && (pTableTemp->bType == ITEM_WEAPON || pTableTemp->bType == ITEM_ARMOR) && startRefineVnum != currVnum)
						currVnum = (startRefineVnum != 0 ? startRefineVnum : currVnum);
					
					CommonWikiData::TWikiItemOriginInfo origin_info;
					origin_info.set_vnum(iMobVnum);
					origin_info.set_is_mob(true);
					
					m_itemOriginMap[currVnum].push_back(origin_info);
					CMobManager::instance().GetMobWikiInfo(iMobVnum).push_back(CommonWikiData::TWikiMobDropInfo(dwVnum, iCount));
#endif

//-----------------------------------//

//Search -> Inside ReadMonsterDropItemGroup function:
					if (iCount < 1)
					{
						sys_err("ReadMonsterDropItemGroup : there is no count for item %s : node %s", name.c_str(), stName.c_str());
						M2_DELETE(pkGroup);

						return false;
					}

					float fPercent = atof(pTok->at(2).c_str());

					DWORD dwPct = (DWORD)(10000.0f * fPercent);

					sys_log(0,"        name %s pct %d count %d", name.c_str(), dwPct, iCount);
					pkGroup->AddItem(dwVnum, dwPct, iCount);

//Add after:
#ifdef __INGAME_WIKI__
					CommonWikiData::TWikiInfoTable* tbl;
					if ((tbl = GetItemWikiInfo(dwVnum)) && !tbl->origin_vnum)
						tbl->origin_vnum = iMobVnum;

					auto pTableTemp = GetTable(dwVnum);
					DWORD currVnum = dwVnum;
					DWORD startRefineVnum = GetWikiItemStartRefineVnum(dwVnum);
					
					if (pTableTemp && (pTableTemp->bType == ITEM_WEAPON || pTableTemp->bType == ITEM_ARMOR) && startRefineVnum != currVnum)
						currVnum = startRefineVnum != 0 ? startRefineVnum : currVnum;

					CommonWikiData::TWikiItemOriginInfo origin_info;
					origin_info.set_vnum(iMobVnum);
					origin_info.set_is_mob(true);
					
					m_itemOriginMap[currVnum].push_back(origin_info);
					CMobManager::instance().GetMobWikiInfo(iMobVnum).push_back(CommonWikiData::TWikiMobDropInfo(dwVnum, iCount));
#endif

//-----------------------------------//

//Search -> Inside ReadMonsterDropItemGroup function:
					if (iCount < 1)
					{
						sys_err("ReadMonsterDropItemGroup : there is no count for item %s : node %s", name.c_str(), stName.c_str());
						M2_DELETE(pkLevelItemGroup);
						return false;
					}

					float fPct = atof(pTok->at(2).c_str());
					DWORD dwPct = (DWORD)(10000.0f * fPct);

					sys_log(0,"        name %s pct %d count %d", name.c_str(), dwPct, iCount);
					pkLevelItemGroup->AddItem(dwItemVnum, dwPct, iCount);

//Add after:
#ifdef __INGAME_WIKI__
					CommonWikiData::TWikiInfoTable* tbl;
					if ((tbl = GetItemWikiInfo(dwItemVnum)) && !tbl->origin_vnum)
						tbl->origin_vnum = iMobVnum;

					auto pTableTemp = GetTable(dwItemVnum);
					DWORD currVnum = dwItemVnum;
					DWORD startRefineVnum = GetWikiItemStartRefineVnum(dwItemVnum);
					
					if (pTableTemp && (pTableTemp->bType == ITEM_WEAPON || pTableTemp->bType == ITEM_ARMOR) && startRefineVnum != currVnum)
						currVnum = startRefineVnum != 0 ? startRefineVnum : currVnum;

					CommonWikiData::TWikiItemOriginInfo origin_info;
					origin_info.set_vnum(iMobVnum);
					origin_info.set_is_mob(true);
					
					m_itemOriginMap[currVnum].push_back(origin_info);
					CMobManager::instance().GetMobWikiInfo(iMobVnum).push_back(CommonWikiData::TWikiMobDropInfo(dwItemVnum, iCount));
#endif
