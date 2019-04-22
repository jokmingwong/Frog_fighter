#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender); 

	// implement the "static create()" method manually
	CREATE_FUNC(Setting);
};