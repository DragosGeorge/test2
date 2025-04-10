/* File: game/mob_manager.h */

//Search:
#ifndef __INC_METIN_II_MOB_MANAGER_H__
#define __INC_METIN_II_MOB_MANAGER_H__

//Add after:
#ifdef __INGAME_WIKI__
	#include "../../common/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside CMobManager class:
		void RebindMobProto(LPCHARACTER ch);

//Add after:
#ifdef __INGAME_WIKI__
		typedef std::vector<CommonWikiData::TWikiMobDropInfo> TMobWikiInfoVector;
		typedef std::map<DWORD, TMobWikiInfoVector> TMobWikiInfoMap;
		
		TMobWikiInfoMap&	GetMobWikiInfoMap() { return m_wikiInfoMap; }
		TMobWikiInfoVector&	GetMobWikiInfo(DWORD vnum) { return m_wikiInfoMap[vnum]; }
#endif

//-----------------------------------//

//Search -> Inside CMobManager class:
		std::map<DWORD, CMob *> m_map_pkMobByVnum;
		std::map<std::string, CMob *> m_map_pkMobByName;
		std::map<DWORD, CMobGroup *> m_map_pkMobGroup;
		std::map<DWORD, CMobGroupGroup *> m_map_pkMobGroupGroup;

//Add after:
#ifdef __INGAME_WIKI__
		TMobWikiInfoMap	m_wikiInfoMap;
#endif
