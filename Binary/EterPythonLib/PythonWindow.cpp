/* File: EterPythonLib/PythonWindow.cpp */

//Search:
#include "PythonWindowManager.h"

//Add after:
#ifdef INGAME_WIKI
	#include "../eterLib/CWikiRenderTargetManager.h"
#endif

//-----------------------------------//

//Search -> Inside CWindow constructor (namespace UI):
		m_isUpdatingChildren(FALSE)

//Add after:
#ifdef INGAME_WIKI
		, m_isInsideRender(false)
#endif

//-----------------------------------//

//Search -> Inside CWindow constructor (namespace UI):
		m_limitBiasRect.bottom = m_limitBiasRect.left = m_limitBiasRect.right = m_limitBiasRect.top = 0;

//Add after:
#ifdef INGAME_WIKI
		memset(&m_renderBox, 0, sizeof(m_renderBox));
#endif

//-----------------------------------//

//Search:
	void CWindow::Hide()
	{
		m_bShow = false;
	}

//Add after:
#ifdef INGAME_WIKI
	void CWindow::OnHideWithChilds()
	{
		OnHide();
		std::for_each(m_pChildList.begin(), m_pChildList.end(), std::mem_fn(&CWindow::OnHideWithChilds));
	}

	void CWindow::OnHide()
	{
		PyCallClassMemberFunc(m_poHandler, "OnHide", BuildEmptyTuple());
	}
#endif

//-----------------------------------//

//Search:
	void CWindow::Render()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	bool CWindow::IsShow()
	{
		if (!m_bShow)
			return false;

		if (m_isInsideRender)
			if (m_renderBox.left + m_renderBox.right >= m_lWidth || m_renderBox.top + m_renderBox.bottom >= m_lHeight)
				return false;

		return true;
	}
#endif

//-----------------------------------//

//Search -> Inside CWindow::Render routine:
		std::for_each(m_pChildList.begin(), m_pChildList.end(), std::mem_fn(&CWindow::Render));

//Add after:
#ifdef INGAME_WIKI
		OnAfterRender();
#endif

//-----------------------------------//

//Search:
	void CWindow::OnRender()
	{
		if (!m_poHandler)
			return;

		if (!IsShow())
			return;

		PyCallClassMemberFunc(m_poHandler, "OnRender", BuildEmptyTuple());
	}

//Add after:
#ifdef INGAME_WIKI
	void CWindow::OnAfterRender()
	{
		if (!m_poHandler)
			return;

		if (!IsShow())
			return;

		PyCallClassMemberFunc(m_poHandler, "OnAfterRender", BuildEmptyTuple());
	}
#endif

//-----------------------------------//

//Search -> Inside CWindow::SetSize routine:
		m_rect.right = m_rect.left + m_lWidth;
		m_rect.bottom = m_rect.top + m_lHeight;

//Add after:
#ifdef INGAME_WIKI
		if (m_isInsideRender)
			UpdateRenderBoxRecursive();
#endif

//-----------------------------------//

//Search -> Inside CWindow::SetPosition routine:
		UpdateRect();

//Add after:
#ifdef INGAME_WIKI
		if (m_isInsideRender)
			UpdateRenderBoxRecursive();
#endif

//-----------------------------------//

