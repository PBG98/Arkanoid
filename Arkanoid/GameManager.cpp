#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	score = 0;
	life = 3;
}

GameManager::~GameManager()
{
}

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

unsigned int GameManager::GetScore()
{
	return score;
}

void GameManager::IncreaseScore()
{
	++score;
}

void GameManager::DecreaseLife()
{
	--life;
}

bool GameManager::IsGameOver()
{
	if (life < 0)
	{
		return true;
	}
	return false;
}
