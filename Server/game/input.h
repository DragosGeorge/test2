/* File: game/input.h */

//Search -> Inside CInputMain class:
		int			Guild(LPCHARACTER ch, const char * data, size_t uiBytes);

//Add !!BEFORE!!:
#ifdef __INGAME_WIKI__
		void		RecvWikiPacket(LPCHARACTER ch, const char * c_pData);
#endif
