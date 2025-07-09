#include "stdafx.h"
#include "Blood.h"
#include "Zombie.h"

Blood::Blood(const std::string& name)
	: GameObject(name)
{
}

void Blood::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	blood.setPosition(pos);
}

void Blood::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	blood.setRotation(rot);
}

void Blood::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	blood.setScale(s);
}

void Blood::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	blood.setOrigin(o);
}

void Blood::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(blood, preset);
	}
}

void Blood::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void Blood::Release()
{
}

void Blood::Reset()
{
}

void Blood::Reset(const sf::Vector2f& pos)
{
	blood.setTexture(TEXTURE_MGR.Get(texId), true);
	SetPosition(pos);
	time = 0.f;
}

void Blood::Update(float dt)
{
	time += dt;
	if (time >= maxTime)
	{
		SetActive(false);
	}
}

void Blood::Draw(sf::RenderWindow& window)
{
	window.draw(blood);
}