#include "stdafx.h"
#include "Aircraft.h"


Aircraft::Aircraft(int flag):
eTexture()
,eSprite()
{
	switch (flag)
	{
	case Enemy:
		type = flag;
		HealthPoint = EnemyHP;
		Armor = EnemyArmor;
		Score = EnemyScore;
		damage = EnemyDamage;
		range = EnemyRange;
		width = EnemyWidth;
		height = EnemyHeight;
		father = Enemy;
		eTexture.loadFromFile("resources/image/enemy.png");
		eSprite.setTexture(eTexture);
		break;
	case Player:
		type = flag;
		eVelocity = PlayerSpeed;
		HealthPoint = PlayerHP;
		Armor = PlayerArmor;
		Score = PlayerScore;
		damage = PlayerDamage;
		range = PlayerRange;
		father = Player;
		eTexture.loadFromFile("resources/image/player.png");
		eSprite.setTexture(eTexture);
		break;
	case Bullet:
		type = flag;
		eVelocity = BulletSpeed;
		HealthPoint = BulletHP;
		Armor = BulletArmor;
		Score = BulletScore;
		damage = BulletDamage;
		range = BulletRange;
		width = BulletWidth;
		height = BulletHight;
		father = Player;
		ammo = MAXNUM;
		eTexture.loadFromFile("resources/image/bullet.png");
		eSprite.setTexture(eTexture);
		break;
	case JbBullet:
		type = flag;
		eVelocity = JbBulletSpeed;
		HealthPoint = JbBulletHP;
		Armor = JbBulletArmor;
		Score = JbBulletScore;
		damage = JbBulletDamage;
		range = JbBulletRange;
		width = JbBulletWidth;
		height = JbBulletHight;
		father = Player;
		ammo = InitialJbBullet;
		eTexture.loadFromFile("resources/image/jbbullet.png");
		eSprite.setTexture(eTexture);
		break;
	case Boss:
		type = flag;
		HealthPoint = BossHP;
		Armor = BossArmor;
		Score = BossScore;
		damage = BossDamage;
		range = BossRange;
		width = BossWidth;
		height = BossHeight;
		father = Boss;
		eTexture.loadFromFile("resources/image/boss.png");
		eSprite.setTexture(eTexture);
		break;
	default:
		break;
	}
	

}


Aircraft::~Aircraft()
{
}
