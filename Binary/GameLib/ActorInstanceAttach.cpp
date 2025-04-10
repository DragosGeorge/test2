/* File: GameLib/ActorInstanceAttach.cpp */

//Search:
void CActorInstance::__ClearAttachingEffect()
{
	m_bEffectInitialized = false;

	std::list<TAttachingEffect>::iterator it;
	for(it = m_AttachingEffectList.begin(); it!= m_AttachingEffectList.end();++it)
	{
		CEffectManager::Instance().DestroyEffectInstance(it->dwEffectIndex);
	}
	m_AttachingEffectList.clear();
}

//Add after:
#ifdef INGAME_WIKI
void CActorInstance::WikiRenderAllAttachingModuleEffect()
{
	for (const auto& it : m_AttachingEffectList)
		CEffectManager::Instance().WikiModuleRenderOneEffect(it.dwEffectIndex);
}
#endif