//Search:
	void CWindow::GetPosition(long * plx, long * ply)

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	void CWindow::UpdateRenderBoxRecursive()
	{
		UpdateRenderBox();
		for (auto it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
			(*it)->UpdateRenderBoxRecursive();
	}
#endif

//-----------------------------------//

//Search -> Inside CWindow::AddChild routine:
		m_pChildList.push_back(pWin);
		pWin->m_pParent = this;

//Add after:
#ifdef INGAME_WIKI
		if (m_isInsideRender && !pWin->m_isInsideRender)
			pWin->SetInsideRender(m_isInsideRender);
#endif

//-----------------------------------//

//Search:
	CWindow * CWindow::GetRoot()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	void CWindow::SetInsideRender(BOOL flag)
	{
		if (!m_pParent || m_isInsideRender && m_pParent->m_isInsideRender)
			return;

		if (m_isInsideRender && flag)
			return;

		m_isInsideRender = flag;
		UpdateRenderBox();
		for (auto it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
			(*it)->SetInsideRender(m_isInsideRender);
	}

	void CWindow::GetRenderBox(RECT* box)
	{
		memcpy(box, &m_renderBox, sizeof(RECT));
	}
	
	void CWindow::UpdateTextLineRenderBox()
	{
		int width, height;
		((CTextLine*)this)->GetTextSize(&width, &height);
		
		int pWidth = m_pParent->GetWidth();
		int pHeight = m_pParent->GetHeight();

		if (m_x - m_pParent->m_renderBox.left < 0)
			m_renderBox.left = -m_x + m_pParent->m_renderBox.left;
		else
			m_renderBox.left = 0;

		if (m_y - m_pParent->m_renderBox.top < 0)
			m_renderBox.top = -m_y + m_pParent->m_renderBox.top;
		else
			m_renderBox.top = 0;

		if (m_x + width > pWidth - m_pParent->m_renderBox.right)
			m_renderBox.right = m_x + width - pWidth + m_pParent->m_renderBox.right;
		else
			m_renderBox.right = 0;

		if (m_y + height > pHeight - m_pParent->m_renderBox.bottom)
			m_renderBox.bottom = m_y + height - pHeight + m_pParent->m_renderBox.bottom;
		else
			m_renderBox.bottom = 0;
	}

	void CWindow::UpdateRenderBox()
	{
		if (!m_isInsideRender || !m_pParent)
			memset(&m_renderBox, 0, sizeof(m_renderBox));
		else
		{
			int width = m_lWidth;
			int height = m_lHeight;
			int pWidth = m_pParent->GetWidth();
			int pHeight = m_pParent->GetHeight();

			if (m_x - m_pParent->m_renderBox.left < 0)
				m_renderBox.left = -m_x + m_pParent->m_renderBox.left;
			else
				m_renderBox.left = 0;

			if (m_y - m_pParent->m_renderBox.top < 0)
				m_renderBox.top = -m_y + m_pParent->m_renderBox.top;
			else
				m_renderBox.top = 0;

			if (m_x + width > pWidth - m_pParent->m_renderBox.right)
				m_renderBox.right = m_x + width - pWidth + m_pParent->m_renderBox.right;
			else
				m_renderBox.right = 0;

			if (m_y + height > pHeight - m_pParent->m_renderBox.bottom)
				m_renderBox.bottom = m_y + height - pHeight + m_pParent->m_renderBox.bottom;
			else
				m_renderBox.bottom = 0;
		}
		
		OnUpdateRenderBox();
	}
#endif

//-----------------------------------//

//Search:
	bool CWindow::IsChild(CWindow * pWin)

//Replace with:
#ifdef INGAME_WIKI
	bool CWindow::IsChild(CWindow* pWin, bool bCheckRecursive)
#else
	bool CWindow::IsChild(CWindow * pWin)
#endif

//-----------------------------------//

//Search -> Inside CWindow::IsChild function:
			if (*itor == pWin)
				return true;

//Add after:
#ifdef INGAME_WIKI
			if (bCheckRecursive)
				if ((*itor)->IsChild(pWin, true))
					return true;
#endif

//-----------------------------------//

//Search:
	CWindow * CWindow::PickTopWindow(long x, long y)
	{
		std::list<CWindow *>::reverse_iterator ritor = m_pChildList.rbegin();
		for (; ritor != m_pChildList.rend(); ++ritor)
		{
			CWindow * pWin = *ritor;
			if (pWin->IsShow())
				if (pWin->IsIn(x, y))
					if (!pWin->IsFlag(CWindow::FLAG_NOT_PICK))
						return pWin;
		}

		return NULL;
	}

//Add after:
#ifdef INGAME_WIKI
	void CWindow::iSetRenderingRect(int iLeft, int iTop, int iRight, int iBottom)
	{
		m_renderingRect.left = iLeft;
		m_renderingRect.top = iTop;
		m_renderingRect.right = iRight;
		m_renderingRect.bottom = iBottom;

		OnSetRenderingRect();
	}

	void CWindow::SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom)
	{
		float fWidth = float(GetWidth());
		float fHeight = float(GetHeight());
		if (IsType(CTextLine::Type()))
		{
			int iWidth, iHeight;
			((CTextLine*)this)->GetTextSize(&iWidth, &iHeight);
			fWidth = float(iWidth);
			fHeight = float(iHeight);
		}
		
		iSetRenderingRect(fWidth * fLeft, fHeight * fTop, fWidth * fRight, fHeight * fBottom);
	}

	int CWindow::GetRenderingWidth()
	{
		return max(0, GetWidth() + m_renderingRect.right + m_renderingRect.left);
	}

	int CWindow::GetRenderingHeight()
	{
		return max(0, GetHeight() + m_renderingRect.bottom + m_renderingRect.top);
	}

	void CWindow::ResetRenderingRect(bool bCallEvent)
	{
		m_renderingRect.bottom = m_renderingRect.left = m_renderingRect.right = m_renderingRect.top = 0;

		if (bCallEvent)
			OnSetRenderingRect();
	}

	void CWindow::OnSetRenderingRect()
	{
	}
#endif

//-----------------------------------//

//Search:
	CBox::CBox(PyObject * ppyObject) : CWindow(ppyObject), m_dwColor(0xff000000)

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	CUiWikiRenderTarget::~CUiWikiRenderTarget() = default;
	CUiWikiRenderTarget::CUiWikiRenderTarget(PyObject * ppyObject) :
															CWindow(ppyObject),
															m_dwIndex(-1) {}
	
	/*----------------------------
	--------PUBLIC CLASS FUNCTIONS
	-----------------------------*/
	
	bool CUiWikiRenderTarget::SetWikiRenderTargetModule(int iRenderTargetModule)
	{
		if (!CWikiRenderTargetManager::Instance().GetRenderTarget(iRenderTargetModule))
		{
			if (!CWikiRenderTargetManager::Instance().CreateRenderTarget(iRenderTargetModule, GetWidth(), GetHeight()))
			{
				TraceError("CWikiRenderTargetManager could not create the texture. w %d h %d", GetWidth(), GetHeight());
				return false;
			}
		}
		
		m_dwIndex = iRenderTargetModule;
		
		UpdateRect();
		return true;
	}
	
	void CUiWikiRenderTarget::OnUpdateRenderBox()
	{
		if (m_dwIndex == -1 /*(CPythonWikiRenderTarget::START_MODULE)*/)
			return;
		
		auto target = CWikiRenderTargetManager::Instance().GetRenderTarget(m_dwIndex);
		if (!target)
			return;
		
		target->SetRenderingBox(&m_renderBox);
	}
	
	/*----------------------------
	-----PROTECTED CLASS FUNCTIONS
	-----------------------------*/
	
	void CUiWikiRenderTarget::OnRender()
	{
		if (m_dwIndex == -1 /*(CPythonWikiRenderTarget::START_MODULE)*/)
			return;
		
		auto target = CWikiRenderTargetManager::Instance().GetRenderTarget(m_dwIndex);
		if (!target)
			return;
		
		target->SetRenderingRect(&m_rect);
		target->RenderTexture();
	}
#endif

//-----------------------------------//

//Search:
	void CBar::OnRender()
	{
		CPythonGraphic::Instance().SetDiffuseColor(m_dwColor);
		CPythonGraphic::Instance().RenderBar2d(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	}

//Replace whole routine with:
	void CBar::OnRender()
	{
		CPythonGraphic::Instance().SetDiffuseColor(m_dwColor);
#ifdef INGAME_WIKI
		CPythonGraphic::Instance().RenderBar2d(m_rect.left + m_renderBox.left, m_rect.top + m_renderBox.top, m_rect.right - m_renderBox.right, m_rect.bottom - m_renderBox.bottom);
#else
		CPythonGraphic::Instance().RenderBar2d(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
#endif
	}

//-----------------------------------//

//Search:
	CTextLine::~CTextLine()
	{
		m_TextInstance.Destroy();
	}

//Add after:
#ifdef INGAME_WIKI
	DWORD CTextLine::Type()
	{
		static DWORD s_dwType = GetCRC32("CTextLine", strlen("CTextLine"));
		return (s_dwType);
	}
#endif

//-----------------------------------//

//Search:
	void CTextLine::HideCursor()
	{
		m_TextInstance.HideCursor();
	}

//Add after:
#ifdef INGAME_WIKI
	bool CTextLine::IsShowCursor()
	{
		return m_TextInstance.IsShowCursor();
	}
#endif

//-----------------------------------//

//Search -> Inside CTextLine::OnSetText routine:
		m_TextInstance.SetValue(c_szText);
		m_TextInstance.Update();

//Add after:
#ifdef INGAME_WIKI
		if (m_isInsideRender)
			UpdateRenderBoxRecursive();
#endif

//-----------------------------------//

//Search:
	void CTextLine::OnUpdate()

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	bool CTextLine::IsShow()
	{
		if (!m_bShow)
			return false;
		
		if (m_isInsideRender)
		{
			int cW, cH;
			GetTextSize(&cW, &cH);
			if (m_renderBox.left + m_renderBox.right >= cW || m_renderBox.top + m_renderBox.bottom >= cH)
				return false;
		}
		
		return true;
	}
#endif

//-----------------------------------//

//Search:
	void CTextLine::OnRender()
	{
		if (IsShow())
			m_TextInstance.Render();
	}

//Add after:
#ifdef INGAME_WIKI
	int CTextLine::GetRenderingWidth()
	{
		int iTextWidth, iTextHeight;
		GetTextSize(&iTextWidth, &iTextHeight);

		return iTextWidth + m_renderingRect.right + m_renderingRect.left;
	}

	int CTextLine::GetRenderingHeight()
	{
		int iTextWidth, iTextHeight;
		GetTextSize(&iTextWidth, &iTextHeight);

		return iTextHeight + m_renderingRect.bottom + m_renderingRect.top;
	}

	void CTextLine::OnSetRenderingRect()
	{
		int iTextWidth, iTextHeight;
		GetTextSize(&iTextWidth, &iTextHeight);

		m_TextInstance.iSetRenderingRect(m_renderingRect.left, -m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
	}
#endif

//-----------------------------------//

//Search:
	void CExpandedImageBox::SetRenderingMode(int iMode)
	{
		((CGraphicExpandedImageInstance*)m_pImageInstance)->SetRenderingMode(iMode);
	}

//Add after:
#ifdef INGAME_WIKI
	int CExpandedImageBox::GetRenderingWidth()
	{
		return CWindow::GetWidth() + m_renderingRect.right + m_renderingRect.left;
	}
	
	int CExpandedImageBox::GetRenderingHeight()
	{
		return CWindow::GetHeight() + m_renderingRect.bottom + m_renderingRect.top;
	}
	
	void CExpandedImageBox::OnSetRenderingRect()
	{
		if (!m_pImageInstance)
			return;
		
		((CGraphicExpandedImageInstance*)m_pImageInstance)->iSetRenderingRect(m_renderingRect.left, m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
	}
	
	void CExpandedImageBox::SetExpandedRenderingRect(float fLeftTop, float fLeftBottom, float fTopLeft, float fTopRight, float fRightTop, float fRightBottom, float fBottomLeft, float fBottomRight)
	{
		if (!m_pImageInstance)
			return;
		
		((CGraphicExpandedImageInstance*)m_pImageInstance)->SetExpandedRenderingRect(fLeftTop, fLeftBottom, fTopLeft, fTopRight, fRightTop, fRightBottom, fBottomLeft, fBottomRight);
	}
	
	void CExpandedImageBox::SetTextureRenderingRect(float fLeft, float fTop, float fRight, float fBottom)
	{
		if (!m_pImageInstance)
			return;
		
		((CGraphicExpandedImageInstance*)m_pImageInstance)->SetTextureRenderingRect(fLeft, fTop, fRight, fBottom);
	}
	
	DWORD CExpandedImageBox::GetPixelColor(DWORD x, DWORD y)
	{
		return ((CGraphicExpandedImageInstance*)m_pImageInstance)->GetPixelColor(x, y);
	}
	
	void CExpandedImageBox::OnUpdateRenderBox()
	{
		if (!m_pImageInstance)
			return;
		
		((CGraphicExpandedImageInstance*)m_pImageInstance)->SetRenderBox(m_renderBox);
	}
#endif

//-----------------------------------//

//Search:
	void CButton::SetCurrentVisual(CGraphicImageInstance * pVisual)

//Replace with:
#ifdef INGAME_WIKI
	void CButton::SetCurrentVisual(CGraphicExpandedImageInstance* pVisual)
#else
	void CButton::SetCurrentVisual(CGraphicImageInstance * pVisual)
#endif

//-----------------------------------//

//Search -> Inside CButton::SetCurrentVisual routine:
		m_pcurVisual = pVisual;
		m_pcurVisual->SetPosition(m_rect.left, m_rect.top);

//Add after:
#ifdef INGAME_WIKI
		if (m_pcurVisual == &m_upVisual)
			PyCallClassMemberFunc(m_poHandler, "OnSetUpVisual", BuildEmptyTuple());
		else if (m_pcurVisual == &m_overVisual)
			PyCallClassMemberFunc(m_poHandler, "OnSetOverVisual", BuildEmptyTuple());
		else if (m_pcurVisual == &m_downVisual)
			PyCallClassMemberFunc(m_poHandler, "OnSetDownVisual", BuildEmptyTuple());
		else if (m_pcurVisual == &m_disableVisual)
			PyCallClassMemberFunc(m_poHandler, "OnSetDisableVisual", BuildEmptyTuple());
#endif

//-----------------------------------//

//Search:
	BOOL CButton::IsPressed()
	{
		return m_isPressed;
	}

//Add after:
#ifdef INGAME_WIKI
	void CButton::OnSetRenderingRect()
	{
		m_upVisual.iSetRenderingRect(m_renderingRect.left, m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
		m_overVisual.iSetRenderingRect(m_renderingRect.left, m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
		m_downVisual.iSetRenderingRect(m_renderingRect.left, m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
		m_disableVisual.iSetRenderingRect(m_renderingRect.left, m_renderingRect.top, m_renderingRect.right, m_renderingRect.bottom);
	}
#endif
