/* File: EterLib/Camera.cpp */

//Search -> Inside CCameraManager constructor:
	AddCamera(DEFAULT_ORTHO_CAMERA);

//Add after:
#ifdef INGAME_WIKI
	AddCamera(INGAME_WIKI_CAMERA);
#endif
