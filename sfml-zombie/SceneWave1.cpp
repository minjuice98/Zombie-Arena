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
	stageLevel = 1;
	SceneGame::Init();

	map->SetSize({ 10,10 });
	map->Init();

	ui->SetStageLevel(stageLevel);
}

void SceneWave1::Enter()
{
	SceneGame::Enter();

	stageLevel = 1;
	SpawnItems(5);
	SpawnZombies(5);
}

void SceneWave1::Exit()
{
	SceneGame::Exit();
}

void SceneWave1::Update(float dt)
{
	SceneGame::Update(dt);
}

void SceneWave1::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}