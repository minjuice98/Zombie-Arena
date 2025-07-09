#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/background.png");

	titleMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	titleMessage.setCharacterSize(75);
	Utils::SetOrigin(titleMessage, Origins::ML);
	titleMessage.setPosition({ 200.f,380.f });
	titleMessage.setString("PRESS SPACE TO START");

	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Upgrade);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(titleMessage);
	Scene::Draw(window);
}