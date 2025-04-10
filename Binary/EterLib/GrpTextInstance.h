/* File: EterLib/GrpTextInstance.h */

//Search -> Inside CGraphicTextInstance class:
		void Render(RECT * pClipRect = NULL);

//Add after:
#ifdef INGAME_WIKI
		void SetFixedRenderPos(WORD startPos, WORD endPos) { m_startPos = startPos; m_endPos = endPos; m_isFixedRenderPos = true; }
		void GetRenderPositions(WORD& startPos, WORD& endPos) { startPos = m_startPos; endPos = m_endPos; }
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		void HideCursor();

//Add after:
#ifdef INGAME_WIKI
		bool IsShowCursor();
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		void SetColor(float r, float g, float b, float a = 1.0f);

//Add after:
#ifdef INGAME_WIKI
		DWORD GetColor() const;
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		void SetPosition(float fx, float fy, float fz = 0.0f);

//Add after:
#ifdef INGAME_WIKI
		float GetPositionX() const { return m_v3Position.x; }
		float GetPositionY() const { return m_v3Position.y; }
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		int GetHorizontalAlign();

//Add after:
#ifdef INGAME_WIKI
		void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
		void iSetRenderingRect(int iLeft, int iTop, int iRight, int iBottom);
		
		void SetRenderBox(RECT& renderBox);
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		BYTE m_vAlign;

//Add after:
#ifdef INGAME_WIKI
		WORD m_startPos, m_endPos;
		bool m_isFixedRenderPos;
		RECT m_renderBox;
#endif

//-----------------------------------//

//Search -> Inside CGraphicTextInstance class:
		std::vector<SHyperlink> m_hyperlinkVector;

//Add after:
#ifdef INGAME_WIKI
		bool m_bUseRenderingRect;
		RECT m_RenderingRect;
#endif
