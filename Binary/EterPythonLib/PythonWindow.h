/* File: EterPythonLib/PythonWindow.h */

//Search:
#include "../eterBase/Utils.h"

/*Add after:
	
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
	In public render target system and others this include already exist here,
		then if you have it, ignore this step
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
	#include <cstdint>
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			bool			IsShow() { return m_bShow; }

//Replace with:
#ifdef INGAME_WIKI
			virtual	bool	IsShow();
			void			OnHideWithChilds();
			void			OnHide();
#else
			bool			IsShow() { return m_bShow; }
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			bool			IsChild(CWindow * pWin);

//Replace with:
#ifdef INGAME_WIKI
			bool			IsChild(CWindow* pWin, bool bCheckRecursive = false);
#else
			bool			IsChild(CWindow * pWin);
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			bool			IsFlag(DWORD flag)		{ return (m_dwFlag & flag) ? true : false;	}

//Add after:
#ifdef INGAME_WIKI
			void			SetInsideRender(BOOL flag);
			void			GetRenderBox(RECT* box);
			void			UpdateTextLineRenderBox();
			void			UpdateRenderBox();
			void			UpdateRenderBoxRecursive();
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			virtual void	OnRender();

//Add after:
#ifdef INGAME_WIKI
			virtual void	OnAfterRender();
			virtual void	OnUpdateRenderBox() {}
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
		protected:
			std::string			m_strName;

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
		public:
			virtual void	iSetRenderingRect(int iLeft, int iTop, int iRight, int iBottom);
			virtual void	SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
			virtual int		GetRenderingWidth();
			virtual int		GetRenderingHeight();
			void			ResetRenderingRect(bool bCallEvent = true);

		private:
			virtual void	OnSetRenderingRect();
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			bool				m_bMovable;

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
			RECT				m_renderingRect;
#endif

//-----------------------------------//

//Search -> Inside CWindow class:
			TWindowContainer	m_pReserveChildList;

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
			BOOL				m_isInsideRender;
			RECT				m_renderBox;
#endif

//-----------------------------------//

//Search:
	class CBox : public CWindow

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	class CUiWikiRenderTarget : public CWindow
	{
		public:
			CUiWikiRenderTarget(PyObject * ppyObject);
			virtual ~CUiWikiRenderTarget();
		
		public:
			bool	SetWikiRenderTargetModule(int iRenderTargetModule);
			void	OnUpdateRenderBox();
		
		protected:
			void	OnRender();
		
		protected:
			DWORD	m_dwIndex;
	};
#endif

//-----------------------------------//

//Search:
	class CTextLine : public CWindow
	{

//Add after:
#ifdef INGAME_WIKI
		public:
			static DWORD Type();
#endif

//-----------------------------------//

//Search -> Inside CTextLine class:
			void SetLimitWidth(float fWidth);

//Add after:
#ifdef INGAME_WIKI
			void SetFixedRenderPos(WORD startPos, WORD endPos) { m_TextInstance.SetFixedRenderPos(startPos, endPos); }
			void GetRenderPositions(WORD& startPos, WORD& endPos) { m_TextInstance.GetRenderPositions(startPos, endPos); }
#endif

//-----------------------------------//

//Search -> Inside CTextLine class:
			void HideCursor();

//Add after:
#ifdef INGAME_WIKI
			bool IsShowCursor();
#endif

//-----------------------------------//

//Search -> Inside CTextLine class:
			void GetTextSize(int* pnWidth, int* pnHeight);

//Add after:
#ifdef INGAME_WIKI
			bool IsShow();
			int GetRenderingWidth();
			int GetRenderingHeight();
			void OnSetRenderingRect();
#endif

//-----------------------------------//

//Search -> Inside CTextLine class:
			virtual void OnSetText(const char * c_szText);

//Add after:
#ifdef INGAME_WIKI
			void OnUpdateRenderBox() {
				UpdateTextLineRenderBox();
				m_TextInstance.SetRenderBox(m_renderBox);
			}
#endif

//-----------------------------------//

//Search -> Inside CImageBox class:
			BOOL LoadImage(const char * c_szFileName);

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
			void UnloadImage()
			{
				OnDestroyInstance();
				SetSize(GetWidth(), GetHeight());
				UpdateRect();
			}
#endif

//-----------------------------------//

//Search -> Inside CExpandedImageBox class:
			void SetRenderingMode(int iMode);

//Add after:
#ifdef INGAME_WIKI
			int GetRenderingWidth();
			int GetRenderingHeight();
			void OnSetRenderingRect();
			void SetExpandedRenderingRect(float fLeftTop, float fLeftBottom, float fTopLeft, float fTopRight, float fRightTop, float fRightBottom, float fBottomLeft, float fBottomRight);
			void SetTextureRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
			DWORD GetPixelColor(DWORD x, DWORD y);
#endif

//-----------------------------------//

//Search -> Inside CExpandedImageBox class:
			void OnDestroyInstance();

//Add after:
#ifdef INGAME_WIKI
			void OnUpdateRenderBox();
#endif

//-----------------------------------//

//Search -> Inside CButton class:
			BOOL IsPressed();

//Add after:
#ifdef INGAME_WIKI
			void OnSetRenderingRect();
#endif

//-----------------------------------//

//Search -> Inside CButton class:
			void SetCurrentVisual(CGraphicImageInstance * pVisual);

//Replace with:
#ifdef INGAME_WIKI
			void SetCurrentVisual(CGraphicExpandedImageInstance* pVisual);
#else
			void SetCurrentVisual(CGraphicImageInstance * pVisual);
#endif

//-----------------------------------//

//Search -> Inside CButton class:
			CGraphicImageInstance * m_pcurVisual;
			CGraphicImageInstance m_upVisual;
			CGraphicImageInstance m_overVisual;
			CGraphicImageInstance m_downVisual;
			CGraphicImageInstance m_disableVisual;

//Replace with:
#ifdef INGAME_WIKI
			CGraphicExpandedImageInstance* m_pcurVisual;
			CGraphicExpandedImageInstance m_upVisual;
			CGraphicExpandedImageInstance m_overVisual;
			CGraphicExpandedImageInstance m_downVisual;
			CGraphicExpandedImageInstance m_disableVisual;
#else
			CGraphicImageInstance * m_pcurVisual;
			CGraphicImageInstance m_upVisual;
			CGraphicImageInstance m_overVisual;
			CGraphicImageInstance m_downVisual;
			CGraphicImageInstance m_disableVisual;
#endif
