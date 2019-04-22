#ifndef _HELLOWORLD_SCENE_H_
#define _HELLOWORLD_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "SystemHeader.h"
#include "HelpScene.h"

// define a enum structure
typedef enum {
	MenuItemGame,
	MenuItemSetting,
	MenuItemHelp
} ActionType; 


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuItemCallback(cocos2d::Ref* pSender);  
   
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // _HELLOWORLD_SCENE_H_
