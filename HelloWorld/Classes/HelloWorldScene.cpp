// include header file
#include "HelloWorldScene.h"
#include "GamePlayScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*
	// add background music
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/sunnyday.mp3", true);
	*/
	//add a background
	Sprite* bg = Sprite::createWithSpriteFrameName("Background2.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	// add menu code
	/*
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(78);
	MenuItemFont* item1 = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));
	// add the second menu
	MenuItemFont *item2 = MenuItemFont::create("Help", CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	//add the third menu
	MenuItemFont *item3 = MenuItemFont::create("Setting", CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
	// move the menu to object
	Menu *mn = Menu::create(item1, item2, item3, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
	*/
	// add 3 labelS
	auto label1 = Label::createWithTTF("GAME", "fonts/Marker Felt.ttf", 54);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2 + 2 * label1->getContentSize().height));
	this->addChild(label1);

	auto label2 = Label::createWithTTF("SETTING", "fonts/Marker Felt.ttf", 54);
	label2->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2));
	this->addChild(label2);

	auto label3 = Label::createWithTTF("HELP", "fonts/Marker Felt.ttf", 54);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2 - 2 * label1->getContentSize().height));
	this->addChild(label3);
	// game menu
	auto gameSpriteNormal = Sprite::createWithSpriteFrameName("game_button.png");
	auto gameSpriteSelected = Sprite::createWithSpriteFrameName("game_button_on.png");
	auto gameMenuItem = MenuItemSprite::create(
		gameSpriteNormal, gameSpriteSelected, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	gameMenuItem->setTag(ActionType::MenuItemGame);

	// setting menu
	auto settingSpriteNormal = Sprite::createWithSpriteFrameName("setting_button.png");
	auto settingSpriteSelected = Sprite::createWithSpriteFrameName("setting_button_on.png");
	auto settingMenuItem = MenuItemSprite::create(
		settingSpriteNormal, settingSpriteSelected, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	settingMenuItem->setTag(ActionType::MenuItemSetting);

	// Help menu
	auto helpSpriteNormal = Sprite::createWithSpriteFrameName("help_button.png");
	auto helpSpriteSelected = Sprite::createWithSpriteFrameName("help_button_on.png");
	auto helpMenuItem = MenuItemSprite::create(
		helpSpriteNormal, helpSpriteSelected, CC_CALLBACK_1(HelloWorld::menuItemCallback, this));
	helpMenuItem->setTag(ActionType::MenuItemHelp);

	// combine menu
	auto mu = Menu::create(gameMenuItem, settingMenuItem, helpMenuItem, NULL);
	mu->setPosition(visibleSize.width*2/ 3, visibleSize.height/ 2);
	mu->alignItemsVerticallyWithPadding(27);
	addChild(mu);
	
	// bg music
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music1, true);

	return true;
}

void HelloWorld::menuItemCallback(Ref*pSender) {
	Scene* tsc = nullptr;
	MenuItem *item = (MenuItem*)pSender;
	log("MenuItem Tag = %d,", item->getTag());
	switch (item->getTag())
	{
	case ActionType::MenuItemGame:
		tsc = TransitionCrossFade::create(1.0f, GamePlayScene::createScene());
		log("Press button 1");
		break;
	case ActionType::MenuItemHelp:
		tsc = TransitionCrossFade::create(0.5f, Help::createScene());
		log("Press button 2");
		break;
	case ActionType::MenuItemSetting:
		tsc = TransitionCrossFade::create(0.5f, Setting::createScene());
		log("Press button 3");
		break;
	default:
		break;
	}
	if (tsc) {
		Director::getInstance()->pushScene(tsc);
	}
}


void HelloWorld::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Stop updating
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
