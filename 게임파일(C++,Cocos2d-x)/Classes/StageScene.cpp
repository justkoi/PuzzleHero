#include "stdafx.h"

int g_nLevel = 0;
//CCPoint g_MousePoint = ccp(0,0);
Scene* StageScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StageScene::create();
	scene->addChild(layer);

	return scene;
}

bool StageScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	
	if(bgsound == true)
		D_SOUNDMNG->playBackgroundMusic("BGM_MenuScene.mp3");
	
	//!< 이미지 삽입
	CCSprite* pSprite = CCSprite::create("BackGround_StageMenu.png");
	pSprite->setPosition(0.0f,0.0f);
	pSprite->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(pSprite, 0);
	
	//!< 일시정지 화면


	m_pPauseBg_1 = CCSprite::create("BackGround_Option_1.png");
	m_pPauseBg_1->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2);
	m_pPauseBg_1->setVisible(false);
	this->addChild(m_pPauseBg_1, 31);

	
	m_pPauseBg_2 = CCSprite::create("BackGround_Credit_1.png");
	m_pPauseBg_2->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2);
	m_pPauseBg_1->setVisible(false);
	this->addChild(m_pPauseBg_2, 31);
	
	m_btnPause.Init(this,11,"Button_Option_1.png","Button_Option_3.png",CCPoint(660,1200),1.5f);
	m_btnPause.setVisible(true);
	
	m_btnProfile.Init(this,11,"Button_Stage_Lock.png","Button_Stage_Lock.png",CCPoint(120,1050),1.0f);
	m_btnProfile.setVisible(true);
	
	m_btnNext.Init(this,11,"Button_Stage_1_1.png","Button_Stage_1_3.png",CCPoint(120,870),1.0f);
	m_btnNext.setVisible(true);
	
	m_btnPause_Bg_On.Init(this,32,"Button_On_1.png","Button_On_3.png",CCPoint(300,280 + 440 - 25),1.0f);
	m_btnPause_Bg_On.setVisible(false);
	m_btnPause_Bg_On.setSync(false);

	m_btnPause_Bg_Off.Init(this,32,"Button_Off_1.png","Button_Off_3.png",CCPoint(425,280 + 440 - 25),1.0f);
	m_btnPause_Bg_Off.setVisible(false);
	m_btnPause_Bg_Off.setSync(false);

	m_btnPause_Effect_On.Init(this,32,"Button_On_1.png","Button_On_3.png",CCPoint(300,190 + 440 - 30),1.0f);
	m_btnPause_Effect_On.setVisible(false);
	m_btnPause_Effect_On.setSync(false);

	m_btnPause_Effect_Off.Init(this,32,"Button_Off_1.png","Button_Off_3.png",CCPoint(425,190 + 440 - 30),1.0f);
	m_btnPause_Effect_Off.setVisible(false);
	m_btnPause_Effect_Off.setSync(false);

	m_btnPause_Exit.Init(this,32,"Button_Exit_1.png","Button_Exit_3.png",CCPoint(300 + 20,50 + 440),1.0f);
	m_btnPause_Exit.setVisible(false);
	
	m_btnPause_Close.Init(this,32,"Button_Close_1.png","Button_Close_3.png",CCPoint(500 + 40,50 + 440),1.0f);
	m_btnPause_Close.setVisible(false);
	
	m_btnPause_Credit.Init(this,32,"Button_Credit_1.png","Button_Credit_3.png",CCPoint(60 + 80,50 + 440),1.0f);
	m_btnPause_Credit.setVisible(false);

	m_btnPause_Menu.Init(this,32,"Button_GoMenu_1.png","Button_GoMenu_3.png",CCPoint(60 + 80,50 + 440),1.0f);
	m_btnPause_Menu.setVisible(false);

