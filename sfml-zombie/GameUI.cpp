#include "stdafx.h"
#include "GameUI.h"
#include "Player.h"

GameUI::GameUI(const std::string& name)
	: GameObject(name)
{
}

void GameUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	scoreMessage.setFont(FONT_MGR.Get(fontId));
	scoreMessage.setCharacterSize(50);
	scoreMessage.setPosition({ 10.f,10.f });

	ammoMessage.setFont(FONT_MGR.Get(fontId));
	ammoMessage.setCharacterSize(50);
	ammoMessage.setPosition({ 100.f,650.f });

	stageInfoMessage.setCharacterSize(50);
	stageInfoMessage.setFont(FONT_MGR.Get(fontId));
	stageInfoMessage.setPosition({ 840.f,650.f });

	ammoIcon.setTexture(TEXTURE_MGR.Get(ammoTexId));
	ammoIcon.setPosition({ 10.f,650.f });

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition({ 300.f,windowSize.y - 20.f });
	Utils::SetOrigin(hpBar, Origins::ML);
}

void GameUI::Release()
{
}

void GameUI::Reset()
{
	scoreMessage.setString("SCORE:" + std::to_string(score));
	Utils::SetOrigin(scoreMessage, Origins::TL);

	ammoMessage.setString(std::to_string(player->GetCurrentAmmo()) + "/" + std::to_string(player->GetReserveAmmo()));
	Utils::SetOrigin(ammoMessage, Origins::TL);

	stageInfoMessage.setString("WAVE:" + std::to_string(stageLevel) + "     ZOMBIES:" + std::to_string(zombieCount));
	Utils::SetOrigin(stageInfoMessage, Origins::TL);
}

void GameUI::Update(float dt)
{
}

void GameUI::Draw(sf::RenderWindow& window)
{
	window.draw(scoreMessage);
	window.draw(ammoMessage);
	window.draw(stageInfoMessage);
	window.draw(ammoIcon);
	window.draw(hpBar);
}