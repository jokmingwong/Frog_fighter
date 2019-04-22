#pragma once

#include "cocos2d.h"

class Star : public cocos2d::Sprite {
public:
	static Star* createWithSpriteFrameName(const char* spriteFrameName);

	void update(float dt);
	void spawn();
};