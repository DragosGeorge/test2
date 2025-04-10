/* File: Userinterface/PythonApplication.cpp */

//Search -> Inside RenderGame routine:
		m_kChrMgr.Deform();
		m_kEftMgr.Update();

//Add after:
#ifdef INGAME_WIKI
		if (CPythonWikiRenderTarget::instance().CanRenderWikiModules())
			m_pyWikiModelViewManager.DeformModels();
#endif

//-----------------------------------//

//Search -> Inside RenderGame routine:
		m_pyBackground.SetCharacterDirLight();
		m_kChrMgr.Render();

//Add after:
#ifdef INGAME_WIKI
		if (CPythonWikiRenderTarget::instance().CanRenderWikiModules())
			m_pyWikiModelViewManager.RenderModels();
#endif

//-----------------------------------//

//Search -> Inside UpdateGame routine:
	DWORD t3=ELTimer_GetMSec();
	TPixelPosition kPPosMainActor;
	m_pyPlayer.NEW_GetMainActorPosition(&kPPosMainActor);

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	if (CPythonWikiRenderTarget::instance().CanRenderWikiModules())
		m_pyWikiModelViewManager.UpdateModels();
#endif

//-----------------------------------//

//Search -> Inside Process function:
			if (m_pyGraphic.IsLostDevice())
			{
				CPythonBackground& rkBG = CPythonBackground::Instance();
				rkBG.ReleaseCharacterShadowTexture();

//Add after:
#ifdef INGAME_WIKI
				if (CPythonWikiRenderTarget::instance().CanRenderWikiModules())
					CWikiRenderTargetManager::Instance().ReleaseRenderTargetTextures();
#endif

//-----------------------------------//

//Search -> Inside Process function:
				if (m_pyGraphic.RestoreDevice())
				{

//Add after:
#ifdef INGAME_WIKI
					if (CPythonWikiRenderTarget::instance().CanRenderWikiModules())
						CWikiRenderTargetManager::Instance().CreateRenderTargetTextures();
#endif

//-----------------------------------//

//Search -> Inside Destroy routine:
	CPythonSystem::Instance().SaveConfig();

//Add after:
#ifdef INGAME_WIKI
	m_pyWikiModelViewManager.InitializeData();
#endif
