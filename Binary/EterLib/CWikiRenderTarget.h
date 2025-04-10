#pragma once

#include <cstdint>
#include <memory>

#include "../GameLib/in_game_wiki.h"
#include "GrpWikiRenderTargetTexture.h"

class CInstanceBase;
class CGraphicImageInstance;

class CWikiRenderTarget
{
	using TCharacterInstanceMap = std::map<_wuint32, CInstanceBase*>;
	
	public:
		CWikiRenderTarget(_wuint32 width, _wuint32 height);
		virtual ~CWikiRenderTarget();
	
	public:
		void		SetVisibility(bool flag) { m_visible = flag; }
		
		void		CreateTextures() const;
		void		ReleaseTextures() const;
		void		RenderTexture() const;
		
		void		SetRenderingRect(RECT* rect) const;
		void		SetRenderingBox(RECT* renderBox) const;
		
		void		SelectModel(_wuint32 model_vnum);
		void		UpdateModel();
		void		DeformModel() const;
		void		RenderModel() const;
		
		void		SetWeapon(_wuint32 dwVnum);
		void		SetArmor(_wuint32 vnum);
		void		SetHair(_wuint32 vnum);
		void		SetModelV3Eye(_wfloat x, _wfloat y, _wfloat z);
		void		SetModelV3Target(_wfloat x, _wfloat y, _wfloat z);
	
	private:
		std::unique_ptr<CInstanceBase>						m_pModel;
		std::unique_ptr<CGraphicWikiRenderTargetTexture>	m_renderTargetTexture;
		float												m_modelRotation;
		bool												m_visible;
		D3DXVECTOR3											m_v3Eye;
		D3DXVECTOR3											m_v3Target;
		D3DXVECTOR3											m_v3Up;
};
