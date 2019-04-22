#pragma once

#include "cocos2d.h"

class Fighter : public cocos2d::Sprite {
	CC_SYNTHESIZE(int, hitPoints, HitPoints);
public:
	void update(float dt);
	static Fighter* createWithSpriteFrameName(const char* spriteFrameName);
};