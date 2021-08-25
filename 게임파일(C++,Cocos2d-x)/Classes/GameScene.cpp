#include "stdafx.h"



USING_NS_CC;

Point g_MousePoint;

CMap	g_Map; //!< 맵 0과 1로 체크 동적할당

char strTemp[256] = "";

unsigned char* strBuffer;
int m_nWidth = 0;
int m_nHeight = 0;
char sWidth[256];
char sHeight[256];

int	g_nBlockMax; //!< 최대 블록 수

CBlock g_BlockList[D_BLOCKMAP_MAX]; //!< 모든 블록 동적할당


vector<int> g_nTargetPopBlock;
vector<int> g_nTargetPopBlock2;


bool g_bPause = false;

int g_nNowLine = 0;
int g_nHeroDamage = g_nHeroAtk;



int g_nHeroHp = 100;
int g_nHeroHpMax = 100;
int g_nHeroIdx = 0;

int g_nHeroMp = g_nHeroMpConst;
int g_nHeroMpMax = g_nHeroMpConst;

stVec2i g_stHeroIdx ;

int g_nScore = 0; //!< 총점


float fBasicScore = 100.0f;

BEffectManager g_EffectManager;
BNumberManager g_NumberManager;
//!< 한글출력 문제해결을 위한 UTF8인코딩 (cocos2d-x는 내부적으로 UTF8인코딩을 사용)
//!< ==> 모든 파일 UTF8인코딩 CCImage내의 WiteCharToMultiByte 수정하여 해결(첫번째 인자를 CP_UTF8로 변경)
//wchar_t wstrTemp[128];
//
//void GameScene::SetMsg()
//{
//	WideCharToMultiByte(CP_UTF8,0,wstrTemp,-1,strTemp,128,0,0);
//}
//	

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
//
//void GameScene::onEnter()
//{
//	//!< 멀티터치 리스너
//	//...
// 
//    auto listener = EventListenerTouchAllAtOnce::create();
//    //listener->setSwallowTouches(true); //멀티터치이기 때문에 삼키면 안된다
// 
//    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
// 
//    //...
//
//	
//	this->scheduleUpdate();
//
//}
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	//CCParticleSystem *emitter3;
	//emitter3 = CCParticleFire::create();
	//emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	////emitter3->setTotalParticles(20);
	////!< 주의 다시 메모리 해제해주는 방법 찾을것
	////emitter3->setAutoRemoveOnFinish(true);
	//emitter3->setLife(1.0f);
	//emitter3->setLifeVar(0.5f);
	//emitter3->setPosition(ccp( 200.0f, 950.0f));
	////emitter3->setGravity(ccp(0,0));
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter3->setScale(1.0f);
	////emitter3->setStartSize(1.0f);
	////emitter3->setStartSizeVar(1.0f);
	////emitter3->setEndSize(1.5f);
	////emitter3->setEndSizeVar(1.5f);
	////emitter3->setDuration(20.0f);
	////emitter3->setSpeed(160);
	////emitter3->setSpeedVar(0);
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter3->setEmissionRate(60.0f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);

	//emitter3->setStartColor(ccc4f((1.0f/255) * 80, (1.0f/255) * 80, (1.0f/255) * 255, 1.0f));
	//emitter3->setEndColor(ccc4f((1.0f/255) * 150, (1.0f/255) * 150, (1.0f/255) * 255, 0.0f));
	//
	//this->addChild(emitter3,10);

	
	g_Map.Init();

	m_nPopBlockNumber = 1;

	g_EffectManager.Init(this);
	g_NumberManager.Init(this);


	D_SOUNDMNG->setBackgroundMusicVolume(1.0f);
	D_SOUNDMNG->setEffectsVolume(1.0f);
	D_SOUNDMNG->preloadEffect("Select.mp3");
	D_SOUNDMNG->preloadEffect("Clear.mp3");
	
	if(bgsound == true)
		D_SOUNDMNG->playBackgroundMusic("BGM_GameScene.mp3");

	m_btnSkill.Init(this,1,"Button_Skill_1_1.png","Button_Skill_1_3.png",CCPoint(120,120),1.0f);
	m_btnSkill_2.Init(this,1,"Button_Skill_2_1.png","Button_Skill_2_3.png",CCPoint(270,120),1.0f);
	m_btnSkill_3.Init(this,1,"Button_Skill_3_1.png","Button_Skill_3_3.png",CCPoint(420,120),1.0f);
	m_btnSkill_4.Init(this,1,"Button_Skill_4_1.png","Button_Skill_4_3.png",CCPoint(570,120),1.0f);

	m_btnPause.Init(this,4,"Button_Pause_1.png","Button_Pause_3.png",CCPoint(660,1200),1.0f);
	
	
	//!< 일시정지 화면

	m_pPauseBg = CCSprite::create("BackGround_Option_1.png");
	m_pPauseBg->setPosition(D_PHONE_WIDTH/2,D_PHONE_HEIGHT/2);
	m_pPauseBg->setVisible(false);
	this->addChild(m_pPauseBg, 31);
	
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
	
	m_btnPause_Menu.Init(this,32,"Button_GoMenu_1.png","Button_GoMenu_3.png",CCPoint(60 + 80,50 + 440),1.0f);
	m_btnPause_Menu.setVisible(false);


	//!< 클리어 화면
	m_btnClearMenu.Init(this,32,"Button_Menu_1.png","Button_Menu_3.png",CCPoint(280,580),2.0f);
	m_btnClearMenu.setVisible(false);

	m_btnClearRetry.Init(this,32,"Button_Retry_1.png","Button_Retry_3.png",CCPoint(440,580),2.0f);
	m_btnClearRetry.setVisible(false);

	//!< 멀티터치 리스너
//	//...
 
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true); //멀티터치이기 때문에 삼키면 안된다
 
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
//    //...
//

	g_MousePoint.x = 0;
	g_MousePoint.y = 0;

	g_stHeroIdx.m_nX = 0;
	g_stHeroIdx.m_nY = 0;


	//!< Style버튼 삽입m_bTestButton.Init(this,100,"Button_Test_1.png","Button_Test_3.png",CCPoint(150,150),3.3f,1.0f,0.9f);


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	

	//!< 글자삽입
 //   m_pLabel = LabelTTF::create("Hello World", "Arial", 24);
 //   //
 //   //// position the label on the center of the screen
 //   m_pLabel->setPosition(Point(200, 100));
	//m_pLabel->setAnchorPoint(CCPoint(0.0f,0.0f));
	////m_pLabel->set
 //   //// add the label as a child to this layer

	////swprintf(wstrTemp, L"좌표 (%d,%d)", g_MousePoint.x, g_MousePoint.y);
	////SetMsg();
	//

	//sprintf(strTemp,"좌표 (%f,%f)", g_MousePoint.x, g_MousePoint.y);
	//m_pLabel->setString(strTemp);

 //   this->addChild(m_pLabel, 1);


	//!< 이미지 삽입
	CCSprite* pSprite = CCSprite::create("BackGround_Game.png");
	pSprite->setPosition(0.0f,0.0f);
	pSprite->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(pSprite, 0);
	
	//!< 이미지 삽입
	/*m_pBoard = CCSprite::create("board.png");
	m_pBoard->setPosition(25,210);
	m_pBoard->setScale((70.0f/64.0f));
	m_pBoard->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pBoard, 1);*/
	
	//!< 이미지 삽입
	/*m_pScore = CCSprite::create("score.png");
	m_pScore->setPosition(50,1050);
	m_pScore->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pScore, 1);
	*/
	//!< 이미지 삽입
	/*m_pStatus = CCSprite::create("status.png");
	m_pStatus->setPosition(50,1100);
	m_pStatus->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pStatus, 1);
	*/
	//!< 이미지 삽입
	/*m_pBar_1 = CCSprite::create("Bar_1.png");
	m_pBar_1->setPosition(250,1110);
	m_pBar_1->setScale(2.0f,8.0f);
	m_pBar_1->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pBar_1, 2);
*/
	
	
	//!< 이미지 삽입
	m_pStarBar_1 = CCSprite::create("Bar_1.png");
	m_pStarBar_1->setPosition(120,1204 - 28 - 28);
	m_pStarBar_1->setScale( 0.85f,1.0f);
	m_pStarBar_1->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pStarBar_1, 3);

	//!< 이미지 삽입
	m_pMpBar_1 = CCSprite::create("Bar_2.png");
	m_pMpBar_1->setPosition(120,1204 - 28);
	m_pMpBar_1->setScale( 0.85f,1.0f);
	m_pMpBar_1->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pMpBar_1, 3);
	
	//!< 이미지 삽입
	m_pHpBar_1 = CCSprite::create("Bar_3.png");
	m_pHpBar_1->setPosition(120,1204);
	m_pHpBar_1->setScale( 0.85f,1.0f);
	m_pHpBar_1->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pHpBar_1, 3);

	

	m_pReady = CCSprite::create("Ready.png");
	m_pReady->setPosition( ccp( D_PHONE_WIDTH/2 , D_PHONE_HEIGHT + 100.0f  ) );
	m_pReady->setScaleX(1.5f );
	m_pReady->setScaleY(1.5f );
    this->addChild(m_pReady, 33);

	m_pGo = CCSprite::create("Go.png");
	m_pGo->setPosition( ccp( D_PHONE_WIDTH/2 , D_PHONE_HEIGHT + 100.0f  ) );
	m_pGo->setScaleX(1.5f );
	m_pGo->setScaleY(1.5f );
    this->addChild(m_pGo, 33);
	
	m_pBlind = CCSprite::create("Game_Blind.png");
	m_pBlind->setPosition( ccp( D_PHONE_WIDTH/2 , D_PHONE_HEIGHT/2  ) );
	m_pBlind->setScaleX(3.0f);
	m_pBlind->setScaleY(3.0f);
	m_pBlind->setOpacity(255 * 0.7f);
	m_pBlind->setVisible(false);
    this->addChild(m_pBlind, 30);

	
	m_pGameResult_Clear = CCSprite::create("Game_Clear.png");
	m_pGameResult_Clear->setPosition( ccp( D_PHONE_WIDTH/2 , D_PHONE_HEIGHT/2  ) );
	m_pGameResult_Clear->setScaleX(1.5f );
	m_pGameResult_Clear->setScaleY(1.5f );
	m_pGameResult_Clear->setVisible(false);
    this->addChild(m_pGameResult_Clear, 31);
	
	m_pGameResult_Defeat = CCSprite::create("Game_Defeat.png");
	m_pGameResult_Defeat->setPosition( ccp( D_PHONE_WIDTH/2 , D_PHONE_HEIGHT/2  ) );
	m_pGameResult_Defeat->setScaleX(1.5f );
	m_pGameResult_Defeat->setScaleY(1.5f );
	m_pGameResult_Defeat->setVisible(false);
    this->addChild(m_pGameResult_Defeat, 31);

	//!< 이미지 삽입
	/*m_pScore = CCSprite::create("score.png");
	m_pScore->setPosition(20,900);
	m_pScore->setAnchorPoint(CCPoint(0.0f,0.0f));
	this->addChild(m_pScore, 0);
	*/
	//!< TestDisplyer 삽입
	/*m_TextDisplayer.Init(this,100,Point(0.0f,0.0f),"Commit Name으로서 Cocos2dx엔진에서 사용안함",100,550,40,23,20,ccColor3B(255,255,255));
	m_TextDisplayer.SetText("아주대학교 게임제작 소학회 브레인스톰/게임구성요소 설명/PartMap : 각각의 부분 맵/MapManager : 맵을 담아 보관하며 (맵을 씬처럼 체인지 해줌)/Hero : 플레이어가 조종하는 캐릭터/BlokingBlock : 충돌객체(통과불가)");
	m_TextDisplayer.SetProgressTime(0.03f);
*/

	
	m_eGameResult = E_GAME_RESULT_NONE;

	m_eGameStep = E_GAME_STEP_READY;

	m_ePlayStep = E_PLAY_STEP_PLAY;

	g_nBlockMax = D_BLOCKMAP_WIDTH * D_BLOCKMAP_HEIGHT;
	
	for(int i=0; i<g_nBlockMax; i++)
	{
		g_BlockList[i].Init(this, i);
	}
	
	m_nTargetScore = 5000;

	m_numberScore.Init(this,ccp(1.0f,1.0f),0,ccp(420.0f,1075.0f),3);

	m_numberScore_Target.Init(this,ccp(1.0f,1.0f),0,ccp(560.0f,1075.0f),3);
	
	m_numberTime.Init(this,ccp(1.0f,1.0f),0,ccp(170.0f,1075.0f),3);
	
	//!< 글자삽입
    m_labelTime = LabelTTF::create("Hello World", "Arial", 30);
 
    m_labelTime->setPosition(Point(100.0f,1075.0f));
	m_labelTime->setString("Time : ");

    this->addChild(m_labelTime, 3);

	
	//!< 글자삽입
    m_labelScore = LabelTTF::create("Hello World", "Arial", 30);
 
    m_labelScore->setPosition(Point(365.0f,1075.0f));
	m_labelScore->setString("Score :                   /");

    this->addChild(m_labelScore, 3);


	m_fTimer = 0.0f;

	m_numberTime.EffectNumber( 0 );
	m_numberScore_Target.EffectNumber( m_nTargetScore );


	m_nStartLineStep = 0;
	m_fStartLineTimer = 0.0f;
	m_fStartLineTime = 0.4f;
	m_fReadyTimer = 0.0f;
	
	
	for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
	{
		m_bPoped[i] = false;
	}

	 m_stFirstBlockIdx = stVec2i(0,0);
	 m_stSecondBlockIdx = stVec2i(0,0);

	 m_nFirstBlock = 0;
	 m_nSecondBlock = 0;
	 
	 m_bSkill_1_Used = false;
	 m_bSkill_2_Used = false;
	 m_bSkill_4_Used = false;

	 m_fPopSetTimer = 0.0f;

	//!< 업데이트 루프
	this->schedule(schedule_selector(GameScene::Update), 0.0);
	
	g_nScore = 0;
	m_numberScore.EffectNumber(g_nScore);
	


	
	g_bPause = false;

	g_nNowLine = 0;
	g_nHeroDamage = 50.0f;



	g_nHeroHp = 100;
	g_nHeroHpMax = 100;
	g_nHeroIdx = 0;

	g_nHeroMp = 200;
	g_nHeroMpMax = 200;

	g_nScore = 0; //!< 총점


	fBasicScore = 100.0f;


    return true;
}




