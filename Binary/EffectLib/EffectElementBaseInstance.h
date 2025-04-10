/* File: EffectLib/EffectElementBaseInstance.h */

//Search -> Inside CEffectElementBaseInstance class:
		void SetDeactive();

//Add after:
#ifdef INGAME_WIKI
	public:
		void SetWikiIgnoreFrustum(bool flag) { m_wikiIgnoreFrustum = flag; }
	
	protected:
		bool m_wikiIgnoreFrustum;
#endif