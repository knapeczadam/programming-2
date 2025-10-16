// Knapecz, Adam - 1DAE11
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"
#include "GameObject.h"

Game::Game()
{

}
Game::~Game()
{
	// for (Enemy* ptr : m_pEnemies)
	// {
	// 	delete ptr;
	// }
	// m_pEnemies.clear();
	//
	// for (PickUp* ptr : m_pPickUps)
	// {
	// 	delete ptr;
	// }
	// m_pPickUps.clear();
	//
	// for (Weapon* ptr : m_pWeapons)
	// {
	// 	delete ptr;
	// }
	// m_pWeapons.clear();
	for (GameObject* ptr : m_pGameObjects)
	{
		delete ptr;
	}
	m_pGameObjects.clear();
}

void Game::AddEnemy()
{
	//m_pEnemies.push_back(new Enemy());
	m_pGameObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	// m_pPickUps.push_back(new PickUp());
	m_pGameObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	// m_pWeapons.push_back(new Weapon());
	m_pGameObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };

	std::cout << "--> All Game objects\n";
	// for (Enemy* ptr : m_pEnemies)
	// {
	// 	++seqNr;
	// 	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	// }
	// for (PickUp* ptr : m_pPickUps)
	// {
	// 	++seqNr;
	// 	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	// }
	// for (Weapon* ptr : m_pWeapons)
	// {
	// 	++seqNr;
	// 	std::cout << seqNr << ": " << ptr->ToString() << "\n";
	// }
	for (GameObject* ptr : m_pGameObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}
}

void Game::ReportEnemies() const
{
	std::cout << "--> Enemies\n";
	// for (Enemy* ptr : m_pEnemies)
	// {
	// 	std::cout  << ptr->ToString() << "\n";
	// }
	for (GameObject* ptr : m_pGameObjects)
	{
		Enemy* pEnemy{ dynamic_cast<Enemy*>(ptr) };
		if (pEnemy != nullptr)
		{
			std::cout << pEnemy->ToString() << "\n";
		}
	}
}