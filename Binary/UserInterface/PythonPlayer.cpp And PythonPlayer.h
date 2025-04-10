/* File: Userinterface/PythonPlayer.cpp And PythonPlayer.h */

/*In this file you gonna have one enumeration with races num, like the follow
	example:
	
	enum
	{
		MAIN_RACE_WARRIOR_M,
		MAIN_RACE_ASSASSIN_W,
		MAIN_RACE_SURA_M,
		MAIN_RACE_SHAMAN_W,
		MAIN_RACE_WARRIOR_W,
		MAIN_RACE_ASSASSIN_M,
		MAIN_RACE_SURA_W,
		MAIN_RACE_SHAMAN_M,
#ifdef ENABLE_WOLFMAN_CHARACTER
		MAIN_RACE_WOLFMAN_M,
#endif
		MAIN_RACE_MAX_NUM,
	};
	
	You need put this enumeration in start of PythonPlayer.h file, like example:
	
	File: Userinterface/PythonPlayer.h
	
	#pragma once

	#include "AbstractPlayer.h"
	#include "Packet.h"
	#include "PythonSkill.h"

	enum
	{
		MAIN_RACE_WARRIOR_M,
		MAIN_RACE_ASSASSIN_W,
		MAIN_RACE_SURA_M,
		MAIN_RACE_SHAMAN_W,
		MAIN_RACE_WARRIOR_W,
		MAIN_RACE_ASSASSIN_M,
		MAIN_RACE_SURA_W,
		MAIN_RACE_SHAMAN_M,
	#ifdef ENABLE_WOLFMAN_CHARACTER
		MAIN_RACE_WOLFMAN_M,
	#endif
		MAIN_RACE_MAX_NUM,
	};

	class CInstanceBase;
*/
