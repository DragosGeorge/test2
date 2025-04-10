/* File: GameLib/ItemData.cpp */

//Search -> Inside Clear routine:
	m_pLODModelThingVector.clear();

//Add after:
#ifdef INGAME_WIKI
	m_isValidImage = true;
	m_wikiInfo.isSet = false;
	m_wikiInfo.hasData = false;
	m_isBlacklisted = false;
#endif
