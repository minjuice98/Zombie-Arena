#include "stdafx.h"
#include "Framework.h"


void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);

    texIds.push_back("graphics/ammo_icon.png");

    fontIds.push_back("fonts/zombiecontrol.ttf");

    soundIds.push_back("sound/hit.wav");
    soundIds.push_back("sound/pickup.wav");
    soundIds.push_back("sound/powerup.wav");
    soundIds.push_back("sound/reload.wav");
    soundIds.push_back("sound/reload_failed.wav");
    soundIds.push_back("sound/shoot.wav");
    soundIds.push_back("sound/splat.wav");

	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

    Utils::Init();
	InputMgr::Init();
	SCENE_MGR.Init();
    SoundMgr::Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        time += deltaTime;
        realTime = realDeltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateEvent(event);
        }

        InputMgr::Update(deltaTime);

        // Update

#ifdef DEF_DEV
        if (InputMgr::GetKeyDown(sf::Keyboard::F10))
        {
            Variables::isDrawHitBox = !Variables::isDrawHitBox;
        }
#endif


        SCENE_MGR.Update(deltaTime);

        // Draw
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
	SCENE_MGR.Release();

	SOUNDBUFFER_MGR.Unload(soundIds);
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
}


void Framework::SetPauseStatus(bool pause)
{
    timeScale = pause ? 0 : 1.f;
}
