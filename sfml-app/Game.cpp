#include "stdafx.h"
#include "Game.h"
#include "Aircraft.h"

SYSTEMTIME FireStartTime, FireEndTime, EnemyStartTime, EnemyEndTime, BossStartTime, BossEndTime;



Game::Game()
:mWindow(sf::VideoMode(BoundaryWidth,BoundaryHigh),"Flight")
,mPlayer(Player)
,bullet(Bullet)
,commonBullet(Bullet)
,jbBullet(JbBullet)
,enemy(Enemy)
,boss(Boss)
,font()
,music()
,enemyNum(0)
,bossNum(0)
,sumScore(0)
,count(0)
,gameOverFlag(Alive)
{
	mIsMovingDown = false;
	mIsMovingUp = false;
	mIsMovingLeft = false;
	mIsMovingRight = false;
	mFire = false;
	mBullet = false;
	mJbBullet = false;
	

	//font
	if (!font.loadFromFile("resources/font/STHeiti_Light.ttc"))
	{

	}


	//common bullet ammo
	jbBulletAmmo.setFont(font);
	std::string jbnum = std::to_string(InitialJbBullet);
	jbBulletAmmo.setString(jbnum);
	jbBulletAmmo.setColor(sf::Color::Black);
	jbBulletAmmo.setCharacterSize(10);
	jbBulletAmmo.setPosition(JbBulletPositionX+15, JbBulletPositionY+18);
	jbBulletAmmo.setStyle(sf::Text::Italic);


	//Boss destroy
	if (!bossDestroy.openFromFile("resources/sound/enemy2_down.ogg"))
	{
		printf("Open enemy2_down failed!\n");
	}


	if (!bossSound.openFromFile("resources/sound/big_spaceship_flying.ogg"))
	{
		printf("Open big_spaceship_flying sound failed!\n");
	}

	//bulletSound
	if (!bulletSound.openFromFile("resources/sound/bullet.ogg"))
	{
		printf("Open bullet sound failed!\n");
	}

	//attack enemies
	if (!enemyAttackSound.openFromFile("resources/sound/enemy1_down.ogg"))
	{
		printf("Opne bullet sound failed!\n");
	}

	//destroy enemies
	if (!enemyDestroySound.openFromFile("resources/sound/enemy3_down.ogg"))
	{
		printf("Opne bullet sound failed!\n");
	}


	//score
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(5.f, 5.f);
	text.setStyle(sf::Text::Italic);

	//gameover
	if (!gameOverSound.openFromFile("resources/sound/game_over.ogg"))
	{
		printf("Opne game_over sound failed!\n");
	}
	gameOverSound.setVolume(170);
	

	//Music
	if (!music.openFromFile("resources/sound/game_music.ogg"))
	{
		printf("Opne music failed!\n");
	}
	music.setLoop(true);
	music.play();

	//background pic
	if (!tBackGround.loadFromFile("resources/image/background.png"))
	{
		printf("load background pic failed!\n");
	}
	backGround1.setTexture(tBackGround);
	backGround1.setPosition(0, -1);
	backGround2.setTexture(tBackGround);
	backGround2.setPosition(0, 1-BoundaryHigh);

	//Bullet
	if (!tBullet.loadFromFile("resources/image/bulletselect.png"))
	{
		printf("load bullet pic failed!\n");
	}
	sBullet.setTexture(tBullet);
	sBullet.setPosition(BulletPositionX, BulletPositionY);


	//frame
	if (!tFrame.loadFromFile("resources/image/frame.png"))
	{
		printf("load frame pic failed!\n");
	}
	sFrame.setTexture(tFrame);
	sFrame.setPosition(BulletPositionX -4, BulletPositionY -8);


	//game over pic
	if (!tGameOver.loadFromFile("resources/image/gameover.png"))
	{
		printf("load game-over pic failed!\n");
	}
	gameOver.setTexture(tGameOver);
	gameOver.setPosition(0, 0);

	//Jb Bullet
	if (!tJbBullet.loadFromFile("resources/image/jbbulletselect.png"))
	{
		printf("load Jb bullet pic failed!\n");
	}
	sJbBullet.setTexture(tJbBullet);
	sJbBullet.setPosition(JbBulletPositionX, JbBulletPositionY);


	mPlayer.eSprite.setPosition(240.f, 700.f);

	
	GetLocalTime(&FireStartTime);
	EnemyStartTime = FireStartTime;
	BossStartTime = FireStartTime;
	events.push_back(mPlayer);

	//srand
	srand((unsigned)time(NULL));
}


