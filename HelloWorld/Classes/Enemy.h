#pragma once
#include "cocos2d.h"

#define Enemy_Stone "stone.png"
#define Enemy_1 "Enemy1.png"
#define Enemy_2 "Enemy2.png"
#define Enemy_Planet "Trump.png"
#define EnemyStone_score 20
#define EnemyTrump_score 30
#define Enemy1_score 60
#define Enemy2_score 60

// define 4 enemy
typedef enum
{
	EnemyTypeStone = 0, //stone
	EnemyType1, //plane1
	EnemyType2, //plane2
	EnemyTypePlanet //trump
}EnemyTypes;

class Enemy : public cocos2d::Sprite {
	CC_SYNTHESIZE(EnemyTypes, enemyType, EnemyType);// enemy type
	CC_SYNTHESIZE(int, initialHitPoints, InitialHitPoints);// the initial point of enemy 
	CC_SYNTHESIZE(int, hitPoints, HitPoints);// my point
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);// velocity

public:
	Enemy(EnemyTypes enemyType);// contruct function
	void spawn(); //make enemy funtion
	virtual void update(float dt);// circulation update
	static Enemy* createWithEnemyTypes(EnemyTypes enemyType);// static creation
};