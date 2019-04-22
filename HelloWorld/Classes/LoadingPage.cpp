#include"LoadingPage.h"


USING_NS_CC;
using namespace CocosDenshion;

Scene* LoadingPage::createScene()
{
	return LoadingPage::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool LoadingPage::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add plist to cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");
	//add a background
	Sprite* bg = Sprite::create("Background2.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	auto sprite = Sprite::createWithSpriteFrameName("loading3.png");
	this->addChild(sprite);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	// add animation
	Animation* animation = Animation::create();
	for (int i = 1; i <= 3; i++)
	{
		__String *frameName = __String::createWithFormat("loading%d.png", i);
		log("frameName = %s", frameName->getCString());
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}

	animation->setDelayPerUnit(0.5f);           //设置两个帧播放时间
	animation->setRestoreOriginalFrame(true);    //动画执行后还原初始状态
	Animate* action = Animate::create(animation);
	sprite->runAction(RepeatForever::create(action));
	
	// loading texture
	m_nNumberOfLoaded = 0;
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
		CC_CALLBACK_1(LoadingPage::LoadingTextureCallback, this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/basic_texture.png",
		CC_CALLBACK_1(LoadingPage::LoadingTextureCallback, this));
	_loadingAudioThread = new std::thread(&LoadingPage::loadingAudio, this);
	return true;
}

void LoadingPage::loadingAudio()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music1);
}




void LoadingPage::LoadingTextureCallback(Texture2D* texture)
{
	switch (m_nNumberOfLoaded++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist", texture);
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/basic_texture.plist", texture);
		this->schedule(schedule_selector(LoadingPage::delayCall), 1, 1, 2);
	}
}

void LoadingPage::delayCall(float dt)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}

void LoadingPage::onExit()
{
	Scene::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading_texture.plist");
	Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading_texture.png");
	this->unschedule(schedule_selector(LoadingPage::delayCall));
}

void LoadingPage::menuCloseCallback(Ref* pSender)
{
	//Stop updating
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}