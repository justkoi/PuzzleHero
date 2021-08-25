#include "stdafx.h"


Scene* LogoScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LogoScene::create();
	scene->addChild(layer);

	return scene;
}

bool LogoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	

	auto spr = Sprite::create("brainstorm.jpg");
	spr->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2);
	this->addChild(spr);

	this->scheduleOnce(schedule_selector(LogoScene::changeScene),1.0);
	return true;
}

void LogoScene::changeScene(float dt)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = TransitionFade::create(2.0,MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
