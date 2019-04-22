#pragma once

#include "cocos2d.h"
#include "Fighter.h"

class Bullet :public cocos2d::Sprite {
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);

public:
	void shootBulletFromFighter(Fighter* fighter); // send bullet from fighter

	virtual void update(float dt);
	static Bullet* createWithSpriteFrameName(const char* spriteFrameName);
};