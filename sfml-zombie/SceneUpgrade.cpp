#include "stdafx.h"
#include "SceneUpgrade.h"

int SceneUpgrade::hpUpgradeCount = 0;
int SceneUpgrade::pickupUpgradeCount = 0;
int SceneUpgrade::speedUpgradeCount = 0;
SceneIds SceneUpgrade::nextSceneId = SceneIds::Wave1;

SceneUpgrade::SceneUpgrade()
	: Scene(SceneIds::Upgrade)
{
}

void SceneUpgrade::Init()
{
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/crosshair.png");
	hpUpgradeMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	pickupUpgradeMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	speedUpgradeMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));

	const int CHARSIZE = 70;
	hpUpgradeMessage.setCharacterSize(CHARSIZE);
	speedUpgradeMessage.setCharacterSize(CHARSIZE);
	pickupUpgradeMessage.setCharacterSize(CHARSIZE);

	const int MESSAGEGAP = CHARSIZE + 20.f;
	hpUpgradeMessage.setPosition({ 100.f,200.f });
	speedUpgradeMessage.setPosition({ 100.f,200.f + MESSAGEGAP });
	pickupUpgradeMessage.setPosition({ 100.f,200.f + MESSAGEGAP * 2 });

	hpUpgradeMessage.setString("INCREASED MAX HEALTH");
	speedUpgradeMessage.setString("INCREASED RUN SPEED");
	pickupUpgradeMessage.setString("MORE PICKUPS");

	Scene::Init();
}

void SceneUpgrade::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneUpgrade::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}

void SceneUpgrade::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	sf::Vector2f mousePos = cursor.getPosition();

	if (Utils::PointInTransformBounds(hpUpgradeMessage, hpUpgradeMessage.getLocalBounds(), mousePos))
	{
		hpUpgradeMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			hpUpgradeCount++;
			SCENE_MGR.ChangeScene(nextSceneId);
		}
	}
	else
	{
		hpUpgradeMessage.setFillColor(sf::Color::White);
	}

	if (Utils::PointInTransformBounds(speedUpgradeMessage, speedUpgradeMessage.getLocalBounds(), mousePos))
	{
		speedUpgradeMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			speedUpgradeCount++;
			SCENE_MGR.ChangeScene(nextSceneId);
		}
	}
	else
	{
		speedUpgradeMessage.setFillColor(sf::Color::White);
	}

	if (Utils::PointInTransformBounds(pickupUpgradeMessage, pickupUpgradeMessage.getLocalBounds(), mousePos))
	{
		pickupUpgradeMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			pickupUpgradeCount++;
			SCENE_MGR.ChangeScene(nextSceneId);
		}
	}
	else
	{
		pickupUpgradeMessage.setFillColor(sf::Color::White);
	}
}

void SceneUpgrade::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(hpUpgradeMessage);
	window.draw(speedUpgradeMessage);
	window.draw(pickupUpgradeMessage);
	Scene::Draw(window);
	window.draw(cursor);
}