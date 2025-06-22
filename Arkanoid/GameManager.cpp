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

void GameManager::UpdateGameStatus(COMMON::GameStatus status)
{
	this->status = status;
}

bool GameManager::CheckGameStatus(COMMON::GameStatus status)
{
	return this->status == status;
}

unsigned int GameManager::GetScore()
{
	return score;
}

void GameManager::IncreaseScore(size_t score)
{
	this->score += score;
}

void GameManager::DecreaseLife()
{
	--life;
}

bool GameManager::IsGameOver()
{
	return life <= 0;
}

void GameManager::Reset()
{
	status = COMMON::GameStatus::Ready;
	score = 0;
	life = 3;
}
