#include "stdafx.h"
#include "SceneWave1.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "GameUI.h"

SceneWave1::SceneWave1()
	: SceneGame(SceneIds::Wave1)
{
}

void SceneWave1::Init()
{
	uiView.setSize(1280.f, 720.f);

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/bullet.png");

	map = (TileMap*)AddGameObject(new TileMap("TileMap"));
	map->SetSize({ 10,10 });

	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	ui = (GameUI*)AddGameObject(new GameUI("UI"));
	ui->SetPlayer(player);
	ui->SetStageLevel(stageLevel);

	Scene::Init();
}

void SceneWave1::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	stageLevel = 1;
	score = 0;
	zombieCount = 0;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

	SpawnZombies(5, 250.f);
}

void SceneWave1::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	Scene::Exit();
}

void SceneWave1::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		if (!(*it)->GetActive())
		{
			zombiePool.push_back(*it);
			it = zombieList.erase(it);
			zombieCount--;
			score += 10;
			ui->UpdateScoreMessage(score);
			ui->UpdateZombieCountMessage(zombieCount);
		}
		else
		{
			++it;
		}
	}

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Wave1);
	}
}

void SceneWave1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);
}