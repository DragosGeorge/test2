/* File: game/packet_info.cpp */

//Search:
#include "packet_info.h"

//Add after:
#ifdef __INGAME_WIKI__
	#include "../../common/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside CPacketInfoCG constructor:
	Set(HEADER_CG_GUILD, sizeof(TPacketCGGuild), "Guild", true);

//Add !!BEFORE!!:
#ifdef __INGAME_WIKI__
	Set(InGameWiki::HEADER_CG_WIKI, sizeof(InGameWiki::TCGWikiPacket), "RecvWikiPacket", true);
#endif
