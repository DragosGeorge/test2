/* File: EterLib/GrpBase.h */

//Search -> Inside CGraphicBase class:
		float		GetFOV();

/*Replace with:
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
	If you have public render target system you already have this functions and
		changes, if yes, ignore this
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
		float		GetFOV() const;
		float		GetAspect() const;
		float		GetNear() const;
		float		GetFar() const;
#else
		float		GetFOV();
#endif
