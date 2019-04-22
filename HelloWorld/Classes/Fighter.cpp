#include "Fighter.h"
USING_NS_CC;

void Fighter::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	auto halfHeight = this->getContentSize().height / 2;
	auto halfWidth = this->getContentSize().width / 2;
	if (this->getPosition().y < halfHeight) {
		this->setPosition(this->getPosition().x, halfHeight);
		this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 0));
	}
	else if (this->getPosition().y > visibleSize.height-halfHeight) {
		this->setPosition(this->getPosition().x, visibleSize.height - halfHeight);
		this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 0));
	}
	if (this->getPosition().x < halfWidth) {
		this->setPosition(halfWidth, this->getPosition().y);
		this->getPhysicsBody()->setVelocity(Vec2(0, getPhysicsBody()->getVelocity().y));
	}
	else if (this->getPosition().x > visibleSize.width-halfWidth) {
		this->setPosition(visibleSize.width - halfWidth, this->getPosition().y);
		this->getPhysicsBody()->setVelocity(Vec2(0, getPhysicsBody()->getVelocity().y));
	}
	
}


Fighter* Fighter::createWithSpriteFrameName(const char* spriteFrameName) {
	Fighter* fighter = new Fighter();
	if (fighter&&fighter->initWithSpriteFrameName(spriteFrameName)) {
		fighter->autorelease();
		//put under fighter
		ParticleSystem* ps = ParticleFire::create();
		ps->setPosition(Vec2(fighter->getContentSize().width / 2, 0));
		ps->setRotation(180.0f);
		ps->setScale(0.2f);
		fighter->addChild(ps);

		Vec2 verts[] = {
			Vec2(-48,32),
			Vec2(48,32),
			Vec2(48,-32),
			Vec2(-48,-32)
		};

		auto body = PhysicsBody::createPolygon(verts, 4);
		// set bitmask
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		fighter->setPhysicsBody(body);
		return fighter;
	}

	CC_SAFE_DELETE(fighter);
	return NULL;
}