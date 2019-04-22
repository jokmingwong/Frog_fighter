#include"GameOverScene.h"
USING_NS_CC;

GameOverScene::GameOverScene(int score)
{
	this->score = score;
}

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto label = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 65);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2));
	this->addChild(label);
	// add back button
	auto endButton = MenuItemImage::create("button/back.png", "button/back.png", 
		CC_CALLBACK_1(GameOverScene::menuOkCallback, this));
	endButton->setPosition(label->getPosition()+Vec2(0,-80));
	auto endmn = Menu::create(endButton, NULL);
	endmn->setPosition(Vec2::ZERO);
	this->addChild(endmn, 1);
	return true;
}

GameOverScene* GameOverScene::createWithScore(int score)
{
	GameOverScene* gos = new GameOverScene(score);

	if(gos&&gos->init())
	{
		gos->autorelease();
		return gos;
	}
	CC_SAFE_DELETE(gos);
	return nullptr;
}

void GameOverScene::menuOkCallback(cocos2d::Ref* pSender)
{
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionCrossFade::create(0.3f, sc);
	Director::getInstance()->replaceScene(tsc);
}







