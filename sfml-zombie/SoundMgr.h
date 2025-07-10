#pragma once
class SoundMgr
{
public:
	static sf::Sound hit;
	static sf::Sound pickUp;
	static sf::Sound powerUp;
	static sf::Sound reload;
	static sf::Sound reloadFailed;
	static sf::Sound shoot;
	static sf::Sound splat;

	static void Init();
};