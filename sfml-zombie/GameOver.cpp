#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
	:Scene(SceneIds::GameOver)
{
}

void GameOver::Init()
{
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/crosshair.png");
	deathMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	restartMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	exitMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));

	const int CHARSIZE = 70;
	deathMessage.setCharacterSize(CHARSIZE + 30);
	restartMessage.setCharacterSize(CHARSIZE);
	exitMessage.setCharacterSize(CHARSIZE);



	deathMessage.setPosition({ 330.f,200.f });
	restartMessage.setPosition({ 400.f,450.f });
	exitMessage.setPosition({ 450.f,630.f });

	deathMessage.setString("D E A T H");
	restartMessage.setString("RESTART");
	exitMessage.setString("EXIT");

	Scene::Init();
}
void GameOver::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

}
void GameOver::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}


void GameOver::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	sf::Vector2f mousePos = cursor.getPosition();

	if (Utils::PointInTransformBounds(restartMessage, restartMessage.getLocalBounds(), mousePos))
	{
		restartMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			SCENE_MGR.ChangeScene(SceneIds::Title);
		}
	}
	else
	{
		restartMessage.setFillColor(sf::Color::White);
	}

	if (Utils::PointInTransformBounds(exitMessage, exitMessage.getLocalBounds(), mousePos))
	{
		exitMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			FRAMEWORK.GetWindow().close();
		}
	}
	else
	{
		exitMessage.setFillColor(sf::Color::White);
	}

}
void GameOver::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(deathMessage);
	window.draw(restartMessage);
	window.draw(exitMessage);
	Scene::Draw(window);
	window.draw(cursor);
}