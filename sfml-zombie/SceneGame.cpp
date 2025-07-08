#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Blood.h"

SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/blood.png");

	AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	for (int i = 0; i < 50; ++i)
	{
		Blood* blood = (Blood*)AddGameObject(new Blood());
		blood->SetActive(false);
		bloodPool.push_back(blood);
	}
	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});

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

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(10);
	}
	
	if (InputMgr::GetMouseButton(sf::Mouse::Button::Right))
	{
		Skill();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
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
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		zombieList.push_back(zombie);
	}
}

void SceneGame::SpawnBlood(const sf::Vector2f& pos)
{
	std::cout << "bloodPool size: " << bloodPool.size() << std::endl;
	for (auto b : bloodPool)
	{
		if (b == nullptr)
			std::cout << "bloodPool contains nullptr!" << std::endl;
	}

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
	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		int hp = 0;
		if ((*it)->GetActive())
		{
			hp = (*it)->GetHp();
			std::cout << "Before" << (*it)->GetHp() << std::endl;
			//std::cout << "Skill_HP" << hp << std::endl;
			hp -= 10;
			(*it)->SetHp(hp);
			std::cout << "After" << (*it)->GetHp()<< std::endl;
		}
		else {
			++it;
		}
	}
	////int hp = 0;
	//for (Zombie* zombie : zombieList)
	//{
	//	int hp = 0;
	//	if (zombie->GetActive()==true)
	//	{
	//		/*std::cout << "Before" << zombie->GetHp() << std::endl;
	//		zombie->OnDamage(10);
	//		std::cout << "After" << zombie->GetHp() << std::endl;
	//		break;*/

	//		hp = zombie->GetHp();
	//		std::cout << "Before" << zombie->GetHp() << std::endl;
	//		//std::cout << "Skill_HP" << hp << std::endl;
	//		hp -= 10;
	//		zombie->SetHp(hp);
	//		std::cout << "After" << zombie->GetHp() << std::endl;
	//	}
	//	else
	//	{

	//	}

	//}
}