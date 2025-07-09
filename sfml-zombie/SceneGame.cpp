#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Blood.h"
#include "GameUI.h"
#include "Item.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{
}

void SceneGame::Init()
{
	uiView.setSize(1280.f, 720.f);

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/blood.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/acceleration.png");

	map = (TileMap*)AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));
	AddGameObject(new Item("Item"));

	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);

		Item* item = (Item*)AddGameObject(new Item());
		item->SetActive(false);
		itemPool.push_back(item);
	}

	for (int i = 0; i < 50; ++i)
	{
		Blood* blood = (Blood*)AddGameObject(new Blood());
		blood->SetActive(false);
		bloodPool.push_back(blood);
	}

	ui = (GameUI*)AddGameObject(new GameUI("UI"));
	ui->SetPlayer(player);
	ui->SetStageLevel(stageLevel);

	Scene::Init();
}

void SceneGame::Enter()
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
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	for (Blood* blood : bloodList)
	{
		blood->SetActive(false);
		bloodPool.push_back(blood);
	}
	bloodList.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
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
			if (zombieCount == 0)
			{
				StageClear();
			}
		}
		else
		{
			++it;
		}
	}

	auto it2 = bloodList.begin();
	while (it2 != bloodList.end())
	{
		if (!(*it2)->GetActive())
		{
			bloodPool.push_back(*it2);
			it2 = bloodList.erase(it2);
		}
		else
		{
			++it2;			
		}
	}

	auto It = itemList.begin();
	while (It != itemList.end())
	{
		if (!(*It)->GetActive())
		{
			itemPool.push_back(*It);
			It = itemList.erase(It);
		}
		else
		{
			++It;
		}
	}

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(10);
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		std::cout << "Skill Use" << std::endl;
		Skill();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(Id);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}

void SceneGame::SpawnZombies(int count)
{
	float radius = map->GetBounds().width * 0.5f;
	for (int i = 0; i < count; ++i)
	{
		if (zombiePool.empty())
		{
			zombie = (Zombie*)AddGameObject(new Zombie());
			zombie->Init();
		}
		else
		{
			zombie = zombiePool.front();
			zombiePool.pop_front();
			zombie->SetActive(true);
		}
		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * radius);
		zombieList.push_back(zombie);
		zombieCount++;
	}
	ui->UpdateZombieCountMessage(zombieCount);
}

void SceneGame::StageClear()
{
	SCENE_MGR.ChangeScene((SceneIds)((int)Id + 1));
}

void SceneGame::SpawnItems(int count)
{
	sf::FloatRect bounds = map->GetBounds();
	bounds.left -= bounds.width * 0.5f;
	bounds.top -= bounds.height * 0.5f;

	for (int i = 0; i < count; ++i)
	{
		Item* item = nullptr;
		if (itemPool.empty())
		{
			item = (Item*)AddGameObject(new Item());
			item->Init();
		}
		else
		{
			item = itemPool.front();
			itemPool.pop_front();
			item->SetActive(true);
		}
		item->SetType((Item::Types)Utils::RandomRange(0, Item::TotalTypes));
		item->Reset();
		sf::Vector2f pos = Utils::RandomPointInRect(bounds);
		item->SetPosition(pos);
		itemList.push_back(item);
	}
}

void SceneGame::SpawnBlood(const sf::Vector2f& pos)
{
	Blood* blood = nullptr;

	if (bloodPool.empty())
	{
		blood = (Blood*)AddGameObject(new Blood());
		blood->Init();
	}
	else
	{
		blood = bloodPool.front();
		bloodPool.pop_front();
		blood->SetActive(true);
	}
	blood->Reset(pos);
	bloodList.push_back(blood);
}

void SceneGame::Skill()
{
	if (player->GetMp() >= 5)
	{
		std::cout << "Before MP: " << player->GetMp() << std::endl;
		player->SetMp(0);
		for (Zombie* zombie : zombieList)
		{
			if (zombie->GetActive())
			{
				std::cout << "Before HP" << zombie->GetHp() << std::endl;
				zombie->OnDamage(10);
				std::cout << "After HP" << zombie->GetHp() << std::endl;
			}
		}
		std::cout << "After MP " << player->GetMp() << std::endl;
	}
	else
	{
		std::cout << "MP lack" << std::endl;
	}
}
