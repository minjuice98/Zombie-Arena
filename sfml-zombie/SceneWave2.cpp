#include "stdafx.h"
#include "SceneWave2.h"
#include "TileMap.h"
#include "GameUI.h"

SceneWave2::SceneWave2()
	: SceneGame(SceneIds::Wave2)
{
}

void SceneWave2::Init()
{
	stageLevel = 2;

	SceneGame::Init();

	map->SetSize({ 20,20 });
	map->Init();

	ui->SetStageLevel(stageLevel);
}

void SceneWave2::Enter()
{
	SceneGame::Enter();

	stageLevel = 2;
	SpawnItems(10);
	SpawnZombies(10);
}

void SceneWave2::Exit()
{
	SceneGame::Exit();
}

void SceneWave2::Update(float dt)
{
	SceneGame::Update(dt);
}

void SceneWave2::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}