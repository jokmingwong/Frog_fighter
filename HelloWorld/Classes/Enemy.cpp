#include "Enemy.h"

USING_NS_CC;
// initialization
Enemy::Enemy(EnemyTypes e) {
	this->enemyType = e;
	this->initialHitPoints = 1;
	this->velocity = Vec2::ZERO;
}

Enemy* Enemy::createWithEnemyTypes(EnemyTypes enemyType)
{
	Enemy* enemy = new Enemy(enemyType);

	const char* enemyFrameName = Enemy_Stone;

	switch (enemyType)
	{
	case EnemyTypeStone:
		enemyFrameName = Enemy_Stone;
		enemy->initialHitPoints = 10;
		break;
	case EnemyType1:
		enemyFrameName = Enemy_1;
		enemy->initialHitPoints = 10;
		break;
	case EnemyType2:
		enemyFrameName = Enemy_2;
		enemy->initialHitPoints = 25;
		break;
	case EnemyTypePlanet:
		enemyFrameName = Enemy_Planet;
		enemy->initialHitPoints = 30;
		break;
	}
	if (enemy && enemy->initWithSpriteFrameName(enemyFrameName)) {
		enemy->autorelease(); // put it into RAM
		auto body = PhysicsBody::create();
		if (enemyType == EnemyTypeStone || enemyType == EnemyTypePlanet) {
			body->addShape(PhysicsShapeCircle::create(enemy->getContentSize().width / 2));
		}
		else if (enemyType == EnemyType1) {
			Vec2 verts[] = {
				Vec2(0,64),
				Vec2(32,32),
				Vec2(34,21),
				Vec2(0,-58),
				Vec2(-34,21),
				Vec2(-32,32)
			};
			body->addShape(PhysicsShapePolygon::create(verts, 6));
		}
		else if (enemyType == EnemyType2) {
			Vec2 verts[] = {
				Vec2(16,240),
				Vec2(32,208),
				Vec2(112,0),
				Vec2(48,-32),
				Vec2(34,-128),
				Vec2(-34,-128),
				Vec2(-48,-32),
				Vec2(-112,0),
				Vec2(-32,208),
				Vec2(-16,240)
			};
			body->addShape(PhysicsShapePolygon::create(verts, 10));
		}

		//set bitmask
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		// set enemy
		enemy->setPhysicsBody(body);
		enemy->setVisible(false);
		enemy->spawn();
		enemy->unscheduleUpdate();
		enemy->scheduleUpdate();

		return enemy;

	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::update(float dt) {
	// set planet rotate
	switch (enemyType) {
	case EnemyTypeStone:
		this->setRotation(this->getRotation() - 0.5);
		break;
	case EnemyTypePlanet:
		this->setRotation(this->getRotation() + 1);
		break;
	}
	Vec2 moveLen = velocity * dt;
	this->setPosition(this->getPosition() + moveLen);

	if (this->getPosition().y + this->getContentSize().height / 2 < 0) {
		this->spawn();
	}
}

void Enemy::spawn() {
	auto screenSize = Director::getInstance()->getVisibleSize();
	float yPos = screenSize.height + this->getContentSize().height / 2;
	float xPos = CCRANDOM_0_1()*(screenSize.width - this->getContentSize().width) +
		this->getContentSize().width / 2;

	this->setPosition(Vec2(xPos, yPos));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	hitPoints = initialHitPoints;
	this->setVisible(true);
}
