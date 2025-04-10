/* File: Userinterface/PythonApplication.h */

//Search:
#include "MovieMan.h"

//Add after:
#ifdef INGAME_WIKI
	#include "PythonWikiRenderTarget.h"
#endif

//-----------------------------------//

//Search:
		CPythonSystem				m_pySystem;

//Add after:
#ifdef INGAME_WIKI
		CGraphicWikiRenderTargetTexture		m_pyWikiRenderTargetTexture;
		CWikiRenderTargetManager			m_pyWikiModelViewManager;
		CPythonWikiRenderTarget				m_pyWikiRenderTarget;
#endif
