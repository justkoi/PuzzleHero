#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__

#include "stdafx.h"

USING_NS_CC;

class StageScene : public LayerColor
{
public:
	
	//!< 일시정지 화면
	CCSprite* m_pPauseBg_1;
	//!< 일시정지 화면
	CCSprite* m_pPauseBg_2;

	
	BStyleButton m_btnPause;

	BStyleButton m_btnNext;
	BStyleButton m_btnProfile;

	BStyleButton m_btnPause_Bg_On;
	BStyleButton m_btnPause_Bg_Off;
	BStyleButton m_btnPause_Effect_On;
	BStyleButton m_btnPause_Effect_Off;
	BStyleButton m_btnPause_Exit;
	BStyleButton m_btnPause_Close;
	BStyleButton m_btnPause_Credit;
	BStyleButton m_btnPause_Menu;

	static Scene* createScene();
	
	virtual bool init();
	Point MousePoint;
	int stagenum;
	int sw;
	int optionsw;
	CREATE_FUNC(StageScene);
	void Update(float delta);
	
	virtual void onTouchesBegan(const std::vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>&touches, Event *unused_event);

	void setCredit();
	void setOption();
	void changeScene();
};

#endif