/*
	auto profile = Sprite::create("tile1.png");
	profile->setPosition(Point(100, 1050));
	profile->setTag(100);
	this->addChild(profile);
	auto spr = Sprite::create("Button_Stage_1_1.png");
	spr->setPosition(Point(100,1000));
	spr->setTag(1);
	this->addChild(spr);
	auto spr1 = Sprite::create("option.png");
	spr1->setPosition(Point(D_PHONE_WIDTH-70,D_PHONE_HEIGHT-110));
	spr1->setTag(0);
	this->addChild(spr1);
	stagenum=0;
	sw=0;
	optionsw=0;

*/
	
	//!< 업데이트 루프
	this->schedule(schedule_selector(StageScene::Update), 0.0);

	auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(StageScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageScene::onTouchesEnded, this);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);

	g_nLevel = 0;

	return true;
}

void StageScene::onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event)
{
	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	m_btnPause.TouchBegan(g_MousePoint);
	m_btnPause_Bg_Off.TouchBegan(g_MousePoint);
	m_btnPause_Bg_On.TouchBegan(g_MousePoint);
	m_btnPause_Close.TouchBegan(g_MousePoint);
	m_btnPause_Effect_Off.TouchBegan(g_MousePoint);
	m_btnPause_Effect_On.TouchBegan(g_MousePoint);
	m_btnPause_Exit.TouchBegan(g_MousePoint);
	m_btnPause_Menu.TouchBegan(g_MousePoint);
	m_btnPause_Credit.TouchBegan(g_MousePoint);
	m_btnNext.TouchBegan(g_MousePoint);
	m_btnProfile.TouchBegan(g_MousePoint);
}

void StageScene::onTouchesMoved(const std::vector<Touch*>&touches, Event *unused_event)
{
	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	
	m_btnPause.TouchMoved(g_MousePoint);
	m_btnPause_Bg_Off.TouchMoved(g_MousePoint);
	m_btnPause_Bg_On.TouchMoved(g_MousePoint);
	m_btnPause_Close.TouchMoved(g_MousePoint);
	m_btnPause_Effect_Off.TouchMoved(g_MousePoint);
	m_btnPause_Effect_On.TouchMoved(g_MousePoint);
	m_btnPause_Exit.TouchMoved(g_MousePoint);
	m_btnPause_Menu.TouchMoved(g_MousePoint);
	m_btnPause_Credit.TouchMoved(g_MousePoint);
	m_btnNext.TouchMoved(g_MousePoint);
	m_btnProfile.TouchMoved(g_MousePoint);
}

void StageScene::onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event)
{
	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	
	m_btnPause.TouchEnded(g_MousePoint);
	m_btnPause_Bg_Off.TouchEnded(g_MousePoint);
	m_btnPause_Bg_On.TouchEnded(g_MousePoint);
	m_btnPause_Close.TouchEnded(g_MousePoint);
	m_btnPause_Effect_Off.TouchEnded(g_MousePoint);
	m_btnPause_Effect_On.TouchEnded(g_MousePoint);
	m_btnPause_Exit.TouchEnded(g_MousePoint);
	m_btnPause_Menu.TouchEnded(g_MousePoint);
	m_btnPause_Credit.TouchEnded(g_MousePoint);
	m_btnNext.TouchEnded(g_MousePoint);
	m_btnProfile.TouchEnded(g_MousePoint);
}

