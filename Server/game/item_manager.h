/* File: game/item_manager.h */

//Search:
#ifdef M2_USE_POOL
#include "pool.h"
#endif

//Add after:
#ifdef __INGAME_WIKI__
	#include <memory>
	#include "../../common/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside ITEM_MANAGER class:
		void			GracefulShutdown();

//Add after:
#ifdef __INGAME_WIKI__
		DWORD											GetWikiItemStartRefineVnum(DWORD dwVnum);
		std::string											GetWikiItemBaseRefineName(DWORD dwVnum);
		int												GetWikiMaxRefineLevel(DWORD dwVnum);
		
		CommonWikiData::TWikiInfoTable*						GetItemWikiInfo(DWORD vnum);
		std::vector<CommonWikiData::TWikiRefineInfo>		GetWikiRefineInfo(DWORD vnum);
		std::vector<CSpecialItemGroup::CSpecialItemInfo>	GetWikiChestInfo(DWORD vnum);
		std::vector<CommonWikiData::TWikiItemOriginInfo>&	GetItemOrigin(DWORD vnum) { return m_itemOriginMap[vnum]; }
#endif

//-----------------------------------//

//Search -> Inside ITEM_MANAGER class:
	protected:
		typedef std::map<DWORD, LPITEM> ITEM_VID_MAP;

		std::vector<TItemTable>		m_vec_prototype;
		std::vector<TItemTable*> m_vec_item_vnum_range_info;
		std::map<DWORD, DWORD>		m_map_ItemRefineFrom;
		int				m_iTopOfTable;

//Add after:
#ifdef __INGAME_WIKI__
		std::map<DWORD, std::unique_ptr<CommonWikiData::TWikiInfoTable>> m_wikiInfoMap;
		std::map<DWORD, std::vector<CommonWikiData::TWikiItemOriginInfo>> m_itemOriginMap;
#endif
