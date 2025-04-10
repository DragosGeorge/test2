/* File: EterLib/GrpFontTexture.h */

//Search -> Inside CGraphicFontTexture class:
	bool UpdateTexture();

//Add after:
#ifdef INGAME_WIKI
	void GetTextureSize(float& width, float& height)
	{
		width = float(m_dib.GetWidth());
		height = float(m_dib.GetHeight());
	}
#endif
