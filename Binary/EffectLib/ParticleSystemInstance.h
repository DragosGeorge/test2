/* File: EffectLib/ParticleSystemInstance.h */

//Search -> Inside CParticleSystemInstance class:
					if (!InFrustum(*itor))

//Replace with:
#ifdef INGAME_WIKI
					if (!InFrustum(*itor) && !m_wikiIgnoreFrustum)
#else
					if (!InFrustum(*itor))
#endif