void StageScene::Update(float dt)
{
	
	m_btnPause.Update(dt);
	m_btnNext.Update(dt);

	m_btnPause_Bg_Off.Update(dt);
	m_btnPause_Bg_On.Update(dt);
	m_btnPause_Close.Update(dt);
	m_btnPause_Effect_Off.Update(dt);
	m_btnPause_Effect_On.Update(dt);
	m_btnPause_Exit.Update(dt);
	m_btnPause_Menu.Update(dt);
	m_btnPause_Credit.Update(dt);
	m_btnProfile.Update(dt);

	if(m_btnProfile.CheckAction() == true)
	{

		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1.0,ProfileScene::createScene());
		Director::getInstance()->replaceScene(scene);


		m_btnProfile.Reset();
	}

	if(m_btnNext.CheckAction() == true)
	{

		UserDefault::getInstance()->setIntegerForKey("stagenum",stagenum);
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();


		auto scene = TransitionFade::create(1.0,GameScene::createScene());
		Director::getInstance()->replaceScene(scene);


		m_btnNext.Reset();
	}
	if(m_btnPause.CheckAction() == true)
	{
		g_nLevel = 1;
		m_btnPause.Reset();
	}

	if(m_btnPause_Bg_Off.CheckAction() == true)
	{
		bgsound = false;

		D_SOUNDMNG->stopBackgroundMusic();
		
		m_btnPause_Bg_Off.Reset();

		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		UserDefault::getInstance()->setBoolForKey("bgsound",bgsound);
	}
	if(m_btnPause_Bg_On.CheckAction() == true)
	{
			
		bgsound = true;
		
		D_SOUNDMNG->playBackgroundMusic("BGM_MenuScene.mp3");
		
		m_btnPause_Bg_On.Reset();

		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		UserDefault::getInstance()->setBoolForKey("bgsound",bgsound);

	}
	if(m_btnPause_Effect_Off.CheckAction() == true)
	{
		efsound = false;

		m_btnPause_Effect_Off.Reset();

		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		UserDefault::getInstance()->setBoolForKey("efsound",efsound);
	}
	if(m_btnPause_Effect_On.CheckAction() == true)
	{
		efsound = true;

		m_btnPause_Effect_On.Reset();

		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		UserDefault::getInstance()->setBoolForKey("efsound",efsound);
	}

	if(m_btnPause_Close.CheckAction() == true)
	{
		g_nLevel = 0;

		m_btnPause_Close.Reset();


		//m_pBlind->setVisible(false);
//		m_pPauseBg->setVisible(false);
		m_btnPause_Bg_Off.setVisible(false);
		m_btnPause_Bg_On.setVisible(false);
		m_btnPause_Close.setVisible(false);
		m_btnPause_Effect_Off.setVisible(false);
		m_btnPause_Effect_On.setVisible(false);
		m_btnPause_Exit.setVisible(false);
		m_btnPause_Menu.setVisible(false);

		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);


	}
	if(m_btnPause_Exit.CheckAction() == true)
	{
		Director::getInstance()->end();
		//!< 게임종료
		m_btnPause_Exit.Reset();
	}
		
	if(m_btnPause_Menu.CheckAction() == true)
	{
		g_nLevel = 1;
		/*D_SOUNDMNG->stopBackgroundMusic();

		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		TransitionFade* scene = TransitionFade::create(1.0f,StageScene::createScene());
		Director::getInstance()->replaceScene(scene);
*/
		//!< 게임종료
		m_btnPause_Menu.Reset();
	}
	if(m_btnPause_Credit.CheckAction() == true)
	{
		g_nLevel = 2;
		/*D_SOUNDMNG->stopBackgroundMusic();

		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		TransitionFade* scene = TransitionFade::create(1.0f,StageScene::createScene());
		Director::getInstance()->replaceScene(scene);
*/
		//!< 게임종료
		m_btnPause_Credit.Reset();
	}
	if(g_nLevel == 0)
	{
		m_pPauseBg_1->setVisible(false);
		m_pPauseBg_2->setVisible(false);
		m_btnPause_Bg_On.setVisible(false);
		m_btnPause_Bg_Off.setVisible(false);
		m_btnPause_Effect_On.setVisible(false);
		m_btnPause_Effect_Off.setVisible(false);
		m_btnPause_Exit.setVisible(false);
		m_btnPause_Close.setVisible(false);
		m_btnPause_Credit.setVisible(false);
		m_btnPause_Menu.setVisible(false);
	}
	if(g_nLevel == 1)
	{
		m_pPauseBg_1->setVisible(true);
		m_pPauseBg_2->setVisible(false);

		m_btnPause_Bg_On.setVisible(true);
		m_btnPause_Bg_Off.setVisible(true);
		m_btnPause_Effect_On.setVisible(true);
		m_btnPause_Effect_Off.setVisible(true);

		if(bgsound == true)
		{
			m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

			m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
			
		}
		else if(bgsound == false)
		{
			m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

			m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		}

		if(efsound == true)
		{
			m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

			m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		}
		else if(efsound == false)
		{
			m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);

			m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		}

		m_btnPause_Close.setVisible(true);
		m_btnPause_Exit.setVisible(true);
		m_btnPause_Credit.setVisible(true);
		m_btnPause_Menu.setVisible(false);

	}
	else if(g_nLevel == 2)
	{
		m_pPauseBg_1->setVisible(false);
		m_pPauseBg_2->setVisible(true);


		m_btnPause_Bg_On.setVisible(false);
		m_btnPause_Bg_Off.setVisible(false);
		m_btnPause_Effect_On.setVisible(false);
		m_btnPause_Effect_Off.setVisible(false);

		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Bg_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_Off.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
		m_btnPause_Effect_On.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		
		m_btnPause_Exit.setVisible(true);
		m_btnPause_Close.setVisible(true);
		m_btnPause_Credit.setVisible(false);
		m_btnPause_Menu.setVisible(true);
	}
}

