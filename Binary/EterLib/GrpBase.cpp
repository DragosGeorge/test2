/* File: EterLib/GrpBase.cpp */

//Search:
float CGraphicBase::GetFOV()

/*Replace with:
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
	If you have public render target system you already have this functions and
		changes, if yes, ignore this
	/!\/!\/!\/!\/!\/!\/!\/!\/!\
*/
#ifdef INGAME_WIKI
float CGraphicBase::GetFOV() const
{
	return ms_fFieldOfView;
}

float CGraphicBase::GetAspect() const
{
	return ms_fAspect;
}

float CGraphicBase::GetNear() const
{
	return ms_fNearY;
}

float CGraphicBase::GetFar() const
{

	return ms_fFarY;
}
#else
float CGraphicBase::GetFOV()
{
	return ms_fFieldOfView;
}
#endif
