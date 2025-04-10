/* File: Userinterface/PythonNonPlayerModule.cpp */

//Search:
void initNonPlayer()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
PyObject* nonplayerGetMonsterDataByNamePart(PyObject* poSelf, PyObject* poArgs)
{
	char* szNamePart;
	if (!PyTuple_GetString(poArgs, 0, &szNamePart))
		return Py_BadArgument();
	
	std::tuple<const char*, int> mobData = CPythonNonPlayer::Instance().GetMonsterDataByNamePart(szNamePart);
	return Py_BuildValue("(si)", std::get<0>(mobData), std::get<1>(mobData));
}

PyObject* nonplayerBuildWikiSearchList(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::Instance().BuildWikiSearchList();
	return Py_BuildNone();
}

/*
	Some systems need these functions, and you can probably already have them, if
		you already have ignore the lines below
*/

PyObject* nonplayerGetMonsterImmuneFlag(PyObject* poSelf, PyObject* poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("i", pkTab->dwImmuneFlag);
}

PyObject * nonplayerGetMonsterLevel(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("i", pkTab->bLevel);
}

PyObject * nonplayerGetMonsterRaceFlag(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("i", pkTab->dwRaceFlag);
}

PyObject * nonplayerIsMonsterStone(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("i", pkTab->bType == CPythonNonPlayer::STONE);
}

PyObject * nonplayerGetMonsterDamage(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();
	
	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);
	
	return Py_BuildValue("ii", pkTab->dwDamageRange[0], pkTab->dwDamageRange[1]);
}

PyObject * nonplayerGetMonsterMaxHP(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();
	
	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);
	
	return Py_BuildValue("i", pkTab->dwMaxHP);
}

PyObject * nonplayerGetMonsterExp(PyObject * poSelf, PyObject * poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();
	
	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);
	
	return Py_BuildValue("i", pkTab->dwExp);
}

PyObject* nonplayerGetMonsterResistValue(PyObject* poSelf, PyObject* poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	if (iType < 0 || iType > CPythonNonPlayer::MOB_RESISTS_MAX_NUM)
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("i", pkTab->cResists[iType]);
}

PyObject* nonplayerGetMonsterGold(PyObject* poSelf, PyObject* poArgs)
{
	int iVNum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVNum))
		return Py_BuildException();

	CPythonNonPlayer& rkNonPlayer = CPythonNonPlayer::Instance();
	const CPythonNonPlayer::TMobTable* pkTab = rkNonPlayer.GetTable(iVNum);

	return Py_BuildValue("ii", pkTab->dwGoldMin, pkTab->dwGoldMax);
}
/*
	-----------------------------------------------------------------------------------------
*/
#endif

//-----------------------------------//

//Search -> Inside initNonPlayer routine:
		{ NULL,							NULL,								NULL		 },

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
		{ "GetMonsterDataByNamePart",	nonplayerGetMonsterDataByNamePart,	METH_VARARGS },
		{ "BuildWikiSearchList",		nonplayerBuildWikiSearchList,		METH_VARARGS },
		
		/*
			Some systems need these functions, and you can probably already have them, if
				you already have ignore the lines below
		*/
		{ "GetMonsterLevel",			nonplayerGetMonsterLevel,			METH_VARARGS },
		{ "GetMonsterRaceFlag",			nonplayerGetMonsterRaceFlag,		METH_VARARGS },
		{ "IsMonsterStone",				nonplayerIsMonsterStone,			METH_VARARGS },
		{ "GetMonsterDamage",			nonplayerGetMonsterDamage,			METH_VARARGS },
		{ "GetMonsterMaxHP",			nonplayerGetMonsterMaxHP,			METH_VARARGS },
		{ "GetMonsterExp",				nonplayerGetMonsterExp,				METH_VARARGS },
		
		{ "GetMonsterImmuneFlag",		nonplayerGetMonsterImmuneFlag,		METH_VARARGS },
		{ "GetMonsterResistValue",		nonplayerGetMonsterResistValue,		METH_VARARGS },
		{ "GetMonsterGold",				nonplayerGetMonsterGold,			METH_VARARGS },
		/*
			-----------------------------------------------------------------------------------------
		*/
