/* File: EterPythonLib/PythonWindowManager.h */

//Search:
			CWindow *	RegisterBox(PyObject * po, const char * c_szLayer);

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
			CWindow *	RegisterWikiRenderTarget(PyObject * po, const char * c_szLayer);
#endif
