#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "stdafx.h"

USING_NS_CC;

typedef enum _E_GAME_STEP
{
	E_GAME_STEP_READY,
	E_GAME_STEP_PLAY,
	E_GAME_STEP_END,
}E_GAME_STEP;


typedef enum
{
	E_PLAY_STEP_PLAY,
	E_PLAY_STEP_DRAG,
	E_PLAY_STEP_CHANGE,
	E_PLAY_STEP_POP,
	E_PLAY_STEP_SKILL_POP,
	E_PLAY_STEP_FALL,
	E_PLAY_STEP_POPSET,
	E_PLAY_STEP_POPSET_2,
	E_PLAY_STEP_SKILL_1,
	E_PLAY_STEP_SKILL_2,
	E_PLAY_STEP_SKILL_3,
	E_PLAY_STEP_SKILL_4

}E_PLAY_STEP;

typedef enum
{
	E_GAME_RESULT_NONE,
	E_GAME_RESULT_VICTORY,
	E_GAME_RESULT_DEFEAT,

}E_GAME_RESULT;


class GameScene : public cocos2d::Layer
{
public:
	//!< 게임진행단계
	E_GAME_STEP m_eGameStep;
	//!< 게임 플레이 진행 단계
	E_PLAY_STEP m_ePlayStep;
	//!< 게임 결과
	E_GAME_RESULT m_eGameResult;
	
	float m_fTimer;

	//!< 내려오는 시작 줄 수
	int m_nStartLineStep; 
	//!< 내려오는 시작 줄 타이머
	float m_fStartLineTimer;
	//!< 내려오는 시작 줄 도달시간
	float m_fStartLineTime;
	//!< ReadyTimer
	float m_fReadyTimer; 

	float m_fPopSetTimer;

	stVec2i m_stFirstBlockIdx;
	stVec2i m_stSecondBlockIdx;

	int m_nFirstBlock;
	int m_nSecondBlock;

	bool m_bPoped[E_BLOCKNUMBER_MAX];
	int m_nPopBlockNumber;


	CCSprite* m_pBoard;
	CCSprite* m_pBlind;

	CCSprite* m_pGameResult_Clear;
	CCSprite* m_pGameResult_Defeat;
	
	CCSprite* m_pScore;
	
	CCSprite* m_pStatus;
	
	CCSprite* m_pBar_1;

	CCSprite* m_pHpBar_1;
	CCSprite* m_pMpBar_1;
	CCSprite* m_pStarBar_1;

	BStyleButton m_btnSkill;
	BStyleButton m_btnSkill_2;
	BStyleButton m_btnSkill_3;
	BStyleButton m_btnSkill_4;

	BStyleButton m_btnPause;
	
	//!< 클리어 상황
	BStyleButton m_btnClearMenu;
	BStyleButton m_btnClearRetry;
	
	//!< 일시정지 화면
	CCSprite* m_pPauseBg;
	BStyleButton m_btnPause_Bg_On;
	BStyleButton m_btnPause_Bg_Off;
	BStyleButton m_btnPause_Effect_On;
	BStyleButton m_btnPause_Effect_Off;
	BStyleButton m_btnPause_Exit;
	BStyleButton m_btnPause_Close;
	BStyleButton m_btnPause_Menu;
	
	LabelTTF* m_labelTime;
	LabelTTF* m_labelScore;
	
	bool m_bSkill_1_Used;
	bool m_bSkill_2_Used;
	bool m_bSkill_4_Used;

	
	CCSprite* m_pReady; //!< Ready Sprite
	CCSprite* m_pGo; //!< Go Sprite

	GameScene()
	{

	}

	BNumber m_numberScore;
	BNumber m_numberScore_Target;

	BNumber m_numberTime;

	int m_nTargetScore;
	
public:
	void SetMsg();
	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void Delete();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


	
	void Update(float dt);

	//virtual void onEnter();

	//!< 터치함수 정의

	virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);


	//virtual void  registerWithTouchDispatcher();
	/*
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
    */
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
public:
	
	void Logic_StartLine(float dt);
	void Logic_BlockUpdate(float dt);
	void Logic_BlockFall();
	void Logic_Pop();
	
	bool FillBlockEnd();
	void FillBlockCheck();
	
	void CreateBlock(int nX, int nY);
	void CreateLine();

	void Explosion(CCPoint CPos, E_BLOCKNUMBER eBlockNumber);
};

#endif // __GameScene_SCENE_H__
