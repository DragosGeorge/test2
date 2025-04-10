/* File: Userinterface/PythonPlayerModule.cpp */

//Search -> Inside initPlayer routine:
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_DO_REFINE",	DS_SUB_HEADER_DO_REFINE);

//Add after:
#ifdef INGAME_WIKI
	PyModule_AddIntConstant(poModule, "MAIN_RACE_WARRIOR_M",		MAIN_RACE_WARRIOR_M);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_ASSASSIN_W",		MAIN_RACE_ASSASSIN_W);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_SURA_M",			MAIN_RACE_SURA_M);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_SHAMAN_W",			MAIN_RACE_SHAMAN_W);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_WARRIOR_W",		MAIN_RACE_WARRIOR_W);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_ASSASSIN_M",		MAIN_RACE_ASSASSIN_M);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_SURA_W",			MAIN_RACE_SURA_W);
	PyModule_AddIntConstant(poModule, "MAIN_RACE_SHAMAN_M",			MAIN_RACE_SHAMAN_M);
#ifdef INGAME_WIKI_WOLFMAN
	PyModule_AddIntConstant(poModule, "MAIN_RACE_WOLFMAN_M",		MAIN_RACE_WOLFMAN_M);
#endif
	PyModule_AddIntConstant(poModule, "MAIN_RACE_MAX_NUM",			MAIN_RACE_MAX_NUM);
#endif
