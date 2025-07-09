#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "Blood.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;//백그라운드 위에 그리겟다.
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	player = (Player*)sceneGame->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	hp = maxHp;
	attackTimer = 0.f;
}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - GetPosition());
	SetRotation(Utils::Angle(direction));
	SetPosition(GetPosition() + direction * speed * dt);

	hitBox.UpdateTransform(body, GetLocalBounds());

	attackTimer += dt;
	if (attackTimer > attackInterval)
	{
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			attackTimer = 0.f;
			player->OnDamage(damage);
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 500;
		speed = 50.f;
		damage = 40;
		attackInterval = 1.f;
		mpUp = 3;
		break;
	case Types::Chaser:
		texId = "graphics/chaser.png";
		maxHp = 250;
		speed = 100.f;
		damage = 30;
		attackInterval = 1.f;
		mpUp = 2;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 150;
		speed = 75.f;
		damage = 20;
		attackInterval = 1.f;
		mpUp = 3;
		break;
	}
}

void Zombie::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		SetActive(false);
		sceneGame->SpawnBlood(GetPosition());

		int mp= player->GetMp();
		mp += mpUp;
		player->SetMp(mp);
	}
}