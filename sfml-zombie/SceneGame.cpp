#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Blood.h"
#include "GameUI.h"
#include "Item.h"
#include "Framework.h"

int SceneGame::score = 0;

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

	
	ExitMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));

	const int CHARSIZE = 70;
	PauseMessage.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));	
	ExitMessage.setCharacterSize(CHARSIZE);			
	ExitMessage.setPosition({ 580.f,250.f });	
	ExitMessage.setString("exit");


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

	flashEffect.setFillColor(sf::Color(255, 255, 255, 200));

	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	stageLevel = 1;
	zombieCount = 0;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	flashEffect.setSize(windowSize);
	flashEffect.setPosition(0, 0);

	ApplyUpgrade();
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

	for (Item* item : itemList)
	{
		item->SetActive(false);
		itemPool.push_back(item);
	}
	itemList.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	GenerationTime += dt;
	Scene::Update(dt);

	SpawnItems(30);
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
			ui->UpdateManaMessage(player->GetMp());
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

	worldView.setCenter(player->GetPosition());

	if (isFlashing)
	{
		flashTimer += dt;
		if (flashTimer >= flashDuration)
		{
			isFlashing = false;
			flashTimer = 0.f;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		pause = !pause;
		FRAMEWORK.SetPauseStatus(pause);
	}
	if (pause)
	{
		PauseMenu();


	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		std::cout << "Skill Use" << std::endl;
		Skill();
	}

	/*if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		score = 0;
		SCENE_MGR.ChangeScene(Id);
	}*/
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
	
	if (isFlashing)
	{
		window.draw(flashEffect);
	}
	if (pause)
	{	
		window.draw(ExitMessage);
	}
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

void SceneGame::PauseMenu()
{
	if (Utils::PointInTransformBounds(AgainMessage, AgainMessage.getLocalBounds(), cursor.getPosition()))
	{
		AgainMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			SCENE_MGR.ChangeScene(SceneIds::Title);
		}
	}
	else
	{
		AgainMessage.setFillColor(sf::Color::White);
	}

	if (Utils::PointInTransformBounds(ExitMessage, ExitMessage.getLocalBounds(), cursor.getPosition()))
	{
		ExitMessage.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			FRAMEWORK.GetWindow().close();
		}
	}
	else
	{
		ExitMessage.setFillColor(sf::Color::White);
	}

}

void SceneGame::StageClear()
{
	SceneUpgrade::nextSceneId = (SceneIds)((int)Id + 1);
	SCENE_MGR.ChangeScene(SceneIds::Upgrade);
}

void SceneGame::ApplyUpgrade()
{
	for (int i = 0; i < SceneUpgrade::hpUpgradeCount; ++i)
	{
		player->MaxHpUp(50);
	}

	for (int i = 0; i < SceneUpgrade::speedUpgradeCount; ++i)
	{
		player->AddSpeed(50.f);
	}

	for (int i = 0; i < SceneUpgrade::pickupUpgradeCount; ++i)
	{
		GenerationInterval -= 0.6f;
	}
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
			if (GenerationTime >= GenerationInterval)
			{
				item->SetActive(true);
				GenerationTime = 0.f;
			}
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
	if (player->GetMp() >= 4)
	{
		player->SetMp(0);
		ui->UpdateManaMessage(0);
		isFlashing = true;
		flashTimer = 0.f;

		for (Zombie* zombie : zombieList)
		{
			if (zombie->GetActive())
			{
				zombie->OnDamage(100);
				SoundMgr::splat.play();
			}
		}
	}
	else
	{
		std::cout << "MP lack" << player->GetMp() << std::endl;
	}
}