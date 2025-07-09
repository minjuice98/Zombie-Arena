#include "stdafx.h"
#include "SceneBoss2.h"
#include "TileMap.h"
#include "Player.h"
#include "GameUI.h"
#include "Zombie.h"
#include "GameObject.h"

SceneBoss2::SceneBoss2() : SceneGame(SceneIds::Boss)
{
}

void SceneBoss2::Init()
{
	SceneGame::Init();

	texIds.push_back("graphics/Boss.png");

	map->SetSize({ 30,30 });
	map->Init();

	ui = (GameUI*)AddGameObject(new GameUI("UI"));
	ui->SetPlayer(player);
	ui->SetStageLevel(stageLevel);

	Scene::Init();
}

void SceneBoss2::Enter()
{
	SceneGame::Enter();

	stageLevel = 3;

	Scene::Enter();

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	boss.setTexture(TEXTURE_MGR.Get("graphics/Boss.png"));
	Utils::SetOrigin(boss, Origins::MC);
	boss.setRotation(60.f); 
	boss.setPosition({ windowSize.x*0.5f,windowSize.y*0.5f -200.f });
}

void SceneBoss2::Exit()
{
	SceneGame::Exit();
	Scene::Exit();
}

void SceneBoss2::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	GenerationTime += dt;
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	//sf::Vector2f dir = player->GetPosition() - boss.getPosition();
	//sf::Vector2f direction = Utils::GetNormal(dir);
	//boss.setRotation(Utils::Angle(direction));
	//boss.setPosition(boss.getPosition() + direction * speed * dt);

	direction = Utils::GetNormal(player->GetPosition() - boss.getPosition());
	
	std::cout << "Boss pos" << boss.getPosition().x << ","<<boss.getPosition().y << std::endl;
	std::cout << "Player pos" << player->GetPosition().x << "," << player->GetPosition().y << std::endl;
	std::cout << "direction" << direction.x << "," << direction.y << std::endl;

	boss.setRotation(Utils::Angle(direction));
	boss.setPosition(boss.getPosition() + direction * speed * dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		std::cout << "Skill Use" << std::endl;
		Skill();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Boss);
	}
}

void SceneBoss2::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
	window.setView(worldView);
	window.draw(boss);
}

void SceneBoss2::onDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		//delete boss;
		//sceneGame->SpawnBlood(GetPosition());

		//int mp = player->GetMp();
		//mp += mpUp;
		//player->SetMp(mp);
	}
}
