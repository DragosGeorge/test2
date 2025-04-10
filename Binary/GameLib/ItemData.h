/* File: GameLib/ItemData.h */

//Search:
#include "../eterGrnLib/Thing.h"

//Add after:
#ifdef INGAME_WIKI
	#include "in_game_wiki.h"
#endif

//-----------------------------------//

//Search -> Inside CItemData class:
		enum EImmuneFlags

/*Add on the end of enumeration:
	
	/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\
	Pay attention on the number you put on variable
		need to be the right number of last left
		shift variable, example:

			IMMUNE_TERROR		= (1 << [!!!!!! 6 !!!!!!]),
			IMMUNE_FLAG_MAX_NUM = 7

	/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
			IMMUNE_FLAG_MAX_NUM = 7
#endif

//-----------------------------------//

//Search -> Inside CItemData class:
		DWORD GetIconNumber() const;

//Add after:
#ifdef INGAME_WIKI
		DWORD GetRefinedVnum() const { return m_ItemTable.dwRefinedVnum; }
#endif

//-----------------------------------//

//Search -> Inside CItemData class:
	public:
		UINT	GetSpecularPoweru() const;
		float	GetSpecularPowerf() const;

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	public:
		typedef struct SWikiItemInfo
		{
			~SWikiItemInfo() = default;
			SWikiItemInfo() {
				isSet = false;
				hasData = false;
				bIsCommon = false;
				
				dwOrigin = 0;
				maxRefineLevel = CommonWikiData::MAX_REFINE_COUNT;
				
				pRefineData.clear();
				pChestInfo.clear();
				pOriginInfo.clear();
			}
			
			bool isSet;
			bool hasData;
			bool bIsCommon;
			
			DWORD dwOrigin;
			int maxRefineLevel;
			
			std::vector<CommonWikiData::TWikiRefineInfo> pRefineData;
			std::vector<CommonWikiData::TWikiChestInfo> pChestInfo;
			std::vector<CommonWikiData::TWikiItemOriginInfo> pOriginInfo;
		} TWikiItemInfo;
		
		bool IsValidImage() { return m_isValidImage; }
		std::string GetIconFileName() { return m_strIconFileName; }
		TWikiItemInfo* GetWikiTable() { return &m_wikiInfo; }
		bool IsBlacklisted() { return m_isBlacklisted; }
		
		void ValidateImage(bool isValidImage) { m_isValidImage = isValidImage; }
		void SetBlacklisted(bool val) { m_isBlacklisted = val; }
	
	protected:
		bool m_isValidImage;
		bool m_isBlacklisted;
	
	private:
		TWikiItemInfo m_wikiInfo;
#endif
