/* File: EffectLib/EffectInstance.cpp */

//Search -> Inside __Initialize routine:
	m_dwFrame = 0;

//Add after:
#ifdef INGAME_WIKI
	m_wikiIgnoreFrustum = false;
#endif