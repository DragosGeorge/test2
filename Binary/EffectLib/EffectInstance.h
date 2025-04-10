/* File: EffectLib/EffectInstance.h */

//Search -> Inside CEffectInstance class:
		static int ms_iRenderingEffectCount;

//Add after:
#ifdef INGAME_WIKI
	public:
		void SetWikiIgnoreFrustum(bool flag)
		{
			m_wikiIgnoreFrustum = flag;
			
			FWikiEffectFrustum f2(m_wikiIgnoreFrustum);
			std::for_each(m_ParticleInstanceVector.begin(), m_ParticleInstanceVector.end(), f2);
			std::for_each(m_MeshInstanceVector.begin(), m_MeshInstanceVector.end(), f2);
			std::for_each(m_LightInstanceVector.begin(), m_LightInstanceVector.end(), f2);
		}
	
	protected:
		struct FWikiEffectFrustum
		{
			FWikiEffectFrustum(bool igno): wikiIgnoreFrustum(igno) {}
			
			void operator () (CEffectElementBaseInstance * pInstance)
			{
				pInstance->SetWikiIgnoreFrustum(wikiIgnoreFrustum);
			}
			
			bool wikiIgnoreFrustum;
		};
		
		bool m_wikiIgnoreFrustum;
#endif
