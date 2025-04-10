/* File: Userinterface/PythonNonPlayer.h */

//Search:
#pragma once

//Add after:
#ifdef INGAME_WIKI
	#include "../GameLib/in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		enum EClickEvent

/*Add !!BEFORE!!:
	
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
	This mob Types needs to be the same as the server source:
		-> Go to common/length.h and search for: ECharType;
		-> Remove text "CHAR_TYPE_" for each variable inside the enumeration;
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
		enum EMobTypes
		{
			MONSTER,
			NPC,
			STONE,
			WARP,
			DOOR,
			BUILDING,
			PC,
			POLYMORPH_PC,
			HORSE,
			GOTO
		};
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		enum EMobMaxNum

/*Add !!BEFORE!!:
	
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
	This race flags needs to be the same as the server source:
		-> Go to common/length.h and search for: ERaceFlags;
		-> Add on the end on the enumeration "RACE_FLAG_MAX_NUM" like example;
		-> Probably you already have this from other's systems, if yes
			you can ignore this step;
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
	enum ERaceFlags
	{
		RACE_FLAG_ANIMAL	= (1 << 0),
		RACE_FLAG_UNDEAD	= (1 << 1),
		RACE_FLAG_DEVIL		= (1 << 2),
		RACE_FLAG_HUMAN		= (1 << 3),
		RACE_FLAG_ORC		= (1 << 4),
		RACE_FLAG_MILGYO	= (1 << 5),
		RACE_FLAG_INSECT	= (1 << 6),
		RACE_FLAG_FIRE		= (1 << 7),
		RACE_FLAG_ICE		= (1 << 8),
		RACE_FLAG_DESERT	= (1 << 9),
		RACE_FLAG_TREE		= (1 << 10),
		RACE_FLAG_ATT_ELEC	= (1 << 11),
		RACE_FLAG_ATT_FIRE	= (1 << 12),
		RACE_FLAG_ATT_ICE	= (1 << 13),
		RACE_FLAG_ATT_WIND	= (1 << 14),
		RACE_FLAG_ATT_EARTH	= (1 << 15),
		RACE_FLAG_ATT_DARK	= (1 << 16),
		
		RACE_FLAG_MAX_NUM	= 17,
	};
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		typedef struct SMobTable
		{

//Add after:
#ifdef INGAME_WIKI
			SMobTable() = default;
			~SMobTable() = default;
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		typedef std::map<DWORD, TMobTable*> TNonPlayerDataMap;

//Replace with:
#ifdef INGAME_WIKI
		typedef struct SWikiInfoTable
		{
			~SWikiInfoTable() = default;
			SWikiInfoTable() {
				isSet = false;
				isFiltered = false;
				
				dropList.clear();
				mobTable = nullptr;
			}
			
			bool isSet;
			bool isFiltered;
			
			std::vector<CommonWikiData::TWikiMobDropInfo> dropList;
			std::unique_ptr<TMobTable> mobTable;
		} TWikiInfoTable;
		
		typedef std::list<TMobTable*> TMobTableList;
		typedef std::map<DWORD, TWikiInfoTable> TNonPlayerDataMap;
#else
		typedef std::map<DWORD, TMobTable*> TNonPlayerDataMap;
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		const TMobTable *	GetTable(DWORD dwVnum);

//Add after:
#ifdef INGAME_WIKI
		TWikiInfoTable*						GetWikiTable(DWORD dwVnum);
		bool								CanRenderMonsterModel(DWORD dwMonsterVnum);
		size_t								WikiLoadClassMobs(BYTE bType, unsigned short fromLvl, unsigned short toLvl);
		void								WikiSetBlacklisted(DWORD vnum);
		void								BuildWikiSearchList();
		std::tuple<const char*, int>	GetMonsterDataByNamePart(const char* namePart);
		std::vector<DWORD>*				WikiGetLastMobs() { return &m_vecTempMob; }
#endif

//-----------------------------------//

//Search -> Inside CPythonNonPlayer class:
		TNonPlayerDataMap	m_NonPlayerDataMap;

//Add after:
#ifdef INGAME_WIKI
		void								SortMobDataName();
		
		std::vector<DWORD>				m_vecTempMob;
		std::vector<TMobTable*>				m_vecWikiNameSort;
#endif
