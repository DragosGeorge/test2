/* File: EffectLib/EffectManager.h */

//Search -> Inside CEffectManager class:
		void Render();

//Add after:
#ifdef INGAME_WIKI
		void WikiModuleRenderOneEffect(DWORD id);
#endif