void GameScene::Update(float dt)
{


	
	if(g_nHeroMp <= 0)
		g_nHeroMp = 0;
	//m_pMpBar_1->setScale( ((float)g_nHeroMp/(float)g_nHeroMpMax) * 1.6f ,2.0f);

	if(g_nHeroHp <= 0)
		g_nHeroHp = 0;
	//m_pHpBar_1->setScale(((float)g_nHeroHp/(float)g_nHeroHpMax) * 1.6f,2.0f);

	
	m_pStarBar_1->setTextureRect(Rect(0,0,((float)g_nScore/(float)m_nTargetScore) * 560 ,28));
	
	m_pMpBar_1->setTextureRect(Rect(0,0,((float)g_nHeroMp/(float)g_nHeroMpMax) * 560 ,28));
	
	m_pHpBar_1->setTextureRect(Rect(0,0,((float)g_nHeroHp/(float)g_nHeroHpMax) * 560 ,28));
	
	m_numberScore.Update(dt);
	m_numberScore.EffectNumber(g_nScore);
	
	m_numberScore_Target.Update(dt);

	m_numberTime.SetNumber( D_PLAYTIME -  (int)m_fTimer);
	m_numberTime.Update(dt);

	
	if(g_bPause == false)
	{
		
		if(m_btnPause.CheckAction() == true)
		{
			g_bPause = true;
			m_btnPause.Reset();
		}

		g_EffectManager.Update(dt);
		g_NumberManager.Update(dt);

		if(m_eGameStep == E_GAME_STEP_READY)
		{
			m_fTimer += dt;

			
			if(m_fTimer >= 0.5f)
				m_fReadyTimer += dt;

			Logic_StartLine(dt);
			Logic_BlockUpdate(dt);
			Logic_BlockFall();
			

			if(m_fReadyTimer <= 1.0f)
			{
				m_pReady->setPositionY( ((D_PHONE_HEIGHT + 100.0f ) - (m_fReadyTimer * D_PHONE_HEIGHT/2 )) * D_SCALE_HEIGHT);
				m_pReady->setScaleX((m_fReadyTimer+0.2f) * D_SCALE_WIDTH);
				m_pReady->setScaleY((m_fReadyTimer+0.2f) * D_SCALE_HEIGHT);
			}

			else if(m_fReadyTimer <= 2.0f)
			{
				m_pReady->setOpacity(255 * (1.0f - (m_fReadyTimer - 1.0f)));
				m_pReady->setScaleX((1.2f - (m_fReadyTimer - 1.0f)) * D_SCALE_WIDTH);
				m_pReady->setScaleY((1.2f - (m_fReadyTimer - 1.0f)) * D_SCALE_HEIGHT);
				
				m_pGo->setPositionY( ((D_PHONE_HEIGHT + 100.0f ) - ((m_fReadyTimer - 1.0f) * D_PHONE_HEIGHT/2 )) * D_SCALE_HEIGHT);
				//m_pGo->setPositionX( ((-100) + ((m_fReadyTimer - 1.0f) * 340)) * D_SCALE_WIDTH);
				
				m_pGo->setScaleX(((m_fReadyTimer - 1.0f) + 0.2f) * D_SCALE_WIDTH);
				m_pGo->setScaleY(((m_fReadyTimer - 1.0f) + 0.2f) * D_SCALE_HEIGHT);
			}

			else if(m_fReadyTimer <= 3.0f)
			{
				m_pGo->setOpacity(255 * (1.0f - (m_fReadyTimer - 2.0f)));
				m_pGo->setScaleX((1.2f - (m_fReadyTimer - 2.0f)) * D_SCALE_WIDTH);
				m_pGo->setScaleY((1.2f - (m_fReadyTimer - 2.0f)) * D_SCALE_HEIGHT);
			}

			
		}
		else if(m_eGameStep == E_GAME_STEP_PLAY)
		{
			m_fTimer += dt;


			m_btnSkill.Update(dt);
			m_btnSkill_2.Update(dt);
			m_btnSkill_3.Update(dt);
			m_btnSkill_4.Update(dt);
			if(m_bSkill_1_Used == true)
			{
				m_btnSkill.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
				m_btnSkill.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
			}
			else
			{
				m_btnSkill.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
				m_btnSkill.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
			}
			if(m_bSkill_2_Used == true)
			{
				m_btnSkill_2.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
				m_btnSkill_2.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
			}
			else
			{
				m_btnSkill_2.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
				m_btnSkill_2.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
			}
			if(m_bSkill_4_Used == true)
			{
				m_btnSkill_4.m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
				m_btnSkill_4.m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
			}
			else
			{
				m_btnSkill_4.m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
				m_btnSkill_4.m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
			}
			m_btnPause.Update(dt);

			if(g_nHeroHp <= 0 || m_fTimer >= D_PLAYTIME)
			{
				if(efsound == true)
					D_SOUNDMNG->playEffect("Clear.mp3");
				m_eGameStep = E_GAME_STEP_END;
				m_eGameResult = E_GAME_RESULT_DEFEAT;
			}

			if(g_nScore >= m_nTargetScore)
			{
				if(efsound == true)
					D_SOUNDMNG->playEffect("Clear.mp3");
				m_eGameStep = E_GAME_STEP_END;
				m_eGameResult = E_GAME_RESULT_VICTORY;
			}

		/*	for(int i=0; i<g_nBlockMax; i++)
			{
				g_BlockList[i].Update(dt);
			}*/
			if(m_btnPause.CheckAction() == true)
			{
				m_btnPause.Reset();
			}
			Logic_BlockUpdate(dt);

			if(m_ePlayStep == E_PLAY_STEP_PLAY)
			{
				
				if(m_btnSkill.CheckAction() == true && g_nHeroMp >= D_SKILL_1_COST && m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
				{
					g_nHeroMp -= D_SKILL_1_COST;
					m_bSkill_1_Used = true;
					m_btnSkill.Reset();
					m_ePlayStep = E_PLAY_STEP_SKILL_1;
				}
				if(m_btnSkill_2.CheckAction() == true && g_nHeroMp >= D_SKILL_2_COST && m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
				{
					g_nHeroMp -= D_SKILL_2_COST;
					m_bSkill_2_Used = true;
					m_btnSkill_2.Reset();
					//m_ePlayStep = E_PLAY_STEP_SKILL_2;
				}
				if(m_btnSkill_3.CheckAction() == true && g_nHeroMp >= D_SKILL_3_COST)
				{
					g_nHeroMp -= D_SKILL_3_COST;
					g_BlockList[m_nFirstBlock].m_nHpNow += D_SKILL_3_HEAL;
					//!< 최대 Hp 초과 불가
					if(g_BlockList[m_nFirstBlock].m_nHpNow > g_BlockList[m_nFirstBlock].m_nHpMax)
						g_BlockList[m_nFirstBlock].m_nHpNow = g_BlockList[m_nFirstBlock].m_nHpMax;
					if(efsound == true)
						D_SOUNDMNG->playEffect("Sk3.mp3");

					m_btnSkill_3.Reset();
					//m_ePlayStep = E_PLAY_STEP_SKILL_2;
				}
				if(m_btnSkill_4.CheckAction() == true && g_nHeroMp >= D_SKILL_4_COST && m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
				{
					g_nHeroMp -= D_SKILL_4_COST;
					m_bSkill_4_Used = true;
					m_btnSkill_4.Reset();
					//m_ePlayStep = E_PLAY_STEP_SKILL_2;
				}
			}
			else if(m_ePlayStep == E_PLAY_STEP_DRAG)
			{

			}
			else if(m_ePlayStep == E_PLAY_STEP_CHANGE)
			{

				//!< 히어로 블록 체인지
				if( g_BlockList[m_nFirstBlock].m_fChangeDistance > 0.0f)
				{
					if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_RIGHT )
					{
						g_BlockList[m_nFirstBlock].m_stPos.x += D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nFirstBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt ;
						if(g_BlockList[m_nFirstBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nFirstBlock].m_stPos.x += g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nFirstBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_LEFT )
					{
						g_BlockList[m_nFirstBlock].m_stPos.x -= D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nFirstBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt ;
						if(g_BlockList[m_nFirstBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nFirstBlock].m_stPos.x -= g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nFirstBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_UP )
					{
						g_BlockList[m_nFirstBlock].m_stPos.y -= D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nFirstBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt ;
						if(g_BlockList[m_nFirstBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nFirstBlock].m_stPos.y -= g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nFirstBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_DOWN )
					{
						g_BlockList[m_nFirstBlock].m_stPos.y += D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nFirstBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt ;
						if(g_BlockList[m_nFirstBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nFirstBlock].m_stPos.y += g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nFirstBlock].m_fChangeDistance = 0.0f;
						}
					}
				}
				//!<대상 블록 체인지
				if( g_BlockList[m_nSecondBlock].m_fChangeDistance > 0.0f)
				{
					if(g_BlockList[m_nSecondBlock].m_eDerection == E_DERECTION_RIGHT )
					{
						g_BlockList[m_nSecondBlock].m_stPos.x += D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nSecondBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt;
						if(g_BlockList[m_nSecondBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nSecondBlock].m_stPos.x += g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nSecondBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nSecondBlock].m_eDerection == E_DERECTION_LEFT )
					{
						g_BlockList[m_nSecondBlock].m_stPos.x -= D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nSecondBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt;
						if(g_BlockList[m_nSecondBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nSecondBlock].m_stPos.x -= g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nSecondBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nSecondBlock].m_eDerection == E_DERECTION_UP )
					{
						g_BlockList[m_nSecondBlock].m_stPos.y -= D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nSecondBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt;
						if(g_BlockList[m_nSecondBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nSecondBlock].m_stPos.y -= g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nSecondBlock].m_fChangeDistance = 0.0f;
						}
					}
					else if(g_BlockList[m_nSecondBlock].m_eDerection == E_DERECTION_DOWN )
					{
						g_BlockList[m_nSecondBlock].m_stPos.y += D_BLOCK_CHANGE_SPEED * dt;
						g_BlockList[m_nSecondBlock].m_fChangeDistance -= D_BLOCK_CHANGE_SPEED * dt;
						if(g_BlockList[m_nSecondBlock].m_fChangeDistance < 0.0f)
						{
							g_BlockList[m_nSecondBlock].m_stPos.y += g_BlockList[m_nFirstBlock].m_fChangeDistance;
							g_BlockList[m_nSecondBlock].m_fChangeDistance = 0.0f;
						}
					}
				}
				//!< 체인지 완료 후 단계
				if( g_BlockList[m_nFirstBlock].m_fChangeDistance == 0.0f && g_BlockList[m_nSecondBlock].m_fChangeDistance == 0.0f )
				{
					stVec2i stTemp = g_BlockList[m_nFirstBlock].m_stIndex;
					g_BlockList[m_nFirstBlock].m_stIndex = g_BlockList[m_nSecondBlock].m_stIndex;
					g_BlockList[m_nSecondBlock].m_stIndex = stTemp;

					g_BlockList[m_nFirstBlock].m_nHpNow -= g_BlockList[m_nSecondBlock].m_nDamage;
					//g_BlockList[m_nSecondBlock].m_nHpNow -= g_BlockList[m_nFirstBlock].m_nDamage;
					g_nTargetPopBlock2.push_back(m_nSecondBlock);
					

					if(m_bSkill_2_Used == true)
					{
						m_bSkill_2_Used = false;
						m_ePlayStep = E_PLAY_STEP_SKILL_2;
						g_nTargetPopBlock2.clear();
					}
					else if(m_bSkill_4_Used == true)
					{
						m_bSkill_4_Used = false;
						m_ePlayStep = E_PLAY_STEP_SKILL_4;
						g_nTargetPopBlock2.clear();
					}
					else
					{
						m_ePlayStep = E_PLAY_STEP_POP; //!< 원래는 E_PLAY_STEP_POP
					}

				}

			}
			else if(m_ePlayStep == E_PLAY_STEP_POP)
			{
				//!< 죽은 블록 리스트에 전부 추가
				for(int i=0; i<g_nBlockMax; i++)
				{
					if( g_BlockList[i].m_nHpNow <= 0 )
					{
						g_nTargetPopBlock.push_back(i);
					}

					/*	if( g_BlockList[i].m_nHpNow < g_BlockList[i].m_nHpMax )
					{
						
					}*/
				}

				
				Logic_Pop(); //!< 블록 터트리는 로직 갱신
				g_nTargetPopBlock.clear();
				g_nTargetPopBlock2.clear();

				//FillBlockCheck();

				m_ePlayStep = E_PLAY_STEP_POPSET; //!< 원래는 E_PLAY_STEP_POP

			}
			else if(m_ePlayStep == E_PLAY_STEP_SKILL_POP)
			{
				bool bPoped = false;
				//!< 죽은 블록 리스트에 전부 추가
				for(int i=0; i<g_nBlockMax; i++)
				{
					if( g_BlockList[i].m_nHpNow <= 0 )
					{
						g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
						g_BlockList[i].Die();

					
						bPoped = true;
					}
				}
				if(bPoped == true)
				{
					if(efsound == true)
						D_SOUNDMNG->playEffect("BlockPop_1.mp3");
				}
				
				Logic_Pop(); //!< 블록 터트리는 로직 갱신
				
				g_nTargetPopBlock.clear();
				g_nTargetPopBlock2.clear();

				m_ePlayStep = E_PLAY_STEP_POPSET; //!< 원래는 E_PLAY_STEP_POP

			}
			else if(m_ePlayStep == E_PLAY_STEP_POPSET)
			{
				m_fPopSetTimer += dt;
				if(m_fPopSetTimer >= 0.4f)
				{
					FillBlockCheck();

					m_fPopSetTimer = 0.0f;
					m_ePlayStep = E_PLAY_STEP_POPSET_2;
				}
			}
			else if(m_ePlayStep == E_PLAY_STEP_POPSET_2)
			{

				Logic_BlockFall();

				if(FillBlockEnd() == true)
				{
						
				
					m_ePlayStep = E_PLAY_STEP_PLAY;
				}
			}
			else if(m_ePlayStep == E_PLAY_STEP_SKILL_1)
			{
				
			}
			else if(m_ePlayStep == E_PLAY_STEP_SKILL_2)
			{
				
				for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
				{
					m_bPoped[i] = false;
				}
				//!< 죽은 블록 리스트에 전부 추가
				for(int i=0; i<g_nBlockMax; i++)
				{
					
					if( 
						(g_BlockList[i].m_nHpNow <= 0) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX - 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX + 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY + 1) ||
						
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY - 1) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX + 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY + 1) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX - 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY + 1) ||
						
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX + 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY - 1) ||
						(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX - 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY - 1) 
						
						)
					{
						g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
						g_BlockList[i].Die();
						Explosion(ccp(g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y), g_BlockList[i].m_eBlockNumber);
						g_EffectManager.Insert((int)g_BlockList[i].m_eBlockNumber,g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y);

						if(g_BlockList[i].m_eBlockNumber == 0 || g_BlockList[i].m_eBlockNumber == 3)
						{
							fBasicScore = D_SCORE_POP * 2;	
						}
						else
						{
							fBasicScore = D_SCORE_POP;
						}

						g_NumberManager.Insert(  fBasicScore  , g_BlockList[i].m_stPos.x, g_BlockList[i].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
						g_nScore += (int)(fBasicScore);
					
						if(efsound == true)
							D_SOUNDMNG->playEffect("Sk2.mp3");
						
						m_bPoped[(int)g_BlockList[i].m_eBlockNumber] = true;

					}
				}
				if(efsound == true)
				{		
					for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
					{
						if(m_bPoped[i] == true)
							D_SOUNDMNG->playEffect(StringUtils::format("Block_%d.mp3",i).c_str());
					}
				}
				
				
				Logic_Pop(); //!< 블록 터트리는 로직 갱신

				//FillBlockCheck();

				m_ePlayStep = E_PLAY_STEP_POPSET; //!< 원래는 E_PLAY_STEP_POP
			}
			else if(m_ePlayStep == E_PLAY_STEP_SKILL_4)
			{
				
				for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
				{
					m_bPoped[i] = false;
				}

				
				//!< 죽은 블록 리스트에 전부 추가
				for(int i=0; i<g_nBlockMax; i++)
				{

					if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_RIGHT)
					{
						if( 
							(g_BlockList[i].m_nHpNow <= 0) ||
							(g_BlockList[i].m_stIndex.m_nX > g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX - 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) 
							)
						{
							g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
							g_BlockList[i].Die();
							Explosion(ccp(g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y), g_BlockList[i].m_eBlockNumber);
							g_EffectManager.Insert((int)g_BlockList[i].m_eBlockNumber,g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y);
							if(g_BlockList[i].m_eBlockNumber == 0 || g_BlockList[i].m_eBlockNumber == 3)
							{
								fBasicScore = D_SCORE_POP * 2;	
							}
							else
							{
								fBasicScore = D_SCORE_POP;
							}

							g_NumberManager.Insert(  fBasicScore  , g_BlockList[i].m_stPos.x, g_BlockList[i].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
								g_nScore += (int)(fBasicScore);
							
							m_bPoped[(int)g_BlockList[i].m_eBlockNumber] = true;

						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_LEFT)
					{
						if( 
							(g_BlockList[i].m_nHpNow <= 0) ||
							(g_BlockList[i].m_stIndex.m_nX < g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX + 1 && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY) 
							)
						{
							g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
							g_BlockList[i].Die();
							Explosion(ccp(g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y), g_BlockList[i].m_eBlockNumber);
							g_EffectManager.Insert((int)g_BlockList[i].m_eBlockNumber,g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y);
							if(g_BlockList[i].m_eBlockNumber == 0 || g_BlockList[i].m_eBlockNumber == 3)
							{
								fBasicScore = D_SCORE_POP * 2;	
							}
							else
							{
								fBasicScore = D_SCORE_POP;
							}

							g_NumberManager.Insert(  fBasicScore  , g_BlockList[i].m_stPos.x, g_BlockList[i].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore);
					
					
							
							m_bPoped[(int)g_BlockList[i].m_eBlockNumber] = true;

						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_UP)
					{
						if( 
							(g_BlockList[i].m_nHpNow <= 0) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY > g_stHeroIdx.m_nY) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY - 1) 
							)
						{
							g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
							g_BlockList[i].Die();
							Explosion(ccp(g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y), g_BlockList[i].m_eBlockNumber);
							g_EffectManager.Insert((int)g_BlockList[i].m_eBlockNumber,g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y);
							if(g_BlockList[i].m_eBlockNumber == 0 || g_BlockList[i].m_eBlockNumber == 3)
							{
								fBasicScore = D_SCORE_POP * 2;	
							}
							else
							{
								fBasicScore = D_SCORE_POP;
							}

							g_NumberManager.Insert(  fBasicScore  , g_BlockList[i].m_stPos.x, g_BlockList[i].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore);
					
					
							
							m_bPoped[(int)g_BlockList[i].m_eBlockNumber] = true;

						}
					}
					else if(g_BlockList[m_nFirstBlock].m_eDerection == E_DERECTION_DOWN)
					{
						if( 
							(g_BlockList[i].m_nHpNow <= 0) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY < g_stHeroIdx.m_nY) ||
							(g_BlockList[i].m_stIndex.m_nX == g_stHeroIdx.m_nX && g_BlockList[i].m_stIndex.m_nY == g_stHeroIdx.m_nY + 1) 
							)
						{
							g_Map.m_nBlockMap[g_BlockList[i].m_stIndex.m_nY][g_BlockList[i].m_stIndex.m_nX] = 0;
							g_BlockList[i].Die();
							Explosion(ccp(g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y), g_BlockList[i].m_eBlockNumber);
							g_EffectManager.Insert((int)g_BlockList[i].m_eBlockNumber,g_BlockList[i].m_stPos.x,g_BlockList[i].m_stPos.y);
							if(g_BlockList[i].m_eBlockNumber == 0 || g_BlockList[i].m_eBlockNumber == 3)
							{
								fBasicScore = D_SCORE_POP * 2;	
							}
							else
							{
								fBasicScore = D_SCORE_POP;
							}

							g_NumberManager.Insert(  fBasicScore  , g_BlockList[i].m_stPos.x, g_BlockList[i].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore);
					

							
							
							m_bPoped[(int)g_BlockList[i].m_eBlockNumber] = true;

						}
					}

				}
				
			
				if(efsound == true)
				{		
					for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
					{
						if(m_bPoped[i] == true)
							D_SOUNDMNG->playEffect(StringUtils::format("Block_%d.mp3",i).c_str());
					}
					D_SOUNDMNG->playEffect("Sk4.mp3");
				}
				
				Logic_Pop(); //!< 블록 터트리는 로직 갱신

				//FillBlockCheck();

				m_ePlayStep = E_PLAY_STEP_POPSET; //!< 원래는 E_PLAY_STEP_POP
			}

		}
		else if(m_eGameStep == E_GAME_STEP_END)
		{
			m_pBlind->setVisible(true);

			if(m_eGameResult == E_GAME_RESULT_VICTORY)
				m_pGameResult_Clear->setVisible(true);

			if(m_eGameResult == E_GAME_RESULT_DEFEAT)
				m_pGameResult_Defeat->setVisible(true);
			

			m_btnClearMenu.setVisible(true);
			if(m_btnClearMenu.CheckAction() == true)
			{
				/*Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
				auto scene = TransitionFade::create(1.0,StageScene::createScene());
				Director::getInstance()->replaceScene(scene);
				*/
				Delete();

				Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
				TransitionFade* scene = TransitionFade::create(1.0,StageScene::createScene());
				Director::getInstance()->replaceScene(scene);
				
				m_btnClearMenu.Reset();
			}

			m_btnClearRetry.setVisible(true);
			if(m_btnClearRetry.CheckAction() == true)
			{
				/*Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
				auto scene = TransitionFade::create(1.0,StageScene::createScene());
				Director::getInstance()->replaceScene(scene);
				*/
				Delete();

				Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
				TransitionFade* scene = TransitionFade::create(1.0,GameScene::createScene());
				Director::getInstance()->replaceScene(scene);

				m_btnClearRetry.Reset();
			}

		}
	}
	else if(g_bPause == true)
	{
		m_pBlind->setVisible(true);
		m_pPauseBg->setVisible(true);
		
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
		m_btnPause_Menu.setVisible(true);

		m_btnPause_Bg_Off.Update(dt);
		m_btnPause_Bg_On.Update(dt);
		m_btnPause_Close.Update(dt);
		m_btnPause_Effect_Off.Update(dt);
		m_btnPause_Effect_On.Update(dt);
		m_btnPause_Exit.Update(dt);
		m_btnPause_Menu.Update(dt);
		
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
			
			D_SOUNDMNG->playBackgroundMusic("BGM_GameScene.mp3");

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
			g_bPause = false;
			
			m_btnPause_Close.Reset();


			m_pBlind->setVisible(false);
			m_pPauseBg->setVisible(false);
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
			D_SOUNDMNG->stopBackgroundMusic();

			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			TransitionFade* scene = TransitionFade::create(1.0f,StageScene::createScene());
			Director::getInstance()->replaceScene(scene);

			//!< 게임종료
			m_btnPause_Menu.Reset();
		}
	}
}
void GameScene::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{
 
    //...
 
   /* for (auto iter = touches.begin(); iter != touches.end(); iter++){
		g_MousePoint.x = (*iter)->getLocation().x;
		g_MousePoint.y = (*iter)->getLocation().y;


    }*/
	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	
	if(g_bPause == false)
	{
		if(m_eGameStep == E_GAME_STEP_PLAY)
		{
			m_btnPause.TouchBegan(g_MousePoint);

			if(m_ePlayStep == E_PLAY_STEP_PLAY)
			{
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill.TouchBegan(g_MousePoint);
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_2.TouchBegan(g_MousePoint);

				m_btnSkill_3.TouchBegan(g_MousePoint);

				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_4.TouchBegan(g_MousePoint);
				//!< 선택된 블록찾기
				for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
				{
					if( g_BlockList[nBlock].m_bLive == false)
						continue;
					if( g_BlockList[nBlock].m_stIndex.m_nY == 0 )
						continue;
				
					if( g_BlockList[nBlock].m_eBlockNumber != E_BLOCKNUMBER_HERO )
						continue;
					if( g_BlockList[nBlock].HitTest(g_MousePoint.x, g_MousePoint.y) == true && g_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE_FALL_FALLING)
					{
							
						//!<******************* 주석처리필요 ***********************
						//g_BlockList[nBlock].m_pBlock->setScale(1.5f);


						//!< 첫번째 블록으로 지정
						m_stFirstBlockIdx = g_BlockList[nBlock].m_stIndex; 

						m_nFirstBlock = nBlock;
						//!< 다음 단계로
						m_ePlayStep = E_PLAY_STEP_DRAG;
						break;
					}
				}
			}
			else if(m_ePlayStep == E_PLAY_STEP_SKILL_1)
			{
				//!< 히어로 블록찾기
				for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
				{
					if( g_BlockList[nBlock].m_bLive == false)
						continue;
					if( g_BlockList[nBlock].m_stIndex.m_nY == 0 )
						continue;
					if( g_BlockList[nBlock].m_eBlockNumber != E_BLOCKNUMBER_HERO )
						continue;

						//!< 첫번째 블록으로 지정
						m_stFirstBlockIdx = g_BlockList[nBlock].m_stIndex; 
						m_nFirstBlock = nBlock;
						break;
				}

				//!< 선택된 블록찾기
				for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
				{
					if( g_BlockList[nBlock].m_bLive == false)
						continue;
					if( g_BlockList[nBlock].m_stIndex.m_nY == 0 )
						continue;
					if( g_BlockList[nBlock].m_eBlockNumber == E_BLOCKNUMBER_HERO )
						continue;
					if( g_BlockList[nBlock].HitTest(g_MousePoint.x, g_MousePoint.y) == true && g_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE_FALL_FALLING)
					{
						//!< 두번째 블록으로 지정
						m_stSecondBlockIdx = g_BlockList[nBlock].m_stIndex; 
						m_nSecondBlock = nBlock;

						CCPoint stTempPos;
						stVec2i stTempIdx;

					
					
						Explosion(ccp(g_BlockList[m_nSecondBlock].m_stPos.x,g_BlockList[m_nSecondBlock].m_stPos.y), g_BlockList[m_nSecondBlock].m_eBlockNumber);
						g_EffectManager.Insert((int)g_BlockList[m_nSecondBlock].m_eBlockNumber,g_BlockList[m_nSecondBlock].m_stPos.x,g_BlockList[m_nSecondBlock].m_stPos.y);
						if(g_BlockList[m_nSecondBlock].m_eBlockNumber == 0 || g_BlockList[m_nSecondBlock].m_eBlockNumber == 3)
						{
							fBasicScore = D_SCORE_POP * 2;	
						}
						else
						{
							fBasicScore = D_SCORE_POP;
						}

						g_NumberManager.Insert(  fBasicScore  , g_BlockList[m_nSecondBlock].m_stPos.x, g_BlockList[m_nSecondBlock].m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
						g_nScore += (int)(fBasicScore);
					

						stTempPos = g_BlockList[m_nFirstBlock].m_stPos;
						g_BlockList[m_nFirstBlock].m_stPos = g_BlockList[m_nSecondBlock].m_stPos;
						g_BlockList[m_nSecondBlock].m_stPos = stTempPos;

						stTempIdx = g_BlockList[m_nFirstBlock].m_stIndex;
						g_BlockList[m_nFirstBlock].m_stIndex = g_BlockList[m_nSecondBlock].m_stIndex;
						g_BlockList[m_nSecondBlock].m_stIndex = stTempIdx;

						g_BlockList[m_nSecondBlock].m_nHpNow = 0;
						if(efsound == true)
						{
							D_SOUNDMNG->playEffect("Sk1.mp3");
							D_SOUNDMNG->playEffect("Clear.mp3");
						}

						m_bSkill_1_Used = false;

						m_ePlayStep = E_PLAY_STEP_SKILL_POP;

						break;
					}
				}

			

			}
		}
		else if( m_eGameStep == E_GAME_STEP_END)
		{
			m_btnClearMenu.TouchBegan(g_MousePoint);
			m_btnClearRetry.TouchBegan(g_MousePoint);

		}
	}
	else if(g_bPause == true)
	{
		m_btnPause_Bg_Off.TouchBegan(g_MousePoint);
		m_btnPause_Bg_On.TouchBegan(g_MousePoint);
		m_btnPause_Close.TouchBegan(g_MousePoint);
		m_btnPause_Effect_Off.TouchBegan(g_MousePoint);
		m_btnPause_Effect_On.TouchBegan(g_MousePoint);
		m_btnPause_Exit.TouchBegan(g_MousePoint);
		m_btnPause_Menu.TouchBegan(g_MousePoint);
	}

 
    //...
 
}
 
void GameScene::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event)
{
	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	if(g_bPause == false)
	{
		if(m_eGameStep == E_GAME_STEP_PLAY)
		{
		
				m_btnPause.TouchMoved(g_MousePoint);
			if(m_ePlayStep == E_PLAY_STEP_PLAY)
			{
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill.TouchMoved(g_MousePoint);
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_2.TouchMoved(g_MousePoint);

				m_btnSkill_3.TouchMoved(g_MousePoint);
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_4.TouchMoved(g_MousePoint);
			}
			else if(m_ePlayStep == E_PLAY_STEP_DRAG)
			{
				//!< 선택된 블록찾기
					for(int nBlock = 0; nBlock < g_nBlockMax; nBlock++)
					{
						if( g_BlockList[nBlock].m_bLive == false)
							continue;
						if( g_BlockList[nBlock].m_stIndex.m_nY == 0 )
							continue;
						if( g_BlockList[nBlock].HitTest(g_MousePoint.x, g_MousePoint.y) == true && g_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE_FALL_FALLING)
						{
							//!< 오른쪽 블록인 경우
							if(g_BlockList[nBlock].m_stIndex.m_nX == m_stFirstBlockIdx.m_nX + 1 && g_BlockList[nBlock].m_stIndex.m_nY == m_stFirstBlockIdx.m_nY)
							{
								//!< 두번째 블록으로 지정
								m_stSecondBlockIdx = g_BlockList[nBlock].m_stIndex;
								m_nSecondBlock = nBlock;

								g_BlockList[m_nFirstBlock].m_fChangeDistance = D_BLOCK_WIDTH;
								g_BlockList[m_nSecondBlock].m_fChangeDistance = D_BLOCK_WIDTH;

								g_BlockList[m_nFirstBlock].m_eDerection = E_DERECTION_RIGHT;
								g_BlockList[m_nSecondBlock].m_eDerection = E_DERECTION_LEFT;


								//!< 다음 단계로
								m_ePlayStep = E_PLAY_STEP_CHANGE;
								break;
							}
							//!< 왼쪽
							else if(g_BlockList[nBlock].m_stIndex.m_nX == m_stFirstBlockIdx.m_nX - 1 && g_BlockList[nBlock].m_stIndex.m_nY == m_stFirstBlockIdx.m_nY)
							{
								//!< 두번째 블록으로 지정
								m_stSecondBlockIdx = g_BlockList[nBlock].m_stIndex;
								m_nSecondBlock = nBlock;

								g_BlockList[m_nFirstBlock].m_fChangeDistance = D_BLOCK_WIDTH;
								g_BlockList[m_nSecondBlock].m_fChangeDistance = D_BLOCK_WIDTH;

								g_BlockList[m_nFirstBlock].m_eDerection = E_DERECTION_LEFT;
								g_BlockList[m_nSecondBlock].m_eDerection = E_DERECTION_RIGHT;


								//!< 다음 단계로
								m_ePlayStep = E_PLAY_STEP_CHANGE;
								break;
							}
							//!< 위
							else if(g_BlockList[nBlock].m_stIndex.m_nX == m_stFirstBlockIdx.m_nX && g_BlockList[nBlock].m_stIndex.m_nY == m_stFirstBlockIdx.m_nY + 1)
							{
								//!< 두번째 블록으로 지정
								m_stSecondBlockIdx = g_BlockList[nBlock].m_stIndex;
								m_nSecondBlock = nBlock;

								g_BlockList[m_nFirstBlock].m_fChangeDistance = D_BLOCK_WIDTH;
								g_BlockList[m_nSecondBlock].m_fChangeDistance = D_BLOCK_WIDTH;

								g_BlockList[m_nFirstBlock].m_eDerection = E_DERECTION_UP;
								g_BlockList[m_nSecondBlock].m_eDerection = E_DERECTION_DOWN;


								//!< 다음 단계로
								m_ePlayStep = E_PLAY_STEP_CHANGE;
								break;
							}
							//!< 아래
							else if(g_BlockList[nBlock].m_stIndex.m_nX == m_stFirstBlockIdx.m_nX && g_BlockList[nBlock].m_stIndex.m_nY == m_stFirstBlockIdx.m_nY - 1)
							{
								//!< 두번째 블록으로 지정
								m_stSecondBlockIdx = g_BlockList[nBlock].m_stIndex;
								m_nSecondBlock = nBlock;

								g_BlockList[m_nFirstBlock].m_fChangeDistance = D_BLOCK_WIDTH;
								g_BlockList[m_nSecondBlock].m_fChangeDistance = D_BLOCK_WIDTH;

								g_BlockList[m_nFirstBlock].m_eDerection = E_DERECTION_DOWN;
								g_BlockList[m_nSecondBlock].m_eDerection = E_DERECTION_UP;


								//!< 다음 단계로
								m_ePlayStep = E_PLAY_STEP_CHANGE;
								break;
							}
							//
							//m_stFirstBlockIdx = g_BlockList[nBlock].m_stIndex; //!< 마지막 인덱스 저장 후 해당 블록들 전부 선택 표시
							//g_BlockList[nBlock].m_pBlock->setScale(1.5f);

							//m_stFirstBlock = nBlock;
							//m_ePlayStep = E_PLAY_STEP_DRAG;

						}
					}
			}
		}
		else if( m_eGameStep == E_GAME_STEP_END)
		{
			m_btnClearMenu.TouchMoved(g_MousePoint);
			m_btnClearRetry.TouchMoved(g_MousePoint);

		}
	}
	else if(g_bPause == true)
	{
		m_btnPause_Bg_Off.TouchMoved(g_MousePoint);
		m_btnPause_Bg_On.TouchMoved(g_MousePoint);
		m_btnPause_Close.TouchMoved(g_MousePoint);
		m_btnPause_Effect_Off.TouchMoved(g_MousePoint);
		m_btnPause_Effect_On.TouchMoved(g_MousePoint);
		m_btnPause_Exit.TouchMoved(g_MousePoint);
		m_btnPause_Menu.TouchMoved(g_MousePoint);
	}
}
 
