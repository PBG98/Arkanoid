#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	static GameManager& GetInstance();

	unsigned int GetScore();
	void IncreaseScore();
	void DecreaseLife();

	bool IsGameOver();

private:
	unsigned int score;
	int life;
};