#endif

//-----------------------------------//

//Search -> Inside initNonPlayer routine:
	PyObject * poModule = Py_InitModule("nonplayer", s_methods);

//Add after:
/*
	Some systems need these modules constants, and you can probably already have them, if
		you already have ignore the lines below
*/
#ifdef INGAME_WIKI
	PyModule_AddIntConstant(poModule, "IMMUNE_STUN",				CItemData::IMMUNE_STUN);
	PyModule_AddIntConstant(poModule, "IMMUNE_SLOW",				CItemData::IMMUNE_SLOW);
	PyModule_AddIntConstant(poModule, "IMMUNE_CURSE",				CItemData::IMMUNE_CURSE);
	PyModule_AddIntConstant(poModule, "IMMUNE_POISON",				CItemData::IMMUNE_POISON);
	PyModule_AddIntConstant(poModule, "IMMUNE_TERROR",				CItemData::IMMUNE_TERROR);
	PyModule_AddIntConstant(poModule, "IMMUNE_FLAG_MAX_NUM",		CItemData::IMMUNE_FLAG_MAX_NUM);
	
	PyModule_AddIntConstant(poModule, "MOB_RESIST_SWORD",			CPythonNonPlayer::MOB_RESIST_SWORD);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_TWOHAND",			CPythonNonPlayer::MOB_RESIST_TWOHAND);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_DAGGER",			CPythonNonPlayer::MOB_RESIST_DAGGER);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_BELL",			CPythonNonPlayer::MOB_RESIST_BELL);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_FAN",				CPythonNonPlayer::MOB_RESIST_FAN);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_BOW",				CPythonNonPlayer::MOB_RESIST_BOW);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_FIRE",			CPythonNonPlayer::MOB_RESIST_FIRE);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_ELECT",			CPythonNonPlayer::MOB_RESIST_ELECT);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_MAGIC",			CPythonNonPlayer::MOB_RESIST_MAGIC);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_WIND",			CPythonNonPlayer::MOB_RESIST_WIND);
	PyModule_AddIntConstant(poModule, "MOB_RESIST_POISON",			CPythonNonPlayer::MOB_RESIST_POISON);
	PyModule_AddIntConstant(poModule, "MOB_RESISTS_MAX_NUM",		CPythonNonPlayer::MOB_RESISTS_MAX_NUM);

	PyModule_AddIntConstant(poModule, "RACE_FLAG_ANIMAL",			CPythonNonPlayer::RACE_FLAG_ANIMAL);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_UNDEAD",			CPythonNonPlayer::RACE_FLAG_UNDEAD);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_DEVIL",			CPythonNonPlayer::RACE_FLAG_DEVIL);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_HUMAN",			CPythonNonPlayer::RACE_FLAG_HUMAN);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ORC",				CPythonNonPlayer::RACE_FLAG_ORC);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_MILGYO",			CPythonNonPlayer::RACE_FLAG_MILGYO);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_INSECT",			CPythonNonPlayer::RACE_FLAG_INSECT);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_FIRE",				CPythonNonPlayer::RACE_FLAG_FIRE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ICE",				CPythonNonPlayer::RACE_FLAG_ICE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_DESERT",			CPythonNonPlayer::RACE_FLAG_DESERT);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_TREE",				CPythonNonPlayer::RACE_FLAG_TREE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_ELEC",			CPythonNonPlayer::RACE_FLAG_ATT_ELEC);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_FIRE",			CPythonNonPlayer::RACE_FLAG_ATT_FIRE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_ICE",			CPythonNonPlayer::RACE_FLAG_ATT_ICE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_WIND",			CPythonNonPlayer::RACE_FLAG_ATT_WIND);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_EARTH",		CPythonNonPlayer::RACE_FLAG_ATT_EARTH);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_DARK",			CPythonNonPlayer::RACE_FLAG_ATT_DARK);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_MAX_NUM",			CPythonNonPlayer::RACE_FLAG_MAX_NUM);
#endif
/*
	-----------------------------------------------------------------------------------------
*/