void GameScene::onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event)
{

}
 
void GameScene::onTouchesEnded(const std::vector<Touch*>&touches, Event* unused_event)
{
	/*
	  for (auto iter = touches.begin(); iter != touches.end(); iter++){
		g_MousePoint.x = (*iter)->getLocation().x;
		g_MousePoint.y = (*iter)->getLocation().y;
    }*/

	g_MousePoint.x = (*touches.begin())->getLocation().x;
	g_MousePoint.y = (*touches.begin())->getLocation().y;

	if(g_bPause == false)
	{
		if(m_eGameStep == E_GAME_STEP_PLAY)
		{
			m_btnPause.TouchEnded(g_MousePoint);
			if(m_ePlayStep == E_PLAY_STEP_PLAY)
			{
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill.TouchEnded(g_MousePoint);
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_2.TouchEnded(g_MousePoint);
				m_btnSkill_3.TouchEnded(g_MousePoint);
				
				if( m_bSkill_1_Used == false && m_bSkill_2_Used == false && m_bSkill_4_Used == false)
					m_btnSkill_4.TouchEnded(g_MousePoint);
			}
			else if(m_ePlayStep == E_PLAY_STEP_DRAG)
			{
				m_ePlayStep = E_PLAY_STEP_PLAY;
			}
		}
		else if( m_eGameStep == E_GAME_STEP_END)
		{
			m_btnClearMenu.TouchEnded(g_MousePoint);
			m_btnClearRetry.TouchEnded(g_MousePoint);

		}
	}
	else if(g_bPause == true)
	{
		m_btnPause_Bg_Off.TouchEnded(g_MousePoint);
		m_btnPause_Bg_On.TouchEnded(g_MousePoint);
		m_btnPause_Close.TouchEnded(g_MousePoint);
		m_btnPause_Effect_Off.TouchEnded(g_MousePoint);
		m_btnPause_Effect_On.TouchEnded(g_MousePoint);
		m_btnPause_Exit.TouchEnded(g_MousePoint);
		m_btnPause_Menu.TouchEnded(g_MousePoint);
	}
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_INRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GameScene::CreateBlock(int nX, int nY)
{
	for(int i=0; i<g_nBlockMax; i++)
	{
		if(g_BlockList[i].m_bLive == true)
			continue;

		g_BlockList[i].Create(stVec2i(nX,nY));
		g_Map.m_nBlockMap[nY][nX] = 1;
		break;
	}
}

void GameScene::CreateLine()
{
	g_nNowLine++;
	for(int i=0; i<D_BLOCKMAP_WIDTH; i++)
	{
		if(g_nNowLine == 5 && i == 5)
		{
			for(int j=0; j<g_nBlockMax; j++)
			{
				if(g_BlockList[j].m_bLive == true)
					continue;

				g_BlockList[j].Create_Hero(stVec2i(i,0));
				m_nFirstBlock = j;
				g_nHeroIdx = j;
				g_Map.m_nBlockMap[0][i] = 1;
				break;
			}
		}
		else
			CreateBlock(i,0);
	}
}


void GameScene::Logic_StartLine(float dt)
{
	
	//!< 시작 라인 블록맵세로크기 - 1번을 m_fStartLineTime초 간격으로 내려오게 함 m_fStartLineTime는 개행시마다 일정정도 감소 점차 빠르게 내려오게 함
	if(m_nStartLineStep < D_BLOCKMAP_HEIGHT - 2)
	{
		m_fStartLineTimer += dt;
		if(m_fStartLineTimer >= m_fStartLineTime)
		{
			m_fStartLineTimer = 0.0f;
			m_fStartLineTime -= 0.04f;
			CreateLine();
			m_nStartLineStep++;
			
		}
	}
	if(m_nStartLineStep >= D_BLOCKMAP_HEIGHT - 2)
	{
		if(m_fReadyTimer >= 3.0f)
		{
			m_pReady->setVisible(false);
			m_pGo->setVisible(false);
			m_eGameStep = E_GAME_STEP_PLAY;
		}
	}
}
void GameScene::Logic_BlockUpdate(float dt)
{
	//!< 모든 블록 업데이트 갱신
	for(int i=0; i<g_nBlockMax; i++)
	{
		g_BlockList[i].Update(dt);
	}
}
void GameScene::Logic_BlockFall()
{
	int nBlock = 0; //!< 현재 포커싱된 블록
	//!< 모든 블록 낙하 로직 갱신
	for(nBlock = 0; nBlock < g_nBlockMax; nBlock++)
	{
		if(g_BlockList[nBlock].m_bLive == false)
			continue;
		/*if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			continue;*/
		if(g_BlockList[nBlock].m_bDraged == true)
			continue;
		if(g_BlockList[nBlock].m_stIndex.m_nY != D_BLOCKMAP_HEIGHT - 1)
		{
			if(g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] == 0)
			{
				if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
				{
					if(g_BlockList[nBlock].m_bFallFinished == true)
					{
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
						g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] = 1;


						//g_BlockList[nBlock].m_eBlockState = E_BLOCKSTATE_FALL_FALLING;
						g_BlockList[nBlock].m_fStartY = g_BlockList[nBlock].m_stPos.y;
						//g_BlockList[nBlock].m_stPos.y += g_BlockList[nBlock].m_fGPM;
						g_BlockList[nBlock].m_fDistance = g_BlockList[nBlock].m_fNextDistance;
						g_BlockList[nBlock].m_fNextDistance = D_BLOCK_HEIGHT;
						g_BlockList[nBlock].m_stIndex.m_nY += 1;
						g_BlockList[nBlock].m_bFallFinished = false;
					}
				}
				else if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_NONE)
				{
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY][g_BlockList[nBlock].m_stIndex.m_nX] = 0;
					g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] = 1;


					g_BlockList[nBlock].m_eBlockState = E_BLOCKSTATE_FALL_FALLING;
					//g_BlockList[nBlock].m_fGPM = 0.0f;
					g_BlockList[nBlock].m_fStartY = g_BlockList[nBlock].m_stPos.y;
					g_BlockList[nBlock].m_fDistance = g_BlockList[nBlock].m_fNextDistance;
					g_BlockList[nBlock].m_fNextDistance = D_BLOCK_HEIGHT;
					g_BlockList[nBlock].m_stIndex.m_nY += 1;
					g_BlockList[nBlock].m_bFallFinished = false;
				}
			}
			else if(g_Map.m_nBlockMap[g_BlockList[nBlock].m_stIndex.m_nY+1][g_BlockList[nBlock].m_stIndex.m_nX] == 1)
			{
				if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
				{
					if(g_BlockList[nBlock].m_bFallFinished == true)
					{
						g_BlockList[nBlock].m_fBouncePower		= (g_BlockList[nBlock].m_fSpeed - D_BLOCK_SPEED) * D_BLOCK_BOUNCE_HURISTIC;
						if(g_BlockList[nBlock].m_fBouncePower >= D_BLOCK_BOUNCE_FOWER)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
						if(g_BlockList[nBlock].m_fBouncePower <= D_BLOCK_BOUNCE_FOWER_LOW)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER_LOW;
						g_BlockList[nBlock].m_fSpeed			= D_BLOCK_SPEED;
						g_BlockList[nBlock].m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
						g_BlockList[nBlock].m_fNowDistance		= 0.0f;
						g_BlockList[nBlock].m_fDistance			= D_BLOCK_HEIGHT;
						//g_BlockList[nBlock].m_fGPM = 0.0f;
						g_BlockList[nBlock].m_nBounceLevel		= 1;
						g_BlockList[nBlock].m_fBounceLine		= g_BlockList[nBlock].m_stPos.y;
						
						g_BlockList[nBlock].m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
						
					}
				}
			}
		}
		else if(g_BlockList[nBlock].m_stIndex.m_nY == D_BLOCKMAP_HEIGHT - 1)
		{
			if(g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			{
				if(g_BlockList[nBlock].m_bFallFinished == true)
				{
					g_BlockList[nBlock].m_fBouncePower		= (g_BlockList[nBlock].m_fSpeed - D_BLOCK_SPEED) * D_BLOCK_BOUNCE_HURISTIC;
					if(g_BlockList[nBlock].m_fBouncePower >= D_BLOCK_BOUNCE_FOWER)
						g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
					if(g_BlockList[nBlock].m_fBouncePower <= D_BLOCK_BOUNCE_FOWER_LOW)
							g_BlockList[nBlock].m_fBouncePower = D_BLOCK_BOUNCE_FOWER_LOW;
					g_BlockList[nBlock].m_fSpeed			= D_BLOCK_SPEED;
					g_BlockList[nBlock].m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
					g_BlockList[nBlock].m_fNowDistance		= 0.0f;
					g_BlockList[nBlock].m_fDistance			= D_BLOCK_HEIGHT;
					//g_BlockList[nBlock].m_fGPM = 0.0f;
					g_BlockList[nBlock].m_nBounceLevel		= 1;
					g_BlockList[nBlock].m_fBounceLine		= g_BlockList[nBlock].m_stPos.y;
					g_BlockList[nBlock].m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
				}
			}
		}
		
	}
}

