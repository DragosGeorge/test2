/* File: Userinterface/PythonItemModule.cpp */

//Search:
void initItem()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
PyObject* itemGetItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	CItemData* pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetIndex());
}

PyObject* itemGetItemRefinedVnum(PyObject* poSelf, PyObject* poArgs)
{
	CItemData* pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetRefinedVnum());
}

PyObject* itemGetItemDataByNamePart(PyObject* poSelf, PyObject* poArgs)
{
	char* nameStart;
	if (!PyTuple_GetString(poArgs, 0, &nameStart))
		return Py_BadArgument();
	
	std::tuple<const char*, int> itemData = CItemManager::Instance().SelectByNamePart(nameStart);
	return Py_BuildValue("(si)", std::get<0>(itemData), std::get<1>(itemData));
}
#endif

//-----------------------------------//

//Search -> Inside initItem routine:
	static PyMethodDef s_methods[] =
	{

//Add after:
#ifdef INGAME_WIKI
		{ "GetItemVnum",					itemGetItemVnum,						METH_VARARGS },
		{ "GetItemRefinedVnum",				itemGetItemRefinedVnum,					METH_VARARGS },
		{ "GetItemDataByNamePart",			itemGetItemDataByNamePart,				METH_VARARGS },
#endif
