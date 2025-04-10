/* File: EffectLib/EffectElementBaseInstance.cpp */

//Search -> Inside Initialize routine:
	m_fRemainingTime = 0.0f;

//Add after:
#ifdef INGAME_WIKI
	m_wikiIgnoreFrustum = 0.0f;
#endif
