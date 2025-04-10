/* File: EterPythonLib/PythonWindowManager.cpp */

//Search:
	CWindow * CWindowManager::RegisterBar(PyObject * po, const char * c_szLayer)

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	CWindow * CWindowManager::RegisterWikiRenderTarget(PyObject * po, const char * c_szLayer)
	{
		assert(m_LayerWindowMap.end() != m_LayerWindowMap.find(c_szLayer));

		CWindow * pWin = new CUiWikiRenderTarget(po);
		m_LayerWindowMap[c_szLayer]->AddChild(pWin);

#ifdef __WINDOW_LEAK_CHECK__
		gs_kSet_pkWnd.insert(pWin);
#endif
		return pWin;
	}
#endif
