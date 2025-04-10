/* File: EterPythonLib/PythonWindowManagerModule.cpp */

//Search -> Inside wndMgrIsIn python object:
	return Py_BuildValue("i", pWin == UI::CWindowManager::Instance().GetPointWindow());

//Replace with:
#ifdef INGAME_WIKI
	bool bCheckChilds;
	if (!PyTuple_GetBoolean(poArgs, 1, &bCheckChilds))
		bCheckChilds = false;

	UI::CWindow* pWinPoint = UI::CWindowManager::Instance().GetPointWindow();
	if (pWin == pWinPoint)
		return Py_BuildValue("b", true);

	if (bCheckChilds && pWinPoint)
	{
		if (pWin->IsChild(pWinPoint, true))
			return Py_BuildValue("b", true);
	}

	return Py_BuildValue("b", false);
#else
	return Py_BuildValue("i", pWin == UI::CWindowManager::Instance().GetPointWindow());
#endif

//-----------------------------------//

//Search:
PyObject * wndTextHideCursor(PyObject * poSelf, PyObject * poArgs)
{
	UI::CWindow * pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->HideCursor();
	return Py_BuildNone();
}

//Add after:
#ifdef INGAME_WIKI
PyObject* wndTextIsShowCursor(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	return Py_BuildValue("b", ((UI::CTextLine*)pWindow)->IsShowCursor());
}
#endif

//-----------------------------------//

//Search:
void initwndMgr()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
PyObject * wndMgrRegisterWikiRenderTarget(PyObject * poSelf, PyObject * poArgs)
{
	PyObject * po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char * szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow * pWindow = UI::CWindowManager::Instance().RegisterWikiRenderTarget(po, szLayer);
	return Py_BuildValue("i", pWindow);
}

PyObject* wndMgrSetInsideRender(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	bool val;
	if (!PyTuple_GetBoolean(poArgs, 1, &val))
		return Py_BuildException();
	
	pWin->SetInsideRender(val);
	return Py_BuildNone();
}

PyObject* wndSetRenderingRect(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	float fLeft;
	if (!PyTuple_GetFloat(poArgs, 1, &fLeft))
		return Py_BuildException();
	float fTop;
	if (!PyTuple_GetFloat(poArgs, 2, &fTop))
		return Py_BuildException();
	float fRight;
	if (!PyTuple_GetFloat(poArgs, 3, &fRight))
		return Py_BuildException();
	float fBottom;
	if (!PyTuple_GetFloat(poArgs, 4, &fBottom))
		return Py_BuildException();
	
	pWindow->SetRenderingRect(fLeft, fTop, fRight, fBottom);
	return Py_BuildNone();
}

PyObject* wndMgrGetRenderBox(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	RECT val;
	pWin->GetRenderBox(&val);
	return Py_BuildValue("iiii", val.left, val.top, val.right, val.bottom);
}

PyObject* wndMgrSetWikiRenderTarget(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	
	int renderWindow = -1;
	if (!PyTuple_GetInteger(poArgs, 1, &renderWindow))
		return Py_BuildException();
	
	((UI::CUiWikiRenderTarget*)pWin)->SetWikiRenderTargetModule(renderWindow);
	return Py_BuildNone();
}

PyObject* wndTextSetFixedRenderPos(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int startPos, endPos;
	if (!PyTuple_GetInteger(poArgs, 1, &startPos))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 2, &endPos))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetFixedRenderPos(startPos, endPos);
	return Py_BuildNone();
}

PyObject* wndTextGetRenderPos(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	WORD startPos, endPos;

	((UI::CTextLine*)pWindow)->GetRenderPositions(startPos, endPos);
	return Py_BuildValue("ii", startPos, endPos);
}

PyObject* wndImageUnloadImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow * pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CImageBox*)pWindow)->UnloadImage();
	return Py_BuildNone();
}
#endif

//-----------------------------------//

//Search -> Inside initwndMgr routine:
		{ NULL,							NULL,								NULL },

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
		{ "RegisterWikiRenderTarget",	wndMgrRegisterWikiRenderTarget,		METH_VARARGS },
		{ "SetInsideRender",			wndMgrSetInsideRender,				METH_VARARGS },
		{ "SetRenderingRect",			wndSetRenderingRect,				METH_VARARGS },
		{ "GetRenderBox",				wndMgrGetRenderBox,					METH_VARARGS },
		{ "SetWikiRenderTarget",		wndMgrSetWikiRenderTarget,			METH_VARARGS },
		{ "SetFixedRenderPos",			wndTextSetFixedRenderPos,			METH_VARARGS },
		{ "GetRenderPos",				wndTextGetRenderPos,				METH_VARARGS },
		{ "UnloadImage",				wndImageUnloadImage,				METH_VARARGS },
		{ "IsShowCursor",				wndTextIsShowCursor,				METH_VARARGS },
#endif
