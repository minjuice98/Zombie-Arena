#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "GameUI.h"
#include "TileMap.h"
#include <GameOver.h>

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::Heal(int amount)
{
	hp += amount;
	if (hp > maxHp)
	{
		hp = maxHp;
	}
	ui->UpdateHpBar(maxHp, hp);
}

void Player::AddResrveAmmo(int ammo)
{
	reserveAmmo += ammo;
	ui->UpdateAmmoMessage();
}

void Player::AddSpeed(int s)
{
	speed += s;
	isSpeedUp = true;
	SpeedUptime = SpeedDuration;
	std::cout << speed << std::endl;
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::Release()
{
}

void Player::Reset()
{
	sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	ui = (GameUI*)sceneGame->FindGameObject("UI");
	map = (TileMap*)sceneGame->FindGameObject("TileMap");

	sf::FloatRect bounds = map->GetBounds();
	minX = bounds.left - bounds.width * 0.5f;
	minY = bounds.top - bounds.height * 0.5f;
	maxX = minX + bounds.width;
	maxY = minY + bounds.height;

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.0f, 0.f };

	shootTimer = 0.f;
	hp = maxHp;
	currentAmmo = MAX_MAG;
	reserveAmmo = INITIAL_AMMO;
}

void Player::Update(float dt)
{
	auto it = bulletList.begin();
	while (it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (isSpeedUp)
	{
		SpeedUptime -= dt;
		if (SpeedUptime <= 0.f)
		{
			speed -= 100;
			isSpeedUp = false;
			std::cout << speed << std::endl;
		}
	}


	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f pos = position + direction * speed * dt;
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	SetPosition(pos);

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));
	hitBox.UpdateTransform(body, GetLocalBounds());

	shootTimer += dt;
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer > shootInterval && currentAmmo > 0)
	{
		shootTimer = 0.f;
		Shoot();
		SoundMgr::shoot.play();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R) && reserveAmmo > 0 && currentAmmo < MAX_MAG)
	{
		int reloadAmount = MAX_MAG - currentAmmo;
		if (reloadAmount <= reserveAmmo)
		{
			currentAmmo += reloadAmount;
			reserveAmmo -= reloadAmount;
		}
		else
		{
			currentAmmo += reserveAmmo;
			reserveAmmo = 0;
		}

		ui->UpdateAmmoMessage();
		SoundMgr::reload.play();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::Shoot()
{
	Bullet* bullet = nullptr;
	if (bulletPool.empty())
	{
		bullet = new Bullet();
		bullet->Init();
	}
	else
	{
		bullet = bulletPool.front();
		bulletPool.pop_front();
		bullet->SetActive(true);
	}

	bullet->Reset();
	bullet->Fire(position + look * 10.f, look, 1000.f, 100);

	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);

	currentAmmo--;

	ui->UpdateAmmoMessage();
}

void Player::OnDamage(int damage) 
{
	if (!IsAlive())
		return;

	hp = Utils::Clamp(hp - damage, 0, maxHp);
	ui->UpdateHpBar(maxHp, hp);
	SoundMgr::hit.play();
	if (hp == 0)
	{
		//SCENE_MGR.ChangeScene(sceneGame->Id);
		SCENE_MGR.ChangeScene(SceneIds::GameOver);
		SceneUpgrade::speedUpgradeCount = 0;
		SceneUpgrade::hpUpgradeCount = 0;
		SceneUpgrade::pickupUpgradeCount = 0;
		SceneUpgrade::nextSceneId = SceneIds::Wave1;
	}
}