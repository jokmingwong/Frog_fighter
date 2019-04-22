#include "GamePlayScene.h"
#include "SystemHeader.h"
#include "Particle3D/PU/CCPUColorAffector.h"
USING_NS_CC;

Scene* GamePlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	PhysicsWorld* pw = scene->getPhysicsWorld();
	pw->setGravity(Vec2(0, 0));
	auto layer = GamePlayScene::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GamePlayScene::init() {
	if (!Scene::init())return false;
	this->initBG();
	return true;
}

void GamePlayScene::initBG() {
	auto visibelSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// add background
	auto bg = Sprite::createWithSpriteFrameName("BackgroundGame.jpg");
	bg->setPosition(Vec2(origin.x + visibelSize.width / 2, origin.y + visibelSize.height / 2));
	this->addChild(bg, 0, GameSceneNodeBatchTagBackground);
}

void GamePlayScene::onExit() {
	Scene::onExit();
	// stop using shootBulletFromFigher() function
	this->unschedule(schedule_selector(GamePlayScene::shootBullet));
	Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);

	auto nodes = this->getChildren();
	for (const auto&node : nodes) {
		if (node->getTag() != GameSceneNodeBatchTagBackground) {
			this->removeChild(node);
		}
	}
}

void GamePlayScene::onEnter() {
	Scene::onEnter();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// initialize the pause button
	auto pauseSprite = Sprite::createWithSpriteFrameName("pause.png");
	auto pauseMenuItem = MenuItemSprite::create(pauseSprite, pauseSprite, CC_CALLBACK_1(GamePlayScene::menuPauseCallback, this));
	auto pauseMenu = Menu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(Vec2(100, visibleSize.height - pauseSprite->getContentSize().height - 10));
	this->addChild(pauseMenu, 20, 999);

	auto stone = Enemy::createWithEnemyTypes(EnemyTypeStone);
	stone->setVelocity(Vec2(0, -120));
	this->addChild(stone, 0, GameSceneNodeBatchTagEnemy);
	this->enemy_vector.pushBack(stone);

	// add trump
	auto trump = Enemy::createWithEnemyTypes(EnemyTypePlanet);
	trump->setVelocity(Vec2(0, -50));
	this->addChild(trump, 0, GameSceneNodeBatchTagEnemy);
	this->enemy_vector.pushBack(trump);

	// add enemy fighter 1
	auto enemy1 = Enemy::createWithEnemyTypes(EnemyType1);
	enemy1->setVelocity(Vec2(0, -150));
	this->addChild(enemy1, 0, GameSceneNodeBatchTagEnemy);
	this->enemy_vector.pushBack(enemy1);

	// add huge fighter
	auto enemyHuge = Enemy::createWithEnemyTypes(EnemyType2);
	enemyHuge->setVelocity(Vec2(0, -60));
	this->addChild(enemyHuge, 0, GameSceneNodeBatchTagEnemy);
	this->enemy_vector.pushBack(enemyHuge);
	

	// our fighter ^_^ 
	this->fighter = Fighter::createWithSpriteFrameName("frog.png");
	this->fighter->setHitPoints(5);
	this->fighter->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));
	this->fighter->getPhysicsBody()->setVelocity(Vec2(0, 0));
	this->addChild(fighter, 10, GameSceneNodeTagFighter);

	// control the star
	this->scheduleOnce(schedule_selector(GamePlayScene::createStar),20.0f);

	// sign up the listener and add a lambda funtion
	this->keyboardListener = EventListenerKeyboard::create();
	this->keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event) {
		// the move distance
		auto target = event->getCurrentTarget();

		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			target->getPhysicsBody()->getVelocity().y < 0 ?
				target->getPhysicsBody()->setVelocity(Vec2(0, 0)) :
				target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(0, 200));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			target->getPhysicsBody()->getVelocity().y > 0 ?
				target->getPhysicsBody()->setVelocity(Vec2(0, 0)) :
				target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity()
					+ Vec2(0, -200));
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			target->getPhysicsBody()->getVelocity().x > 0 ?
				target->getPhysicsBody()->setVelocity(Vec2(0, 0)) :
				target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(-200, 0));
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			target->getPhysicsBody()->getVelocity().x < 0 ?
				target->getPhysicsBody()->setVelocity(Vec2(0, 0)) :
				target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(200, 0));
			break;
		default:
			break;
		}
	};
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this->fighter);

	// Listen the contact
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeB()->getBody()->getNode();
		// fighter contact with the plane
		Node* enemy1 = nullptr;
		if (spriteA->getTag() == GameSceneNodeTagFighter &&
			spriteB->getTag() == GameSceneNodeBatchTagEnemy)
		{
			enemy1 = spriteB;
		}
		if (spriteA->getTag() == GameSceneNodeBatchTagEnemy &&
			spriteB->getTag() == GameSceneNodeTagFighter)
		{
			enemy1 = spriteA;
		}
		if (enemy1 != nullptr)
		{
			this->fighterCollidingWithEnemy((Enemy*)enemy1);
			return false;
		}

		Node* enemy2 = nullptr;
		if (spriteA->getTag() == GameSceneNodeBatchTagBullet &&
			spriteB->getTag() == GameSceneNodeBatchTagEnemy)
		{
			if (!spriteA->isVisible())return false;
			spriteA->setVisible(false);
			enemy2 = spriteB;
		}
		if (spriteA->getTag() == GameSceneNodeBatchTagEnemy
			&& spriteB->getTag() == GameSceneNodeBatchTagBullet)
		{
			if (!spriteB->isVisible())return false;
			spriteB->setVisible(false);
			enemy2 = spriteA;
		}
		// contact happen
		if (enemy2 != nullptr)
		{
			this->handleBulletCollidingWithEnemy((Enemy*)enemy2);
			return false;
		}

		Node* award = nullptr;
		if (spriteA->getTag() == GameSceneNodeTagFighter &&
			spriteB->getTag() == GameSceneNodeBatchTagStar)
		{
			award = spriteB;
		}
		if (spriteA->getTag() == GameSceneNodeBatchTagStar &&
			spriteB->getTag() == GameSceneNodeTagFighter)
		{
			award = spriteA;
		}
		if (award != nullptr)
		{
			this->fighterCollidingWithStar();
			return false;
		}
		return false;

	};
	EventDispatcher* eventsDiapatcher2 = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	// eventsDispatcher2 end

	this->schedule(schedule_selector(GamePlayScene::shootBullet), 0.2f);
	// set score
	this->score = 0;
	this->scorePlaceholder = 0;
	// show life
	this->updateStatusBarFighter();
	// show score
	this->updateStatusBarScore();
}



