/* File: EterLib/GrpExpandedImageInstance.h */

//Search:
#include "GrpImageInstance.h"

//Add after:
#ifdef INGAME_WIKI
typedef struct tagExpandedRECT
{
	LONG	left_top;
	LONG	left_bottom;
	LONG	top_left;
	LONG	top_right;
	LONG	right_top;
	LONG	right_bottom;
	LONG	bottom_left;
	LONG	bottom_right;
} ExpandedRECT, * PEXPANDEDRECT;
#endif

//-----------------------------------//

//Search -> Inside CGraphicExpandedImageInstance class:
		void SetRenderingMode(int iMode);

//Add after:
#ifdef INGAME_WIKI
		void SetRenderBox(RECT& renderBox);
		DWORD GetPixelColor(DWORD x, DWORD y);
		int GetRenderWidth();
		int GetRenderHeight();
		
		void SetExpandedRenderingRect(float fLeftTop, float fLeftBottom, float fTopLeft, float fTopRight, float fRightTop, float fRightBottom, float fBottomLeft, float fBottomRight);
		void iSetRenderingRect(int iLeft, int iTop, int iRight, int iBottom);
		void iSetExpandedRenderingRect(int iLeftTop, int iLeftBottom, int iTopLeft, int iTopRight, int iRightTop, int iRightBottom, int iBottomLeft, int iBottomRight);
		void SetTextureRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
#endif

//-----------------------------------//

//Search -> Inside CGraphicExpandedImageInstance class:
	protected:
		float m_fDepth;

//Add !!BEFORE!!:
#ifdef INGAME_WIKI
	private:
		void SaveColorMap();
#endif

//-----------------------------------//

//Search -> Inside CGraphicExpandedImageInstance class:
		RECT m_RenderingRect;

//Replace with:
#ifdef INGAME_WIKI
		ExpandedRECT m_RenderingRect;
		RECT m_TextureRenderingRect;
		RECT m_renderBox;
		DWORD* m_pColorMap;
#else
		RECT m_RenderingRect;
#endif
