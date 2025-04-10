/* File: Userinterface/PythonNetworkStream.h */

//Search -> Inside CPythonNetworkStream class:
		bool SendItemPickUpPacket(DWORD vid);

//Add after:
#ifdef INGAME_WIKI
		bool SendWikiRequestInfo(unsigned long long retID, DWORD vnum, bool isMob);
		void ToggleWikiWindow();
#endif

//-----------------------------------//

//Search -> Inside CPythonNetworkStream class:
		bool RecvDragonSoulRefine();

//Add after:
#ifdef INGAME_WIKI
		bool RecvWikiPacket();
#endif
