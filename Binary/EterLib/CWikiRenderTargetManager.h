#pragma once

#include <unordered_map>
#include <cstdint>
#include <memory>

#include "../EterBase/Singleton.h"
#include "../GameLib/in_game_wiki.h"

#include "CWikiRenderTarget.h"

class CWikiRenderTargetManager : public CSingleton<CWikiRenderTargetManager>
{
	public:
		CWikiRenderTargetManager();
		virtual ~CWikiRenderTargetManager();
		void InitializeData() { m_renderTargets.clear(); }
	
	public:
		std::shared_ptr<CWikiRenderTarget>	GetRenderTarget(_wint32 module_id);
		bool								CreateRenderTarget(_wint32 module_id, _wint32 width, _wint32 height);
		void								DeleteRenderTarget(_wint32 module_id);
		
		void								CreateRenderTargetTextures();
		void								ReleaseRenderTargetTextures();
		
		void								DeformModels();
		void								UpdateModels();
		void								RenderModels();
	
	protected:
		std::unordered_map<_wint32, std::shared_ptr<CWikiRenderTarget>>	m_renderTargets;
};
