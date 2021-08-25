#pragma once
#include "stdafx.h"

using namespace std;
USING_NS_CC;

//!< 백노연 2014. 05. 15 작성
//!< 스프라이트 애니메이션 클래스

class BAnimation
{
	
private:
	vector<CCSprite*> m_pList;
	//!< 등록할 현재 씬
	CCLayer* m_pThisScene;
	//!< 등록할 레이어
	int m_nLayer; 

	//!< 포지션
	CCPoint m_stPos;

	//!< 다음 장으로 넘어가는 시간
	float m_fDurationTime;
	//!< 다음 장으로 넘어가는 시간(타이머)
	float m_fDurationTimer;

	//!< 일시정지
	bool m_bPause;

	//!< 현재 프레임
	int m_nCurrentFrame;

	//!< 가시성
	bool m_bVisible;
	//!< 각도
	float m_fRotation;

	//!< 스케일
	float m_fScale;

	//!< 한번재생여부
	bool m_bFrameOnce;


public: 
	//!< 이하 기본 클래스 메서드
	void Init(CCLayer* pThisScene, int nIndex, int nLayer, CCPoint stPos, float fDurationTime);
	void Update(float dt);
	void Exit();

	
	//!< 고유 인덱스
	int m_nIndex;

	//!< 전체 재생시간
	float m_fTimer;
	
public:
	//!< 이하 스프라이트 애니메이션 메서드
	//!< 스프라이트 추가 vector에 push_back으로 보관합니다.
	void Insert(string strFilePath);
public:
	//!< 이하 기능 메서드

	void setDuration(float fDurationTime);
	float getDuration();

	void setPause(bool bPause);
	bool getPause();

	void setPosition(CCPoint stPos);
	CCPoint getPosition();

	void setCurrentFrame(int nCurrentFrame);
	int getCurrentFrame();

	void setVisible(bool bVisible);
	bool getVisible();

	void setRotation(float fRotation);
	float getRotation();
	
	void setAnchorPoint(float fX, float fY);

	void setScale(float fScale);
	float getScale();

	//!< 한번의 재생을 끝마친 경우
	bool getFrameOnce();
	
	//!< 한번의 재생을 끝마친 경우 값 초기화
	void setFrameOnceReset();

private:
	//!< 이하 내부 메서드
	void ChangeSprite();
	
};