void GamePlayScene::handleBulletCollidingWithEnemy(Enemy* enemy)
{
	enemy->setHitPoints(enemy->getHitPoints() - 1);
	if (enemy->getHitPoints() <= 0)
	{
		Node* node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
		if (node)
		{
			this->removeChild(node);
		}
		ParticleSystem* ep = ParticleExplosion::create();
		ep->setPosition(enemy->getPosition());
		ep->setScale(0.2f);
		ep->setColor(Color3B::ORANGE);
		this->addChild(ep, 2, GameSceneNodeTagExplosionParticleSystem);

		switch (enemy->getEnemyType())
		{
		case EnemyTypeStone:
			score += EnemyStone_score;
			scorePlaceholder += EnemyStone_score;
			break;
		case EnemyType1:
			score += Enemy1_score;
			scorePlaceholder += Enemy1_score;
			break;

		case EnemyType2:
			score += Enemy2_score;
			scorePlaceholder += Enemy2_score;
			break;
		case EnemyTypePlanet:
			score += EnemyTrump_score;
			scorePlaceholder += EnemyTrump_score;
			break;
		}

		// get the life when get 1000 scores
		if (scorePlaceholder >= 1000)
		{
			fighter->setHitPoints(fighter->getHitPoints() + 1);
			// increse difficulty
			for (auto it = enemy_vector.begin(); it != enemy_vector.end(); ++it) {
				(*it)->setVelocity((*it)->getVelocity() + Vec2(0, -25));
			}
			this->updateStatusBarFighter();
			scorePlaceholder -= 1000;
		}
		this->updateStatusBarScore();

		// make the enemy disappear
		enemy->setVisible(false);
		enemy->spawn();
	}
}

void GamePlayScene::fighterCollidingWithStar()
{

	Node* node = this->getChildByTag(GameSceneNodeTagParticleGalaxy);
	if (node)
	{
		this->removeChild(node);
	}
	ParticleSystem*eg = ParticleGalaxy::create();
	eg->setScale(0.1f);
	eg->setPosition(star->getPosition());
	this->addChild(eg, 10, GameSceneNodeTagParticleGalaxy);
	this->score += 100;
	this->scorePlaceholder += 100;
	// make the enemy disappear
	star->setVisible(false);
	this->updateStatusBarScore();
}


