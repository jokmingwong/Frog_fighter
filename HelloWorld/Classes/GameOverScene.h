#pragma once

#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include "HelloWorldScene.h"

class GameOverScene :public cocos2d::Scene
{
public:
	GameOverScene(int score);

	virtual bool init();
	
	void menuOkCallback(cocos2d::Ref* pSender);
	static GameOverScene* createWithScore(int score);
private:
	int score;
};