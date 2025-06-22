#pragma once
#include "CommonDefine.h"
class GameManager
{
public:
	GameManager();
	~GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	static GameManager& GetInstance();

	void UpdateGameStatus(COMMON::GameStatus status);
	bool CheckGameStatus(COMMON::GameStatus status);
	unsigned int GetScore();
	void IncreaseScore(size_t score);
	void DecreaseLife();
	bool IsGameOver();
	void Reset();

private:
	COMMON::GameStatus status;
	unsigned int score;
	int life;
};

