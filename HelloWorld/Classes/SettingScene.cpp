#include"SettingScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene()
{
	return Setting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Setting::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibelSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* bg = Sprite::createWithSpriteFrameName("Background2.jpg");
	bg->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height / 2));
	this->addChild(bg);
	//add a label
	auto label = Label::createWithTTF("Background Music:", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(origin.x + visibelSize.width / 3, origin.y + visibelSize.height / 2));
	this->addChild(label);
	// add sound effect button
	auto musicOnSprite = Sprite::createWithSpriteFrameName("on.png");
	auto musicOffSprite = Sprite::createWithSpriteFrameName("off.png");
	auto musicOnMenuItem = MenuItemSprite::create(musicOnSprite,NULL);
	auto musicOffMenuItem = MenuItemSprite::create(musicOffSprite,NULL);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
		musicOffMenuItem, musicOnMenuItem, NULL); 
	musicToggleMenuItem->setPosition(Vec2(origin.x + visibelSize.width - musicToggleMenuItem->getContentSize().width,
		origin.y + visibelSize.height / 2));
	Menu* mn = Menu::create(musicToggleMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	// end button
	auto endButton = Sprite::createWithSpriteFrameName("back.png");
	auto endOnButton = Sprite::createWithSpriteFrameName("back_on.png");
	auto endButtonMenu = MenuItemSprite::create(endButton, endOnButton, CC_CALLBACK_1(Setting::menuOkCallback, this));
	auto mu = Menu::create(endButtonMenu, NULL);
	mu->setPosition(Vec2(origin.x + visibelSize.width - endButton->getContentSize().width,
		origin.y + endButton->getContentSize().height * 2));
	addChild(mu);
	return true;
}


void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Setting::menuMusicToggleCallback(Ref* pSender) 
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	if (musicToggleMenuItem->getSelectedIndex() == 1) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/sunnyday.mp3");
	}
	else {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/sunnyday.mp3");
	}
}

void Setting::menuCloseCallback(Ref* pSender)
{
	//Stop updating
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}