#include"HelpScene.h"


USING_NS_CC;

Scene* Help::createScene()
{
	return Help::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Help::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibelSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// background
	Sprite* bg = Sprite::createWithSpriteFrameName("Background2.jpg");
	bg->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height / 2));
	this->addChild(bg);
	// add text Label
	auto txt = Label::createWithTTF("e-mail:", "fonts/Marker Felt.ttf", 54);
	txt->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height * 2 / 3));
	this->addChild(txt);
	auto txt2 = Label::createWithTTF("jokmingwong@gmail.com", "fonts/Marker Felt.ttf", 42);
	txt2->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height* 1.5 / 3));
	this->addChild(txt2);
	auto txt3 = Label::createWithTTF("wechat:", "fonts/Marker Felt.ttf", 54);
	txt3->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height / 3));
	this->addChild(txt3);
	auto txt4 = Label::createWithTTF("mickycorn", "fonts/Marker Felt.ttf", 42);
	txt4->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height / 6));
	this->addChild(txt4);
	// end button
	// end button
	auto endButton = Sprite::createWithSpriteFrameName("back.png");
	auto endOnButton = Sprite::createWithSpriteFrameName("back_on.png");
	auto endButtonMenu = MenuItemSprite::create(endButton, endOnButton, CC_CALLBACK_1(Help::menuOkCallback, this));
	auto mu = Menu::create(endButtonMenu, NULL);
	mu->setPosition(Vec2(origin.x + visibelSize.width - endButton->getContentSize().width,
		origin.y + endButton->getContentSize().height * 2));
	addChild(mu);

	return true;
}

void Help::menuOkCallback(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}