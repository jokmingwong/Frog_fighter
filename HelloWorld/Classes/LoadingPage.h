#pragma once

#include"cocos2d.h" 
#include"SimpleAudioEngine.h"
#include "HelloWorldScene.h"

class LoadingPage : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	void loadingAudio();
	virtual bool init();
	virtual void onExit();
	void LoadingTextureCallback(cocos2d::Texture2D* texture);
	void menuCloseCallback(Ref* pSender);
	void delayCall(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(LoadingPage);
private:
	std::thread* _loadingAudioThread;
	unsigned int m_nNumberOfLoaded;
}; 
