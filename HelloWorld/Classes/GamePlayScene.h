#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include "Enemy.h"
#include"Bullet.h"
#include"Fighter.h"
#include"GameOverScene.h"
#include"Star.h"
USING_NS_CC; 

#define GameSceneNodeTagStatusBarScore 668
#define GameSceneNodeBatchTagBackground	607
#define GameSceneNodeBatchTagEnemy 10086
#define GameSceneNodeBatchTagBullet 12306
#define GameSceneNodeTagFighter 666
#define GameSceneNodeTagExplosionParticleSystem 110
#define GameSceneBulletVelocity 100
#define GameSceneNodeTagStatusBarFighter 1998
#define GameSceneNodeTagStatusBarLifeNode 715
#define GameSceneNodeBatchTagStar 1069
#define GameSceneNodeTagParticleGalaxy 1402


class GamePlayScene : public cocos2d::Scene
{
private:
	Fighter* fighter;
	Menu* menu;
	int score;
	int scorePlaceholder;
	EventListenerKeyboard *keyboardListener;
	EventListenerPhysicsContact * contactListener;
	Vec2 keepFighterAcce;
	Vector<Enemy*> enemy_vector;
	Vec2 keepFighterVelocity;
	Star* star;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	void initBG();
	void shootBullet(float dt);
	void updateStatusBarFighter();
	void updateStatusBarScore();
	void handleBulletCollidingWithEnemy(Enemy* enemy);
	void fighterCollidingWithEnemy(Enemy* enemy);
	void fighterCollidingWithStar();
	void createStar(float dt);
	void menuResumeCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GamePlayScene);
};