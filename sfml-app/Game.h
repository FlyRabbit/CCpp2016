#pragma once
#include "Aircraft.h"


class Game
{
public:
	Game();
	void run();
	~Game();

private:
	void checkCollision(PFITERATOR object1, PFITERATOR object2);
	bool checkOverstep(PFITERATOR object);
	void changeBullet(int flag);
	void enemyup();
	void entityDestroy();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void layout();
	void listup();
	void processDestroy(PFITERATOR object);
	void processEvents();
	void render();
	void showScore();
	void update(sf::Time deltaTime);


private:
	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mFire, mBullet, mJbBullet;
	int enemyNum, bossNum, sumScore, gameOverFlag, count;

private:
	void fire(Aircraft mPlayer);
	
	std::list<Aircraft> events,backup;
	std::list<PFITERATOR> destroy;
	std::string scoreString;
	Aircraft mPlayer, bullet, enemy, commonBullet, jbBullet, boss;

private:
	sf::Time globalTime, fireTime;
	sf::Sprite backGround1, backGround2, gameOver, sBullet, sJbBullet, sFrame;
	sf::Texture tBackGround, tGameOver, tBullet, tJbBullet, tFrame;
	sf::Clock fireClock;
	sf::RenderWindow mWindow;
	sf::Font font;
	sf::Text text, jbBulletAmmo;
	sf::Music music, bulletSound, enemyAttackSound, enemyDestroySound, gameOverSound, bossSound, bossDestroy;
};