void Game::changeBullet(int flag)
{
	switch (flag)
	{
	case Bullet:
		bullet=commonBullet;
		sFrame.setPosition(BulletPositionX-4,BulletPositionY-8);
		break;
	case JbBullet:
		bullet = jbBullet;
		sFrame.setPosition(JbBulletPositionX - 4, JbBulletPositionY - 8);
	default:
		break;
	}
}


void Game::checkCollision(PFITERATOR iterator1, PFITERATOR iterator2)
{
	if ((*iterator1).type == (*iterator2).father || (*iterator2).type == (*iterator1).father || ((*iterator1).father!=Player && (*iterator2).father!=Player)) return;
	int dam = (*iterator2).damage - (*iterator1).Armor*ArmorRate;
	if (dam < 0) dam = 0;
	(*iterator1).HealthPoint -= dam;

	if ((*iterator1).type == Player)
		printf("%d %d\n", (*iterator1).HealthPoint,dam);
	if ((*iterator1).HealthPoint <= 0)
	{
		switch ((*iterator1).type)
		{
		case Bullet:
			(*iterator1).eTexture.loadFromFile("resources/image/smog.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			(*iterator1).flag = Destroy4;
			break;
		case JbBullet:
			(*iterator1).eTexture.loadFromFile("resources/image/smog.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			(*iterator1).flag = Destroy4;
			break;
		case Enemy:
			(*iterator1).eTexture.loadFromFile("resources/image/enemydestroy1.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			enemyAttackSound.play();
			(*iterator1).flag = Destroy1;
			sumScore += (*iterator1).Score;
			break;
		case Player:
			(*iterator1).eTexture.loadFromFile("resources/image/playerdestroy1.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			gameOverSound.play();
			(*iterator1).flag = Destroy1;
			sumScore += (*iterator1).Score;
			gameOverFlag = Destroy1;
			break;
		case Boss:
			(*iterator1).eTexture.loadFromFile("resources/image/bossdestroy1.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			bossDestroy.play();
			(*iterator1).flag = Destroy1;
			sumScore += (*iterator1).Score;
		default:
			break;
		}
	}
	
}


bool Game::checkOverstep(PFITERATOR iterator1)
{
	processDestroy(iterator1);	

	int aircraftY = (int)(*iterator1).eSprite.getPosition().y;

	if (aircraftY > BoundaryHigh + 50 || aircraftY<-50)
		return true;
	return false;
}

//update enemies
void Game::enemyup()
{
	float xPostion = (rand() % (BoundaryWidth - 100)) + 50;
	GetLocalTime(&EnemyEndTime);
	BossEndTime = EnemyEndTime;
	if (abs(EnemyEndTime.wMilliseconds - EnemyStartTime.wMilliseconds) > Level3Time && enemyNum<=200)
	{
		enemyNum++;
		enemy.eSprite.setPosition(xPostion, -50);
		enemy.eVelocity = EnemySpeed + (abs(EnemyEndTime.wMilliseconds - EnemyStartTime.wMilliseconds) / 10);
		enemy.flag = Alive;
		events.push_back(enemy);
		GetLocalTime(&EnemyStartTime);
	}

	if (abs(BossEndTime.wMilliseconds - BossStartTime.wMilliseconds) > Level1Time && bossNum <= 1 && enemyNum>100)
	{
		bossNum++;
		boss.eSprite.setPosition(xPostion, -50);
		boss.eVelocity = BossSpeed + (abs(EnemyEndTime.wMilliseconds - EnemyStartTime.wMilliseconds) / 20);
		boss.flag = Alive;
		events.push_back(boss);
		bossSound.play();
		GetLocalTime(&BossStartTime);
	}
	

}


void Game::entityDestroy()
{
	for (auto i = destroy.begin(); i != destroy.end();i++)
	{
		events.erase(*i);
	}
	destroy.clear();
}


void Game::fire(Aircraft mPlayer)
{
	bulletSound.play();
	int playX = (int)mPlayer.eSprite.getPosition().x;
	int playY = (int)mPlayer.eSprite.getPosition().y;

	bullet.eSprite.setPosition(playX, playY + 3);
	bullet.flag = Alive;
	events.push_back(bullet);
	bullet.ammo--;

	bullet.eSprite.setPosition(playX + 35, playY + 3);
	bullet.flag = Alive;
	events.push_back(bullet);
	bullet.ammo--;
	
	if (bullet.type == JbBullet)
	{
		std::string jbnum = std::to_string(bullet.ammo);
		jbBulletAmmo.setString(jbnum);
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::Space)
		mFire = isPressed;
	else if (key == sf::Keyboard::Num1)
		mBullet = isPressed;
	else if (key == sf::Keyboard::Num2)
		mJbBullet = isPressed;

}


void Game::layout()
{
	sf::Vector2f movement(0.f, BackGroundSpeed);
	backGround1.move(movement * globalTime.asSeconds());
	backGround2.move(movement * globalTime.asSeconds());
	mWindow.draw(backGround1);
	mWindow.draw(backGround2);
	if (backGround1.getPosition().y >= BoundaryHigh)
		backGround1.setPosition(0, 10 - BoundaryHigh);
	if (backGround2.getPosition().y >= BoundaryHigh)
		backGround2.setPosition(0, 10 - BoundaryHigh);

	showScore();
	mWindow.draw(text);
	mWindow.draw(sBullet);
	mWindow.draw(sJbBullet);
	mWindow.draw(sFrame);
	if (bullet.type == JbBullet)
		mWindow.draw(jbBulletAmmo);
}


//update events list
void Game::listup()
{
	entityDestroy();
	for (auto i = events.begin(); i != events.end();i++)
	{

		
		if (checkOverstep(i))  //check whether overstep(bullets and enemies)
			(*i).flag = Destroy4;
		if ((*i).flag<Destroy1  )
			{
				auto j = i;
				j++;
				for (; j != events.end(); j++)
				{
					if ((*i).eSprite.getGlobalBounds().intersects((*j).eSprite.getGlobalBounds()) && (*j).flag < Destroy1)
					{
						checkCollision(i, j);
						checkCollision(j, i);
					}

				}
				if ((*i).type != Player)
				{
					sf::Vector2f movment(0.f, (*i).eVelocity);
					(*i).eSprite.move(movment * globalTime.asSeconds());
					if ((*i).type == Boss)
					{
						if ((*i).eSprite.getPosition().y >= 100 && (*i).eVelocity>0)
							(*i).eVelocity = 0 - (*i).eVelocity;
						if ((*i).eVelocity < 0 && (*i).eSprite.getPosition().y <=50)
							(*i).eVelocity = 0;
					}
				}
				//else
				//	(*i) = mPlayer;
			

			
			}
		if ((*i).flag == Destroy4)
			destroy.push_back(i);
		if ((*i).type == Player)
			(*i).eSprite.setPosition(mPlayer.eSprite.getPosition().x, mPlayer.eSprite.getPosition().y);

		
	}
	
}


void Game::processDestroy(PFITERATOR iterator1)
{
	if ((*iterator1).flag >= Destroy1 && (*iterator1).flag<Destroy2)
		(*iterator1).flag++;

	if ((*iterator1).flag >= Destroy2 && (*iterator1).flag < Destroy3)
	{
		switch ((*iterator1).type)
		{
		case Enemy:
			(*iterator1).eTexture.loadFromFile("resources/image/enemydestroy2.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			enemyAttackSound.play();
			(*iterator1).flag++;
			break;
		case Boss:
			(*iterator1).eTexture.loadFromFile("resources/image/bossdestroy2.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			bossDestroy.play();
			(*iterator1).flag++;
			break;
		case Player:
			(*iterator1).flag++;
			break;
		default:
			break;
		}
		
	}

	if ((*iterator1).flag >= Destroy3 && (*iterator1).flag < Destroy4)
	{
		switch ((*iterator1).type)
		{
		case Enemy:
			(*iterator1).eTexture.loadFromFile("resources/image/enemydestroy3.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			enemyAttackSound.play();
			(*iterator1).flag++;
			break;
		case Boss:
			(*iterator1).eTexture.loadFromFile("resources/image/bossdestroy3.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			bossDestroy.play();
			(*iterator1).flag++;
			break;
		case Player:
			(*iterator1).flag++;
			break;
		default:
			break;
		}
		
	}

	if ((*iterator1).flag == Destroy4)
	{
		switch ((*iterator1).type)
		{
		case Enemy:
			(*iterator1).eTexture.loadFromFile("resources/image/enemydestroy4.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			enemyDestroySound.play();
			break;
		case Boss:
			(*iterator1).eTexture.loadFromFile("resources/image/bossdestroy4.png");
			(*iterator1).eSprite.setTexture((*iterator1).eTexture);
			bossDestroy.play();
			break;
		case Player:
			(*iterator1).flag++;
			printf("%d\n", (*iterator1).flag);
			break;
		default:
			break;
		}
		
	}


	//Player
	if ((*iterator1).flag >Destroy4 && (*iterator1).flag<= Gameover1)
	{
		(*iterator1).eTexture.loadFromFile("resources/image/playerdestroy2.png");
		(*iterator1).eSprite.setTexture((*iterator1).eTexture);
		gameOverSound.play();
		(*iterator1).flag++;
	}

	if ((*iterator1).flag >Gameover1 && (*iterator1).flag<= Gameover2)
	{
		(*iterator1).eTexture.loadFromFile("resources/image/playerdestroy3.png");
		(*iterator1).eSprite.setTexture((*iterator1).eTexture);
		gameOverSound.play();
		(*iterator1).flag++;
	}

	if ((*iterator1).flag >Gameover2 && (*iterator1).flag<= Gameover3)
	{
		(*iterator1).eTexture.loadFromFile("resources/image/playerdestroy4.png");
		(*iterator1).eSprite.setTexture((*iterator1).eTexture);
		gameOverSound.play();
		(*iterator1).flag++;
	}


	if ((*iterator1).flag >Gameover3 && (*iterator1).flag <= Gameover4)
	{
		gameOverSound.play();
		(*iterator1).flag++;
		gameOverFlag = Gameover4;
	}
}


void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}


void Game::render()
{
	mWindow.clear();
	if (gameOverFlag != Gameover4)
	{
		layout();
		
		for (auto i = events.begin(); i != events.end(); i++)
		{
			Aircraft pic = *i;
			mWindow.draw(pic.eSprite);
		}
	}
	else
	{
		entityDestroy();
		mWindow.draw(gameOver);
	}
	mWindow.display();
}


void Game::run()
{
	sf::Clock clock,globalClock;
	while (mWindow.isOpen())
	{
		globalTime = globalClock.restart();
		fireTime = fireClock.restart();
		sf::Time deltaTime = clock.restart();

		processEvents();
		if (gameOverFlag==Alive)
			update(deltaTime);
		enemyup();
		listup();
		render();
	}
}


void Game::showScore()
{
	scoreString = "Score: ";
	if (count < sumScore) count++;
	std::string score = std::to_string(count);
	scoreString.append(score);
	text.setString(scoreString);
}


void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	GetLocalTime(&FireEndTime);
	if (mFire && abs(FireEndTime.wMilliseconds - FireStartTime.wMilliseconds)>100)
	{
		if (bullet.ammo == 0)
		{
			if (bullet.type = JbBullet) jbBullet.ammo = 0;
		}
		else
		{
			fire(mPlayer);
			GetLocalTime(&FireStartTime);
		}
		
	}
	if (mIsMovingUp && mPlayer.eSprite.getPosition().y >= 5.0)
	{
		movement.y -= PlayerSpeed;
	}
	if (mIsMovingDown && mPlayer.eSprite.getPosition().y <= BoundaryHigh - 50)
	{
		movement.y += PlayerSpeed;
	}
	if (mIsMovingLeft && mPlayer.eSprite.getPosition().x >= 5.0)
	{
		movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight && mPlayer.eSprite.getPosition().x <= BoundaryWidth - 50)
	{
		movement.x += PlayerSpeed;
	}
	if (mBullet)
	{
		changeBullet(Bullet);
	}
	if (mJbBullet)
	{
		changeBullet(JbBullet);
	}
	   
	mPlayer.eSprite.move(movement * deltaTime.asSeconds());

}


Game::~Game()
{
}