void StageScene::setOption()
{
	auto spr = Sprite::create("optionback.png");
	spr->setPosition(D_PHONE_WIDTH/2, D_PHONE_HEIGHT/2);
	spr->setTag(1000);
	this->addChild(spr);
		
	auto spr1 = Sprite::create("Button_On_1.png");
	if(!bgsound)
		spr1->setTexture("Button_On_3.png");
	spr1->setPosition(300,280);
	spr1->setTag(1001);
	spr->addChild(spr1);
	auto spr2 = Sprite::create("Button_Off_3.png");
	if(!bgsound)
		spr2->setTexture("Button_Off_1.png");
	spr2->setPosition(420,280);
	spr2->setTag(1002);
	spr->addChild(spr2);
	
	auto spr3 = Sprite::create("Button_On_1.png");
	if(!efsound)
		spr3->setTexture("Button_On_3.png");
	spr3->setPosition(300,190);
	spr3->setTag(1003);
	spr->addChild(spr3);
	auto spr4 = Sprite::create("Button_Off_3.png");
	if(!efsound)
		spr4->setTexture("Button_Off_1.png");
	spr4->setPosition(420,190);
	spr4->setTag(1004);
	spr->addChild(spr4);
	
	auto spr5 = Sprite::create("Button_Credit_1.png");
	spr5->setPosition(60,50);
	spr5->setTag(1005);
	spr->addChild(spr5);
	
	auto spr6 = Sprite::create("Button_Close_1.png");
	spr6->setPosition(530,50);
	spr6->setTag(1006);
	spr->addChild(spr6);
	
	auto spr7 = Sprite::create("Button_Exit_1.png");
	spr7->setPosition(300,50);
	spr7->setTag(1007);
	spr->addChild(spr7);
	
	optionsw=1;
}

void StageScene::setCredit()
{
	auto spr = Sprite::create("creditback.png");
	spr->setPosition(D_PHONE_WIDTH/2, D_PHONE_HEIGHT/2);
	spr->setTag(1000);
	this->addChild(spr);

	auto spr1 = Sprite::create("optionbtn.png");
	spr1->setPosition(60,50);
	spr1->setTag(1001);
	spr->addChild(spr1);
	
	auto spr2 = Sprite::create("Button_Close_1.png");
	spr2->setPosition(530,50);
	spr2->setTag(1002);
	spr->addChild(spr2);

	optionsw=2;
}
void StageScene::changeScene()
{
	if(stagenum==100)
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1.0,ProfileScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey("stagenum",stagenum);
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1.0,GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
}