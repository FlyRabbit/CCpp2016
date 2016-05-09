// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once



#include "targetver.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <Windows.h>
#include <ctime>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>


//typedef std::list<>


#define Enemy 0
#define Player 1
#define Bullet 2
#define JbBullet 3
#define Boom 4
#define Boss 5
#define ExtraRate 1.5
#define Alive 1
#define Destroy1 99999985
#define Destroy2 99999990
#define Destroy3 99999995
#define Destroy4 99999999
#define Gameover1 100000135
#define Gameover2 100000205
#define Gameover3 100000275
#define Gameover4 100000365
#define ArmorRate 4

// TODO:  在此处引用程序需要的其他头文件
#define PlayerSpeed 300.f
#define PlayerHP 1000
#define PlayerScore 0
#define PlayerArmor 5
#define PlayerDamage 300
#define PlayerRange 0



//Enemy
#define EnemySpeed 100.f
#define EnemyHP 300
#define EnemyScore 50
#define EnemyArmor 0
#define EnemyDamage 200;
#define EnemyRange 0

//bullet
#define BulletSpeed 0-400.f
#define BulletHP 1
#define BulletScore 0
#define BulletArmor 0
#define BulletDamage 50
#define BulletRange 0

//jbbullet
#define JbBulletSpeed 0-400.f
#define JbBulletHP 1
#define JbBulletScore 0
#define JbBulletArmor 0
#define JbBulletDamage 100
#define JbBulletRange 0


//boss
#define BossSpeed 10.f
#define BossHP 5000
#define BossScore 1000
#define BossArmor 8
#define BossDamage 1000;
#define BossRange 0

//limit boundary
#define BoundaryHigh 800
#define BoundaryWidth 480
#define JbBulletWidth 4
#define JbBulletHight 8
#define BulletWidth 4
#define BulletHight 8
#define EnemyWidth 16
#define EnemyHeight 20
#define BossWidth 40
#define BossHeight 57
#define BulletPositionX 190.f
#define BulletPositionY 765.f
#define JbBulletPositionX 240.f
#define JbBulletPositionY 765.f

//timr
#define Level1Time 490
#define Level2Time 440
#define Level3Time 390


//other
#define PFITERATOR std::_List_iterator<std::_List_val<std::_List_simple_types<Aircraft>>>
#define NoFather 9999
#define MAXNUM 999999999
#define InitialJbBullet 400
#define BackGroundSpeed 50.f