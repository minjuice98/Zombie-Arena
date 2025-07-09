#include "stdafx.h"
#include "SceneBoss2.h"
#include "TileMap.h"
#include "Player.h"
#include "GameUI.h"
#include "Zombie.h"
#include "GameObject.h"
#include "Bullet.h"

SceneBoss2::SceneBoss2() : SceneGame(SceneIds::Boss)
{
}

void SceneBoss2::Init()
{
	SceneGame::Init();

	map->SetSize({ 30, 30 });
	map->Init();

	texIds.push_back("graphics/Boss.png");

	bossHpBar.setFillColor(sf::Color::Red);
	bossHpBar.setSize({ BOSS_HP_BAR_WIDTH, BOSS_HP_BAR_HEIGHT });
	bossHpBar.setOutlineColor(sf::Color::White);
	bossHpBar.setOutlineThickness(2.f);

	bossHpText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	bossHpText.setCharacterSize(24);
	bossHpText.setFillColor(sf::Color::White);
	bossHpText.setString("BOSS");

	clearText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	clearText.setCharacterSize(72);
	clearText.setFillColor(sf::Color::Yellow);
	clearText.setString("CLEAR!");

	scoreText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	scoreText.setCharacterSize(36);
	scoreText.setFillColor(sf::Color::White);

	Scene::Init();
}

void SceneBoss2::Enter()
{
	SceneGame::Enter();
	stageLevel = 3;
	ui->SetStageLevel(stageLevel);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	boss.setTexture(TEXTURE_MGR.Get("graphics/Boss.png"));
	Utils::SetOrigin(boss, Origins::MC);
	boss.setRotation(0.f);
	boss.setPosition({ windowSize.x * 0.5f, windowSize.y * 0.5f - 200.f });

	hp = maxHp;
	attackTimer = 0.f;
	isCleared = false;

	bossHpBar.setPosition({ windowSize.x * 0.5f - BOSS_HP_BAR_WIDTH * 0.5f, 50.f });
	bossHpText.setPosition({ windowSize.x * 0.5f - 50.f, 20.f });
	Utils::SetOrigin(bossHpText, Origins::MC);

	UpdateBossHpUI();
	SetupClearUI();

	SpawnItems(10);
	SpawnZombies(15);
}

void SceneBoss2::Exit()
{
	SceneGame::Exit();
}

void SceneBoss2::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	GenerationTime += dt;

	if (!isCleared)
	{
		SceneGame::Update(dt);

		// 플레이어 사망 체크 추가
		if (player->GetHp() <= 0)
		{
			SCENE_MGR.ChangeScene(SceneIds::GameOver);
			return;
		}

		if (hp > 0)
		{
			direction = Utils::GetNormal(player->GetPosition() - boss.getPosition());
			boss.setRotation(Utils::Angle(direction));
			boss.setPosition(boss.getPosition() + direction * speed * dt);
			hitBox.UpdateTransform(boss, boss.getLocalBounds());

			attackTimer += dt;
			if (attackTimer > attackInterval)
			{
				if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
				{
					attackTimer = 0.f;
					player->OnDamage(damage);
				}
			}

			for (auto bullet : player->GetBullets())
			{
				if (bullet->GetActive())
				{
					if (Utils::CheckCollision(bullet->GetHitBox().rect, hitBox.rect))
					{
						bullet->SetActive(false);
						OnDamage(100);
						break;
					}
				}
			}
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
			{
				if (player->GetMp() >= 4)
				{
					player->SetMp(0);
					ui->UpdateManaMessage(0);

					OnDamage(200);

					for (auto zombie : zombieList)
					{
						if (zombie->GetActive())
						{
							zombie->OnDamage(200);
						}
					}
				}
			}

		}

		worldView.setCenter(player->GetPosition());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Boss);
	}
}

void SceneBoss2::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);

	if (!isCleared)
	{
		if (hp > 0)
		{
			window.setView(worldView);
			window.draw(boss);
			hitBox.Draw(window);
		}

		window.setView(uiView);
		window.draw(bossHpBar);
		window.draw(bossHpText);
	}
	else
	{
		window.setView(uiView);
		window.draw(clearText);
		window.draw(scoreText);
	}
}

void SceneBoss2::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	UpdateBossHpUI();

	if (hp == 0 && !isCleared)
	{
		SceneGame::SpawnBlood(boss.getPosition());
		SceneGame::score += 500;
		ui->UpdateScoreMessage(SceneGame::score);

		int mp = player->GetMp();
		mp += 5;
		player->SetMp(mp);
		ui->UpdateManaMessage(mp);

		isCleared = true;
		scoreText.setString("SCORE: " + std::to_string(SceneGame::score));
		SetupClearUI();
	}
}

void SceneBoss2::UpdateBossHpUI()
{
	float hpRatio = (float)hp / maxHp;
	bossHpBar.setSize({ BOSS_HP_BAR_WIDTH * hpRatio, BOSS_HP_BAR_HEIGHT });
	bossHpText.setString("BOSS: " + std::to_string(hp) + "/" + std::to_string(maxHp));
	Utils::SetOrigin(bossHpText, Origins::MC);
}

void SceneBoss2::SetupClearUI()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center = { windowSize.x * 0.5f, windowSize.y * 0.5f };

	Utils::SetOrigin(clearText, Origins::TC);
	clearText.setPosition(center.x, center.y - 100.f);

	Utils::SetOrigin(scoreText, Origins::TC);
	scoreText.setPosition(center.x, center.y - 20.f);
}