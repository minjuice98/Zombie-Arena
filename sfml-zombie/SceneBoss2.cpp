#include "stdafx.h"
#include "SceneBoss2.h"
#include "TileMap.h"
#include "Player.h"
#include "GameUI.h"

SceneBoss2::SceneBoss2() : SceneGame(SceneIds::Boss)
{
}

void SceneBoss2::Init()
{
	//fontIds.push_back("fonts/DS-DIGIT.ttf");
	//TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	//go->SetString("Boss");
	//go->SetCharacterSize(30);
	//go->SetFillColor(sf::Color::White);
	//AddGameObject(go);

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");	
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/Boss.png");

	map = (TileMap*)AddGameObject(new TileMap("TileMap"));
	map->SetSize({ 30,30 });

	AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));

	ui = (GameUI*)AddGameObject(new GameUI("UI"));
	ui->SetPlayer(player);
	ui->SetStageLevel(stageLevel);

	Scene::Init();
}

void SceneBoss2::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	stageLevel = 1;
	zombieCount = 0;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneBoss2::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}

void SceneBoss2::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetMouseButton(sf::Mouse::Button::Right))
	{
		std::cout << "¿ìÅ¬¸¯" << std::endl;
		SceneGame::Skill();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Boss);
	}
}

void SceneBoss2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}