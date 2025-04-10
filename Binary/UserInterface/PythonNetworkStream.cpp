/* File: Userinterface/PythonNetworkStream.cpp */

//Search:
#include "ProcessCRC.h"

//Add after:
#ifdef INGAME_WIKI
	#include "../GameLib/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside CMainPacketHeaderMap constructor:
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));


//Add after:
#ifdef INGAME_WIKI
			Set(InGameWiki::HEADER_GC_WIKI,	CNetworkPacketHeaderMap::TPacketType(sizeof(InGameWiki::TGCWikiPacket), DYNAMIC_SIZE_PACKET));
#endif

//-----------------------------------//

//Search -> Inside CheckPacket function:
		if (!Peek(DynamicSizePacketHeader.size))

//Add !!BEFORE!!:
	///!\/!\/!\Advise/!\/!\/!\
	//only put this line if you have any problems in dynamic wiki communication (G-C)
#ifdef INGAME_WIKI
		DynamicSizePacketHeader.size = PacketType.iPacketSize;
#endif

//-----------------------------------//

//Search:
CPythonNetworkStream::CPythonNetworkStream()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
void CPythonNetworkStream::ToggleWikiWindow()
{
	if (m_apoPhaseWnd[PHASE_WINDOW_GAME])
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ToggleWikiWindow", Py_BuildValue("()"));
}
#endif