void GameScene::Logic_Pop()
{
	for(int nBlock=0; nBlock<g_nBlockMax; nBlock++)
	{
		g_BlockList[nBlock].CheckReset();
		
		/*if(g_BlockList[nBlock].m_stIndex.m_nY == 0) //!< 쌓여있는놈 지우기
		{
			g_BlockList[nBlock].Die();
		}*/
	}

	for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
	{
		m_bPoped[i] = false;
	}

	float m_fCenterX = 0.0f;
	float m_fCenterY = 0.0f;
	

	//for(int i=0; i<g_nBlockMax; i++)
	//{
	//	
	//}

	float fDmgV = 1.0f;
	float fBasicScore = 100.0f;




	for(int i=0; i<g_nTargetPopBlock.size(); i++)
	{
		if(g_BlockList[ g_nTargetPopBlock[i] ].m_bChecked == true) //!< 이미 포함한 녀석이면 지나감
			continue;

		if(g_BlockList[ g_nTargetPopBlock[i] ].m_bLive == false) //!< 죽어있는 녀석이면 지나감
			continue;

		if(g_BlockList[ g_nTargetPopBlock[i] ].m_stIndex.m_nY < 2) //!< 가장 윗줄에 있는 녀석이면 지나감
			continue;
		
			CPopList* pPopList = new CPopList();
			pPopList->Init( g_nTargetPopBlock[i] );

			//!< 진동설정

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	{
//		JniMethodInfo t;
//	/*
//	JniHelper를 통해 org/cocos2dx/application/에 있는 ApplicationDemo class의 JavaJniTestFunc함수 정보를 가져온다.
//	*/
//		if (JniHelper::getStaticMethodInfo(t
//			, "org/cocos2dx/lib/Cocos2dxActivity"
//			, "Vivrate_SHORT_BUZZ"
//			, "()V"))
//		{
//	///< 함수 호출
//			t.env->CallStaticVoidMethod(t.classID, t.methodID);
//	///< Release
//			t.env->DeleteLocalRef(t.classID);
//		}
//	}
//#endif
			m_fCenterX = 0.0f;
			m_fCenterY = 0.0f;
/*
			if(g_bFever == false)
				m_nPopBlockNumber = 4;
			else if (g_bFever == true)
				m_nPopBlockNumber = 3;
*/
			//printf("Logic_Pop Check1 Entered!\n");
			//!< m_nPopBlockNumber개수 이상이면 터짐
			if(pPopList->m_BlockList.size() >= m_nPopBlockNumber)
			{
				if(pPopList->m_BlockList.size() >= 2)
				{
					fDmgV = 1.0f + (((pPopList->m_BlockList.size()) - 2) * 0.5f);
				}
				else
				{
					fDmgV = 1.0f;
				}

				if(pPopList->m_BlockList[0]->m_eBlockNumber == 0 || pPopList->m_BlockList[0]->m_eBlockNumber == 3)
				{
					fBasicScore = D_SCORE_POP * 2;
				}
				else
				{
					fBasicScore = D_SCORE_POP;
				}

				//printf("Logic_Pop Poped Entered!\t");
				for(int i=0; i<pPopList->m_BlockList.size(); i++)
				{
					//g_Map.m_nBlockMap[pPopList->m_BlockList[i]->m_stIndex.m_nY][pPopList->m_BlockList[i]->m_stIndex.m_nX] = 0;
					//g_EffectManager.Insert(((int)pPopList->m_BlockList[i]->m_eBlockNumber) + 1,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y);
					// printf("(%d,%d) 블록 터트림\n",pPopList->m_BlockList[i]->m_stIndex.m_nY,pPopList->m_BlockList[i]->m_stIndex.m_nX);
				
					/*if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_LIGHTNING)
					{
						m_Item_Lightning.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_BOMB)
					{
						m_Item_Bomb.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_SPACE)
					{
						m_Item_Space.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}*/
					m_fCenterX += pPopList->m_BlockList[i]->m_stPos.x;
					m_fCenterY += pPopList->m_BlockList[i]->m_stPos.y;

					//if(g_bFever == true)
					//{
					//	if(i < m_nPopBlockNumber)
					//	{
					//		g_nScore += D_SCORE_POP;
					//	

					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
					//		}

					//	}
					//	else if(i >= m_nPopBlockNumber) //!< 5개째 부터
					//	{
					//		g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1)))) ;
					//	
					//	
					//	
					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//	}
					//}
					//if(g_bFever == false)
					//{
						//if(i < m_nPopBlockNumber)
						//{
						//	g_nScore += D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					


						//	if(g_nCombo == 0)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 1)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 2)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 3)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 4)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
						//	}
						//	else if(g_nCombo == 5)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
						//	}
						//	else
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
						//	}

						//}
						//else if(i >= m_nPopBlockNumber) //!< 5개째 부터
						//{
						//	g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					
					
					
						//	if(g_nCombo == 0)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 1)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 2)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 3)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 4)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 5)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//}
					//}
					
					pPopList->m_BlockList[i]->m_nHpNow -= (int) ((float)g_nHeroDamage * fDmgV); 

					if(pPopList->m_BlockList[i]->m_nHpNow <= 0)
					{
						g_Map.m_nBlockMap[pPopList->m_BlockList[i]->m_stIndex.m_nY][pPopList->m_BlockList[i]->m_stIndex.m_nX] = 0;
						pPopList->m_BlockList[i]->Die();
						Explosion(ccp(pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y), pPopList->m_BlockList[i]->m_eBlockNumber);
						g_EffectManager.Insert((int)pPopList->m_BlockList[i]->m_eBlockNumber,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y);
						
						m_bPoped[(int)pPopList->m_BlockList[i]->m_eBlockNumber] = true;

						if(i+1 > 2)
						{
							g_NumberManager.Insert(  fBasicScore * (1.0f + (0.25f * (i-1))) ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore * (1.0f + (0.25f * (i-1))));
						}
						else
						{
							g_NumberManager.Insert(  fBasicScore  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore);
						}

					}
				}

				m_fCenterX /= pPopList->m_BlockList.size();
				m_fCenterY /= pPopList->m_BlockList.size();

			/*	CDot* pTemp = new CDot(ccp(m_fCenterX,m_fCenterY));
				m_Block_PopPoint.push_back(pTemp);*/

			}

			pPopList->m_BlockList.clear();
			delete pPopList;
	}
	
	for(int i=0; i<g_nTargetPopBlock2.size(); i++)
	{
		if(g_BlockList[ g_nTargetPopBlock2[i] ] .m_bChecked == true) //!< 이미 포함한 녀석이면 지나감
			continue;

		if(g_BlockList[ g_nTargetPopBlock2[i] ] .m_bLive == false) //!< 죽어있는 녀석이면 지나감
			continue;

		if(g_BlockList[ g_nTargetPopBlock2[i] ] .m_stIndex.m_nY < 2) //!< 가장 윗줄에 있는 녀석이면 지나감
			continue;
		
			CPopList* pPopList = new CPopList();
			pPopList->Init( g_nTargetPopBlock2[i] );

			//!< 진동설정

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	{
//		JniMethodInfo t;
//	/*
//	JniHelper를 통해 org/cocos2dx/application/에 있는 ApplicationDemo class의 JavaJniTestFunc함수 정보를 가져온다.
//	*/
//		if (JniHelper::getStaticMethodInfo(t
//			, "org/cocos2dx/lib/Cocos2dxActivity"
//			, "Vivrate_SHORT_BUZZ"
//			, "()V"))
//		{
//	///< 함수 호출
//			t.env->CallStaticVoidMethod(t.classID, t.methodID);
//	///< Release
//			t.env->DeleteLocalRef(t.classID);
//		}
//	}
//#endif
			m_fCenterX = 0.0f;
			m_fCenterY = 0.0f;
/*
			if(g_bFever == false)
				m_nPopBlockNumber = 4;
			else if (g_bFever == true)
				m_nPopBlockNumber = 3;
*/
			//printf("Logic_Pop Check1 Entered!\n");
			//!< m_nPopBlockNumber개수 이상이면 터짐
			if(pPopList->m_BlockList.size() >= m_nPopBlockNumber)
			{
				if(pPopList->m_BlockList.size() >= 2)
				{
					fDmgV = 1.0f + (((pPopList->m_BlockList.size()) - 2) * 0.5f);
				}
				else
				{
					fDmgV = 1.0f;
				}

				if(pPopList->m_BlockList[0]->m_eBlockNumber == 0 || pPopList->m_BlockList[0]->m_eBlockNumber == 3)
				{
					fBasicScore = D_SCORE_POP * 2;
				}
				else
				{
					fBasicScore = D_SCORE_POP;
				}


				//printf("Logic_Pop Poped Entered!\t");
				for(int j=0; j<pPopList->m_BlockList.size(); j++)
				{
				
					/*if(g_BlockList[ g_nTargetPopBlock2[i] ].m_stIndex.m_nX == pPopList->m_BlockList[j]->m_stIndex.m_nX &&
						g_BlockList[ g_nTargetPopBlock2[i] ].m_stIndex.m_nY == pPopList->m_BlockList[j]->m_stIndex.m_nY )
					{
						continue;
					}*/
					//g_Map.m_nBlockMap[pPopList->m_BlockList[i]->m_stIndex.m_nY][pPopList->m_BlockList[i]->m_stIndex.m_nX] = 0;
					//g_EffectManager.Insert(((int)pPopList->m_BlockList[i]->m_eBlockNumber) + 1,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y);
					//Explosion(ccp(pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y), pPopList->m_BlockList[i]->m_eBlockNumber);
					// printf("(%d,%d) 블록 터트림\n",pPopList->m_BlockList[i]->m_stIndex.m_nY,pPopList->m_BlockList[i]->m_stIndex.m_nX);
				
					/*if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_LIGHTNING)
					{
						m_Item_Lightning.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_BOMB)
					{
						m_Item_Bomb.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}
					else if(pPopList->m_BlockList[i]->m_eBlockItem == E_BLOCKITEM_SPACE)
					{
						m_Item_Space.push_back(pPopList->m_BlockList[i]->m_stIndex);
					}*/
					m_fCenterX += pPopList->m_BlockList[i]->m_stPos.x;
					m_fCenterY += pPopList->m_BlockList[i]->m_stPos.y;

					//if(g_bFever == true)
					//{
					//	if(i < m_nPopBlockNumber)
					//	{
					//		g_nScore += D_SCORE_POP;
					//	

					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
					//		}

					//	}
					//	else if(i >= m_nPopBlockNumber) //!< 5개째 부터
					//	{
					//		g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1)))) ;
					//	
					//	
					//	
					//		if(g_nCombo == 0)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 1)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 2)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 3)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 4)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else if(g_nCombo == 5)
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//		else
					//		{
					//			g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  ,pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
					//		}
					//	}
					//}
					//if(g_bFever == false)
					//{
						//if(i < m_nPopBlockNumber)
						//{
						//	g_nScore += D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					


						//	if(g_nCombo == 0)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 1)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 2)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 3)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f));
						//	}
						//	else if(g_nCombo == 4)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f));
						//	}
						//	else if(g_nCombo == 5)
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f));
						//	}
						//	else
						//	{
						//		g_NumberManager.Insert(D_SCORE_POP * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f));
						//	}

						//}
						//else if(i >= m_nPopBlockNumber) //!< 5개째 부터
						//{
						//	g_nScore += (D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo));
					
					
					
						//	if(g_nCombo == 0)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 1)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,127 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 2)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 3)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.0f,255 * 1.0f, 255 * 0.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 4)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 0.3f,255 * 0.3f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else if(g_nCombo == 5)
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(124 * 1.0f,133 * 1.0f, 139 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//	else
						//	{
						//		g_NumberManager.Insert((D_SCORE_POP + (D_SCORE_POP_PLUS * (i-(m_nPopBlockNumber-1))))  * (1.0f + (D_SCORE_POP_COMBO * g_nCombo)),pPopList->m_BlockList[i]->m_stPos.x,pPopList->m_BlockList[i]->m_stPos.y,ccc3(255 * 1.0f,255 * 0.0f, 255 * 1.0f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f), 0.6f + ((i-(m_nPopBlockNumber-1)) * 0.15f));
						//	}
						//}
					//}
					
						pPopList->m_BlockList[j]->m_nHpNow -= (int) ((float)g_nHeroDamage * fDmgV); 

					if(pPopList->m_BlockList[j]->m_nHpNow <= 0)
					{
						g_Map.m_nBlockMap[pPopList->m_BlockList[j]->m_stIndex.m_nY][pPopList->m_BlockList[j]->m_stIndex.m_nX] = 0;
						pPopList->m_BlockList[j]->Die();
						Explosion(ccp(pPopList->m_BlockList[j]->m_stPos.x,pPopList->m_BlockList[j]->m_stPos.y), pPopList->m_BlockList[j]->m_eBlockNumber);
						g_EffectManager.Insert((int)pPopList->m_BlockList[j]->m_eBlockNumber,pPopList->m_BlockList[j]->m_stPos.x,pPopList->m_BlockList[j]->m_stPos.y);
						//g_NumberManager.Insert(D_SCORE_POP,pPopList->m_BlockList[j]->m_stPos.x,pPopList->m_BlockList[j]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
						
						m_bPoped[(int)pPopList->m_BlockList[i]->m_eBlockNumber] = true;

						if(j+1 > 2)
						{
							g_NumberManager.Insert(  fBasicScore * (1.0f + (0.25f * (j-1))) ,pPopList->m_BlockList[j]->m_stPos.x,pPopList->m_BlockList[j]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore * (1.0f + (0.25f * (j-1))));
						}
						else
						{
							g_NumberManager.Insert(  fBasicScore  ,pPopList->m_BlockList[j]->m_stPos.x,pPopList->m_BlockList[j]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
							g_nScore += (int)(fBasicScore);
						}
					}
				}

				m_fCenterX /= pPopList->m_BlockList.size();
				m_fCenterY /= pPopList->m_BlockList.size();

			/*	CDot* pTemp = new CDot(ccp(m_fCenterX,m_fCenterY));
				m_Block_PopPoint.push_back(pTemp);*/

			}

			pPopList->m_BlockList.clear();
			delete pPopList;
	}
	
	
	
	
	if(efsound == true)
	{		
		for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
		{
			if(m_bPoped[i] == true)
				D_SOUNDMNG->playEffect(StringUtils::format("Block_%d.mp3",i).c_str());
		}

		/*if(m_bPoped[0] == false &&
			m_bPoped[1] == false &&
			m_bPoped[2] == false &&
			m_bPoped[3] == false &&
			m_bPoped[4] == false &&
			m_bPoped[5] == false )
		{
			D_SOUNDMNG->playEffect(StringUtils::format("BlockPop_1.mp3").c_str());
		}*/
		D_SOUNDMNG->setEffectsVolume(0.7f);
		D_SOUNDMNG->playEffect(StringUtils::format("BlockPop_1.mp3").c_str());
		D_SOUNDMNG->setEffectsVolume(1.0f);
	}
	


/*
	if(m_Block_PopPoint.size() >= 5)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Pentagon.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 4)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Square.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 3)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Triangle.mp3");
		}
	}
	else if(m_Block_PopPoint.size() >= 2)
	{
		if(g_bEFFECT_Sound == true)
		{
			 
			D_SOUNDMNG->playEffect("Line.mp3");
		}
	}*/



	//if(m_Block_PopPoint.size() >= 2)
	//{
	//	for(int i=0; i<m_Block_PopPoint.size(); i++)
	//	{
	//		g_nScore += D_SCORE_LINE;
	//		g_NumberManager.Insert(D_SCORE_LINE ,m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y, ccc3(255 * 1.0f,255 * 1.0f, 255 * 1.0f),1.0f,1.0f);
	//	}
	//}

	//if(m_Block_PopPoint.size() >= 3)
	//{
	//	float fWidth = 0.0f;
	//	float fHeigjt = 0.0f;

	//	float fDistance = 0.0f;

	//	float fAngle = 0.0f;

	//	for(int i=0; i<m_Block_PopPoint.size()-1; i++)
	//	{
	//		fWidth = m_Block_PopPoint[i]->m_stPos.x - m_Block_PopPoint[i+1]->m_stPos.x;
	//		fHeigjt = m_Block_PopPoint[i]->m_stPos.y - m_Block_PopPoint[i+1]->m_stPos.y;

	//		fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
	//	

	//		fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
	//		//!< 선 긋기 
	//		g_EffectManager.Insert(7,m_Block_PopPoint[i]->m_stPos.x,m_Block_PopPoint[i]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);


	//	}

	//	fWidth = m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x - m_Block_PopPoint[0]->m_stPos.x;
	//	fHeigjt = m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y - m_Block_PopPoint[0]->m_stPos.y;

	//	fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
	//	

	//	fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
	//	//!< 선 긋기 
	//	g_LineManager.Insert(7,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.x,m_Block_PopPoint[m_Block_PopPoint.size()-1]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);
	//}
	//else if(m_Block_PopPoint.size() >= 2)
	//{
	//	float fWidth = 0.0f;
	//	float fHeigjt = 0.0f;

	//	float fDistance = 0.0f;

	//	float fAngle = 0.0f;
	//	
	//	fWidth = m_Block_PopPoint[0]->m_stPos.x - m_Block_PopPoint[1]->m_stPos.x;
	//	fHeigjt = m_Block_PopPoint[0]->m_stPos.y - m_Block_PopPoint[1]->m_stPos.y;

	//	fDistance = sqrt((fWidth*fWidth) + (fHeigjt*fHeigjt));
	//	

	//	fAngle = RadToDeg( atan2(fHeigjt, -fWidth) );
	//	g_LineManager.Insert(7,m_Block_PopPoint[0]->m_stPos.x,m_Block_PopPoint[0]->m_stPos.y,(fDistance / 200.0f),1.0f,fAngle);
	//}
	//m_fCenterX = 0.0f;
	//m_fCenterY = 0.0f;

	//if(m_Block_PopPoint.size() == 1)
	//{
	//	if(m_Block_PopPoint[0]->m_bItem == true)
	//	{

	//	}
	//	else if(m_Block_PopPoint[0]->m_bItem == false)
	//	{
	//		for(int i=0; i<m_Block_PopPoint.size(); i++)
	//		{
	//			g_LineManager.Insert(8,m_Block_PopPoint[i]->m_stPos.x ,m_Block_PopPoint[i]->m_stPos.y);
	//	
	//			m_fCenterX += m_Block_PopPoint[i]->m_stPos.x;
	//			m_fCenterY += m_Block_PopPoint[i]->m_stPos.y;

	//		}
	//	}
	//}
	//else
	//{
	//	for(int i=0; i<m_Block_PopPoint.size(); i++)
	//	{
	//		g_LineManager.Insert(8,m_Block_PopPoint[i]->m_stPos.x ,m_Block_PopPoint[i]->m_stPos.y);
	//	
	//		m_fCenterX += m_Block_PopPoint[i]->m_stPos.x;
	//		m_fCenterY += m_Block_PopPoint[i]->m_stPos.y;

	//	}
	//}
	//m_fCenterX /= m_Block_PopPoint.size();
	//m_fCenterY /= m_Block_PopPoint.size();

	//if(m_Block_PopPoint.size() == 1)
	//{
	//	if(m_Block_PopPoint[0]->m_bItem == true)
	//	{

	//	}
	//	else if(m_Block_PopPoint[0]->m_bItem == false)
	//	{
	//		g_PlaneManager.Insert(m_Block_PopPoint.size(),m_fCenterX,m_fCenterY);
	//	}
	//}
	//else
	//{
	//	g_PlaneManager.Insert(m_Block_PopPoint.size(),m_fCenterX,m_fCenterY);
	//}

	/*for(int i=0; i<m_Block_PopPoint.size(); i++)
	{
		delete m_Block_PopPoint[i];
	}

	m_Block_PopPoint.clear();*/


	// printf("점수 %d , 콤보 %d\b",g_nScore,g_nCombo);
	//printf("Logic_Pop End Entered!\n");
	
}



bool GameScene::FillBlockEnd()
{
	int nNumber = 0;
	int nBlock = 0;
	for(int y=2; y<D_BLOCKMAP_HEIGHT; y++)
	{
		for(int x=0; x<D_BLOCKMAP_WIDTH; x++)
		{
			if(g_Map.m_nBlockMap[y][x] == 1)
			{
				nNumber++;
			}
		}
	}
	if(nNumber < g_nBlockMax - (D_BLOCKMAP_WIDTH * 2))
		return false;
	else
	{
		for(nBlock=0; nBlock<g_nBlockMax; nBlock++)
		{
			if(g_BlockList[nBlock].m_stIndex.m_nY < 2)
			{
				continue;
			}
			if(g_BlockList[nBlock].m_bLive == true && g_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE_FALL_FALLING)
			{
				return false;
			}
			if(g_BlockList[nBlock].m_bLive == true && g_BlockList[nBlock].m_nBounceLevel > 0)
			{
				return false;
			}
		}
		return true;
	}
}
void GameScene::FillBlockCheck()
{
	for(int y=2; y<D_BLOCKMAP_HEIGHT; y++)
	{
		for(int x=0; x<D_BLOCKMAP_WIDTH; x++)
		{
			if(g_Map.m_nBlockMap[y][x] == 0)
			{
				CreateBlock(x,0);
				// printf("(%d,%d) 블록 채워짐\n",x,y);
			}
		}
	}
	
}



void GameScene::Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber)
{

	

	CCParticleSystem *emitter3;
	emitter3 = CCParticleSun::create();
	emitter3->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
	emitter3->setTotalParticles(9);
	//!< 주의 다시 메모리 해제해주는 방법 찾을것
	emitter3->setAutoRemoveOnFinish(true);
	emitter3->setLife(1.5f);
	emitter3->setLifeVar(0.0f);
	emitter3->setPosition(ccp( CPos.x * D_SCALE_WIDTH, CPos.y * D_SCALE_HEIGHT));
	emitter3->setGravity(ccp(0,0));
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter3->setScale(1.0f);
	emitter3->setStartSize(16.0f);
	emitter3->setStartSizeVar(4.0f);
	emitter3->setEndSize(16.0f);
	emitter3->setEndSizeVar(4.0f);
	emitter3->setDuration(1.5f);
	emitter3->setSpeed(160);
	emitter3->setSpeedVar(0);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter3->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
	switch(eBlockNumber)
	{
	case E_BLOCKNUMBER_RED:
		emitter3->setStartColor(ccc4f((1.0f/255) * 176, (1.0f/255) * 221, (1.0f/255) * 81, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 176, (1.0f/255) * 221, (1.0f/255) * 81, 0.0f));
		break;
	case E_BLOCKNUMBER_YELLOW:
		emitter3->setStartColor(ccc4f((1.0f/255) * 187, (1.0f/255) * 187, (1.0f/255) * 187, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 187, (1.0f/255) * 187, (1.0f/255) * 187, 0.0f));
		break;
	case E_BLOCKNUMBER_BLUE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 62, (1.0f/255) * 198, (1.0f/255) * 255, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 62, (1.0f/255) * 198, (1.0f/255) * 255, 0.0f));
		break;
	case E_BLOCKNUMBER_GREEN:
		emitter3->setStartColor(ccc4f((1.0f/255) * 89, (1.0f/255) * 122, (1.0f/255) * 18, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 89, (1.0f/255) * 122, (1.0f/255) * 18, 0.0f));
		break;
	case E_BLOCKNUMBER_PURPLE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 148, (1.0f/255) * 8, (1.0f/255) * 7, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 148, (1.0f/255) * 8, (1.0f/255) * 7, 0.0f));
		break;
	case E_BLOCKNUMBER_ORANGE:
		emitter3->setStartColor(ccc4f((1.0f/255) * 20, (1.0f/255) * 92, (1.0f/255) * 6, 1.0f));
		emitter3->setEndColor(ccc4f((1.0f/255) * 20, (1.0f/255) * 92, (1.0f/255) * 6, 0.0f));
		break;
	}
	this->addChild(emitter3,23);

	//stParticleTimer* stTempTimer = new stParticleTimer(1.5f + ((float)(rand()%300) / 100.0f),0.0f,emitter3);


	//m_ParticleList.push_back(stTempTimer);

	
}

void GameScene::Delete()
{
	for(int i=0; i<g_nBlockMax; i++)
	{
		g_BlockList[i].Exit();
	}
	
}