void GamePlayScene::fighterCollidingWithEnemy(Enemy* enemy)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Node* node = this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
	if (node)
	{
		this->removeChild(node);
	}
	ParticleSystem*ep = ParticleExplosion::create();
	ep->setScale(0.2f);
	ep->setPosition(enemy->getPosition());
	ep->setColor(Color3B::ORANGE);
	this->addChild(ep, 2, GameSceneNodeTagExplosionParticleSystem);

	// make the enemy disappear
	enemy->setVisible(false);
	enemy->spawn();

	// make the player disappear
	fighter->setHitPoints(fighter->getHitPoints() - 1);
	this->updateStatusBarFighter();
	if (fighter->getHitPoints() <= 0)
	{
		auto gol = GameOverScene::createWithScore(score);
		auto gos = GameOverScene::create();
		gos->addChild(gol);

		auto tsc = TransitionCrossFade::create(1.0f, gos);
		Director::getInstance()->pushScene(tsc);
	}
	else
	{
		fighter->setPosition(Vec2(visibleSize.width / 2,
			visibleSize.height / 2 - fighter->getContentSize().height));
		auto ac1 = Show::create();
		auto ac2 = FadeIn::create(1.0f);
		auto seq = Sequence::create(ac1, ac2, NULL);
		fighter->runAction(seq);
	}
}


void GamePlayScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("GamePlayer onEnterTransitionDidFinish");
	UserDefault*defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music1, true);
	}
}

void GamePlayScene::menuPauseCallback(cocos2d::Ref* pSender)
{
	log("Menu Pause Callback");
	this->pause();

	for (const auto& node : this->getChildren())
	{
		node->pause();
	}
	fighter->getPhysicsBody()->setVelocity(Vec2(0, 0));
	star->getPhysicsBody()->setVelocity(Vec2(0, 0));
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// back menu
	auto endButton = Sprite::createWithSpriteFrameName("back.png");
	auto endMenuItem = MenuItemSprite::create(
		endButton, endButton, CC_CALLBACK_1(GamePlayScene::menuBackCallback, this));

	// resume button
	auto resumeButton = Sprite::createWithSpriteFrameName("resume.png");
	auto resumeMenuItem = MenuItemSprite::create(
		resumeButton, resumeButton, CC_CALLBACK_1(GamePlayScene::menuResumeCallback, this));

	menu = Menu::create(endMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVerticallyWithPadding(16);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	addChild(this->menu, 20, 1000);
}

void GamePlayScene::menuResumeCallback(cocos2d::Ref* pSender)
{
	this->resume();
	star->getPhysicsBody()->setVelocity(Vec2(0, -300));
	for (const auto&node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);
}


void GamePlayScene::menuBackCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void GamePlayScene::menuOkCallback(cocos2d::Ref* pSender)
{

}

void GamePlayScene::createStar(float dt) {
	if (fighter&&fighter->isVisible())
	{
		star = Star::createWithSpriteFrameName("star.png");
		star->getPhysicsBody()->setVelocity(Vec2(0, -300));
		this->addChild(star, 10, GameSceneNodeBatchTagStar);
	}
}

void GamePlayScene::shootBullet(float dt) {
	if (fighter&&fighter->isVisible())
	{
		Bullet* bullet = Bullet::createWithSpriteFrameName("bullet.png");
		bullet->setVelocity(Vec2(0, GameSceneBulletVelocity));
		this->addChild(bullet, 0, GameSceneNodeBatchTagBullet);
		bullet->shootBulletFromFighter(fighter);
	}
}

void GamePlayScene::updateStatusBarFighter() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Node* n1 = this->getChildByTag(GameSceneNodeTagStatusBarFighter);
	if (n1)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarFighter);
	}
	Sprite* fg = Sprite::createWithSpriteFrameName("life.png");
	fg->setPosition(Vec2(visibleSize.width * 3 / 4,
		visibleSize.height - fg->getContentSize().height - 10));
	this->addChild(fg, 20, GameSceneNodeTagStatusBarFighter);

	Node* n2 = this->getChildByTag(GameSceneNodeTagStatusBarLifeNode);
	if (n2)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarLifeNode);
	}
	if (this->fighter->getHitPoints() < 0)
	{
		this->fighter->setHitPoints(0);
	}

	__String* life = __String::createWithFormat("x %d", this->fighter->getHitPoints());
	auto lblLife = Label::createWithTTF(life->getCString(), "fonts/Marker Felt.ttf", 35);
	lblLife->setPosition(fg->getPosition() + Vec2(100, 0));
	this->addChild(lblLife, 20, GameSceneNodeTagStatusBarLifeNode);

}

void GamePlayScene::updateStatusBarScore() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Node* n = this->getChildByTag(GameSceneNodeTagStatusBarScore);
	if (n)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarScore);
	}

	if (this->score < 0)
	{
		this->score = 0;
	}

	__String* sco_string = __String::createWithFormat("%d", this->score);
	auto lblscore = Label::createWithTTF(sco_string->getCString(), "fonts/Marker Felt.ttf", 35);
	lblscore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - lblscore->getContentSize().height - 10));
	this->addChild(lblscore, 20, GameSceneNodeTagStatusBarScore);

}

