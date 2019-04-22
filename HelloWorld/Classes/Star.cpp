#include"Star.h"
USING_NS_CC;

Star* Star::createWithSpriteFrameName(const char* spriteFrameName) {
	Star* star = new Star();
	if (star&&star->initWithSpriteFrameName(spriteFrameName)) {
		star->autorelease();

	
		auto body = PhysicsBody::createBox(star->getContentSize());

		//set bitmask
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		// set star
		star->setPhysicsBody(body);
		star->setVisible(false);
		star->spawn();
		star->unscheduleUpdate();
		star->scheduleUpdate();

		return star;
	}
	CC_SAFE_DELETE(star);
	return nullptr;
}

void Star::update(float dt) {
	// judge the bullet is outside the screen
	if (this->getPosition().y <=0 ) {
		this->spawn();
	}
}

void Star::spawn() {
	auto screenSize = Director::getInstance()->getVisibleSize();
	float yPos = screenSize.height + this->getContentSize().height / 2;
	float xPos = CCRANDOM_0_1()*(screenSize.width - this->getContentSize().width) +
		this->getContentSize().width / 2;
	this->setPosition(Vec2(xPos, yPos));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->setVisible(true);
}