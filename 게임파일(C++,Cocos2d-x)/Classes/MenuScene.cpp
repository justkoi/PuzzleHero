#include "stdafx.h"

int g_nHeroHpConst = 0;
int g_nHeroAtk = 0;
int g_nHeroMpConst = 0;
int g_Skill[6] = {0,};
bool bgsound = true;
bool efsound = true;
bool selSkill[6];

//bool titlesw = false;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	
	loadData();

	if(bgsound == true)
		D_SOUNDMNG->playBackgroundMusic("BGM_LogoScene.mp3");




	auto spr = Sprite::create("title.png");
	spr->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2);
	spr->setTag(10);
	this->addChild(spr);
	auto spr1 = Sprite::create("touch.jpg");
	spr1->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2-300);
	spr1->setTag(11);
	this->addChild(spr1);
	countnum=0;
	auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MenuScene::onTouchesBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
	

	this->schedule(schedule_selector(MenuScene::Update), 0.0);

	return true;
}
void MenuScene::loadData()
{
	g_nHeroHpConst=UserDefault::getInstance()->getIntegerForKey("herohp",200);
	g_nHeroMpConst=UserDefault::getInstance()->getIntegerForKey("heromp",200);
	g_nHeroAtk=UserDefault::getInstance()->getIntegerForKey("heroatk",50);
	bgsound=UserDefault::getInstance()->getBoolForKey("bgsound",true);
	efsound=UserDefault::getInstance()->getBoolForKey("efsound",true);
	for(int i=0;i<6;++i)
	{
		char ms[7],ms2[10];
		sprintf(ms,"skill%d",i+1);
		sprintf(ms2,"selskill%d",i+1);
		if(i<4)
		{
			selSkill[i]=UserDefault::getInstance()->getBoolForKey(ms2,true);
			g_Skill[i]=UserDefault::getInstance()->getIntegerForKey(ms,1);
		}
		else
		{
			selSkill[i]=UserDefault::getInstance()->getBoolForKey(ms2,false);
			g_Skill[i]=UserDefault::getInstance()->getIntegerForKey(ms,0);
		}
	}
}

void MenuScene::Update(float delta)
{
	++countnum;
	auto spr = (Sprite*)this->getChildByTag(11);
	if(countnum%40==0){
		spr->setVisible(true);
	}
	else if(countnum%20==0){
		spr->setVisible(false);
	}
	
}
void MenuScene::onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = TransitionFade::create(1.0,StageScene::createScene());
	Director::getInstance()->replaceScene(scene);
}