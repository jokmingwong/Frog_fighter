#include"Bullet.h"
USING_NS_CC;

Bullet* Bullet::createWithSpriteFrameName(const char* spriteFrameName) {
	Bullet* bullet = new Bullet();
	if (bullet&&bullet->initWithSpriteFrameName(spriteFrameName)) {
		bullet->autorelease();
		bullet->setVisible(false);

		auto body = PhysicsBody::createBox(bullet->getContentSize());
		// set bitmask
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		bullet->setPhysicsBody(body);

		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::shootBulletFromFighter(Fighter* fighter) {
	this->setPosition(fighter->getPosition() + Vec2(0, fighter->getContentSize().height / 2));
	this->setVisible(true);
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void Bullet::update(float dt) {
	auto screenSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(this->getPosition() + velocity * dt));
	// judge the bullet is outside the screen
	if (this->getPosition().y > screenSize.height) {
		this->setVisible(false);
		this->unscheduleUpdate();
		// move the bullet
		this->removeFromParent();
	}
}