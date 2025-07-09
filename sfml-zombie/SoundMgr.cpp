#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init()
{
	hit.setBuffer(SOUNDBUFFER_MGR.Get("sound/hit.wav"));
	pickUp.setBuffer(SOUNDBUFFER_MGR.Get("sound/pickup.wav"));
	powerUp.setBuffer(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));
	reload.setBuffer(SOUNDBUFFER_MGR.Get("sound/reload.wav"));
	reloadFailed.setBuffer(SOUNDBUFFER_MGR.Get("sound/reload_failed.wav"));
	shoot.setBuffer(SOUNDBUFFER_MGR.Get("sound/shoot.wav"));
	splat.setBuffer(SOUNDBUFFER_MGR.Get("sound/splat.wav"));
}