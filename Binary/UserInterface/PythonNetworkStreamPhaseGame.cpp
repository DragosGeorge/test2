/* File: Userinterface/PythonNetworkStreamPhaseGame.cpp */

//Search:
#include "ProcessCRC.h"

//Add after:
#ifdef INGAME_WIKI
	#include "../GameLib/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside GamePhase routine:
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;

//Add after:
#ifdef INGAME_WIKI
			case InGameWiki::HEADER_GC_WIKI:
				ret = RecvWikiPacket();
				break;
#endif

//-----------------------------------//

//Add on the end of file:
#ifdef INGAME_WIKI
extern PyObject* wikiModule;

bool CPythonNetworkStream::SendWikiRequestInfo(unsigned long long retID, DWORD vnum, bool isMob)
{
	InGameWiki::TCGWikiPacket pack;
	pack.vnum = vnum;
	pack.is_mob = isMob;
	pack.ret_id = retID;
	
	if (!Send(sizeof(InGameWiki::TCGWikiPacket), &pack))
		return false;
	
	return true;
}

bool CPythonNetworkStream::RecvWikiPacket()
{
	InGameWiki::TGCWikiPacket pack;
	if (!Recv(sizeof(InGameWiki::TGCWikiPacket), &pack))
		return false;
	
	WORD iPacketSize = pack.size - sizeof(InGameWiki::TGCWikiPacket);
	if (iPacketSize <= 0)
		return false;
	
	unsigned long long ret_id = 0;
	DWORD data_vnum = 0;
	
	if (pack.is_data_type(InGameWiki::LOAD_WIKI_ITEM))
	{
		const size_t recv_size = sizeof(InGameWiki::TGCItemWikiPacket);
		iPacketSize -= WORD(recv_size);
		
		InGameWiki::TGCItemWikiPacket item_data;
		if (!Recv(recv_size, &item_data))
			return false;
		
		ret_id = item_data.ret_id;
		data_vnum = item_data.vnum;
		
		CItemData* pData = nullptr;
		if (!CItemManager::instance().GetItemDataPointer(item_data.vnum, &pData)) {
			TraceError("Cant get pointer from item -> %d", item_data.vnum);
			return false;
		}
		
		auto& recv_wiki = item_data.wiki_info;
		auto wikiInfo = pData->GetWikiTable();
		
		const int origin_size = item_data.origin_infos_count;
		const int chest_info_count = recv_wiki.chest_info_count;
		const int refine_infos_count = recv_wiki.refine_infos_count;
		
		wikiInfo->isSet = true;
		wikiInfo->hasData = true;
		wikiInfo->bIsCommon = recv_wiki.is_common;
		wikiInfo->dwOrigin = recv_wiki.origin_vnum;
		wikiInfo->maxRefineLevel = refine_infos_count;
		
		{
			wikiInfo->pOriginInfo.clear();
			const size_t origin_info_recv_base_size = sizeof(CommonWikiData::TWikiItemOriginInfo);
			
			for (int idx = 0; idx < origin_size; ++idx) {
				CommonWikiData::TWikiItemOriginInfo origin_data;
				if (!Recv(origin_info_recv_base_size, &origin_data))
					return false;
				
				wikiInfo->pOriginInfo.emplace_back(origin_data);
				iPacketSize -= WORD(origin_info_recv_base_size);
			}
			
			
			wikiInfo->pChestInfo.clear();
			const size_t chest_info_recv_base_size = sizeof(CommonWikiData::TWikiChestInfo);
			
			for (int idx = 0; idx < chest_info_count; ++idx) {
				CommonWikiData::TWikiChestInfo chest_data;
				if (!Recv(chest_info_recv_base_size, &chest_data))
					return false;
				
				wikiInfo->pChestInfo.emplace_back(chest_data);
				iPacketSize -= WORD(chest_info_recv_base_size);
			}
			
			wikiInfo->pRefineData.clear();
			const size_t refine_info_recv_base_size = sizeof(CommonWikiData::TWikiRefineInfo);
			
			for (int idx = 0; idx < refine_infos_count; ++idx) {
				CommonWikiData::TWikiRefineInfo refine_info_data;
				if (!Recv(refine_info_recv_base_size, &refine_info_data))
					return false;
				
				wikiInfo->pRefineData.emplace_back(refine_info_data);
				iPacketSize -= WORD(refine_info_recv_base_size);
			}
		}
		
		if (iPacketSize != 0)
			return false;
	}
	else
	{
		const size_t recv_size = sizeof(InGameWiki::TGCMobWikiPacket);
		iPacketSize -= WORD(recv_size);
		
		InGameWiki::TGCMobWikiPacket mob_data;
		if (!Recv(recv_size, &mob_data))
			return false;
		
		ret_id = mob_data.ret_id;
		data_vnum = mob_data.vnum;
		const int drop_info_count = mob_data.drop_info_count;
		
		CPythonNonPlayer::TWikiInfoTable* mobData = nullptr;
		if (!(mobData = CPythonNonPlayer::instance().GetWikiTable(mob_data.vnum))) {
			TraceError("Cant get mob data from monster -> %d", mob_data.vnum);
			return false;
		}
		
		mobData->isSet = (drop_info_count > 0);
		
		{
			mobData->dropList.clear();
			const size_t mob_drop_info_recv_base_size = sizeof(CommonWikiData::TWikiMobDropInfo);
			
			for (int idx = 0; idx < drop_info_count; ++idx) {
				CommonWikiData::TWikiMobDropInfo drop_data;
				if (!Recv(mob_drop_info_recv_base_size, &drop_data))
					return false;
				
				mobData->dropList.push_back(drop_data);
				iPacketSize -= WORD(mob_drop_info_recv_base_size);
			}
		}
		
		if (iPacketSize != 0)
			return false;
	}
	
	if (wikiModule)
		PyCallClassMemberFunc(wikiModule, "BINARY_LoadInfo", Py_BuildValue("(Li)", (long long)ret_id, data_vnum));
	
	return true;
}
#endif

