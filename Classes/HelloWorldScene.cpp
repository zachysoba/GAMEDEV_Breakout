#include "HelloWorldScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

	Vect gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();	

	this->labelScore = Label::createWithSystemFont("Score: 0", "Arial", 25);
	this->labelScore->setPosition(Point(visibleSize.width - labelScore->getContentSize().width, visibleSize.height - labelScore->getContentSize().height));
	this->addChild(labelScore);

	score = 0;
    
	border = Sprite::create();
	auto borderBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	borderBody->getShape(0)->setRestitution(1.0f); 
	borderBody->getShape(0)->setFriction(0.0f);
	borderBody->getShape(0)->setDensity(10.0f);
	border->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2)); 
	border->setPhysicsBody(borderBody); 
	borderBody->setContactTestBitmask(0x000001);
	this->addChild(border);
	border->setTag(0);
	

	ball = Sprite::create("ball.png", Rect(0, 0, 18, 18));
	ball->setPosition(100, 100);
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.);
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setDensity(1.0f);
	ballBody->setGravityEnable(false); 
	Vect force = Vect(101000.0f, 101000.0f); 
	ballBody->applyImpulse(force);
	ball->setPhysicsBody(ballBody); 
	ballBody->setContactTestBitmask(0x000001);
	ball->setTag(1);
	this->addChild(ball);

	paddle = Sprite::create("paddle.png");
	auto paddleBody = PhysicsBody::createBox(paddle->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	paddleBody->getShape(0)->setRestitution(1.0f);
	paddleBody->getShape(0)->setFriction(0.0f);
	paddleBody->getShape(0)->setDensity(10.0f); 
	paddleBody->setGravityEnable(false); 
	paddleBody->setDynamic(false); 
	paddle->setPosition(visibleSize.width / 2, 50); 
	paddle->setPhysicsBody(paddleBody);
	paddleBody->setContactTestBitmask(0x000001);

	ball->setTag(2);
	this->addChild(paddle);
	
	for (int i = 0; i < 7; i++) {

		static int padding = 52;

		auto brick = Sprite::create("brick.png");
		auto brickBody = PhysicsBody::createBox(brick->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		brickBody->getShape(0)->setDensity(10.0f);
		brickBody->getShape(0)->setFriction(0.0f);
		brickBody->getShape(0)->setRestitution(1.f);
		brickBody->setDynamic(false);
		int xOffset = padding + brick->getContentSize().width / 2 + ((brick->getContentSize().width + padding)*i);
		brick->setPosition(xOffset, 400);
			
		brickBody->setContactTestBitmask(0x000001);
		brick->setPhysicsBody(brickBody);
		brick->setTag(3);
		this->addChild(brick);
	}
	
	for (int i = 0; i < 7; i++) {

		static int padding = 52;

		auto brick = Sprite::create("brick.png");
		auto brickBody = PhysicsBody::createBox(brick->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		brickBody->getShape(0)->setDensity(10.0f);
		brickBody->getShape(0)->setFriction(0.0f);
		brickBody->getShape(0)->setRestitution(1.f);
		brickBody->setDynamic(false);
		int xOffset = padding + brick->getContentSize().width / 2 + ((brick->getContentSize().width + padding)*i);
		brick->setPosition(xOffset, 450);

		brickBody->setContactTestBitmask(0x000001);
		brick->setPhysicsBody(brickBody);
		brick->setTag(3);
		this->addChild(brick);
	}

	for (int i = 0; i < 7; i++) {

		static int padding = 52;

		auto brick = Sprite::create("brick.png");
		auto brickBody = PhysicsBody::createBox(brick->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		brickBody->getShape(0)->setDensity(10.0f);
		brickBody->getShape(0)->setFriction(0.0f);
		brickBody->getShape(0)->setRestitution(1.f);
		brickBody->setDynamic(false);
		int xOffset = padding + brick->getContentSize().width / 2 + ((brick->getContentSize().width + padding)*i);
		brick->setPosition(xOffset, 500);

		brickBody->setContactTestBitmask(0x000001);
		brick->setPhysicsBody(brickBody);
		brick->setTag(3);
		this->addChild(brick);
	}
		
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);    
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	
	this->schedule(schedule_selector(HelloWorld::tick),0);
	
    return true;
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{		
return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{

}

void HelloWorld::tick(float dt)
{	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	bool isWin = true;
	Vector<PhysicsBody*> bodies = m_world->getAllBodies();
	for each(PhysicsBody* body in bodies)
	{
		if (body->getNode()->getTag() == 3)
		{
			isWin = false;
		}
	}
	if (isWin == true)
	{
		auto gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Won!");

		Director::getInstance()->replaceScene(gameOverScene);
	}
	
}


void HelloWorld::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();
	paddle->setPositionX(touchLocation.x);	
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	if (tagA == 3)
	{
		this->removeChild(spriteA,true);

		score += 10;
		//if (score>highScore) highScore = score;
		this->removeChild(labelScore);
		char scoreCount[20] = { 0 };
		sprintf(scoreCount, "Score: %d", score);
		labelScore = Label::createWithSystemFont(scoreCount, "Arial", 25);
		labelScore->setPosition(Point(visibleSize.width - labelScore->getContentSize().width, visibleSize.height - labelScore->getContentSize().height));
		this->addChild(labelScore);
	}

	if (tagB == 3)
	{
		this->removeChild(spriteB,true); 

		score += 10;
		//if (score>highScore) highScore = score;
		this->removeChild(labelScore);
		char scoreCount[20] = { 0 };
		sprintf(scoreCount, "Score: %d", score);
		labelScore = Label::createWithSystemFont(scoreCount, "Arial", 25);
		labelScore->setPosition(Point(visibleSize.width - labelScore->getContentSize().width, visibleSize.height - labelScore->getContentSize().height));
		this->addChild(labelScore);
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	CCLOG("BAll = %f",ball->getPositionY());
	
	
	if ((tagA == 0 || tagB  == 0 )& (ball->getPositionY() <= paddle->getPositionY()))
	{
		auto gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lost!");

		Director::getInstance()->replaceScene(gameOverScene);
	}
	
	return true;
}