/* File: Userinterface/PythonNetworkStreamModule.cpp */

//Search:
void initnet()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
PyObject* netToggleWikiWindow(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream::Instance().ToggleWikiWindow();
	return Py_BuildNone();
}
#endif

//-----------------------------------//

//Search -> Inside initnet routine:
	static PyMethodDef s_methods[] =
	{

//Add after:
#ifdef INGAME_WIKI
		{ "ToggleWikiWindow",						netToggleWikiWindow,						METH_VARARGS },
#endif
