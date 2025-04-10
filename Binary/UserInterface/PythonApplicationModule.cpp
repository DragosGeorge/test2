/* File: Userinterface/PythonApplicationModule.cpp */

//Search -> Inside initapp routine:
#ifdef ENABLE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM",	1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM",	0);
#endif

//Add after:
#ifdef INGAME_WIKI
	PyModule_AddIntConstant(poModule,		"INGAME_WIKI",		true);
#ifdef INGAME_WIKI_WOLFMAN
	PyModule_AddIntConstant(poModule,	"INGAME_WIKI_WOLFMAN",	true);
#else
	PyModule_AddIntConstant(poModule,	"INGAME_WIKI_WOLFMAN",	false);
#endif
#else
	PyModule_AddIntConstant(poModule,		"INGAME_WIKI",		false);
	PyModule_AddIntConstant(poModule,	"INGAME_WIKI_WOLFMAN",	false);
#endif

