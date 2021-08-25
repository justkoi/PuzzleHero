﻿#include "stdafx.h"

using namespace cocos2d;

typedef enum _m_eButtonState
{
	E_BUTTON_WAIT,
	E_BUTTON_OVERING,
	E_BUTTON_IMAGEMAX,
}eButtonState;

typedef struct _rect
{
	float m_fWidth;
	float m_fHeight;
}stRect;

//!< Style1 : WindRenner Button

class BStyleButton
{
private:
	CCLayer* m_pThisScene;
	stRect	m_CHitRect[E_BUTTON_IMAGEMAX];
	int m_nLayer;
	// float m_fSizeX; //!< Is Scale
	// float m_fSizeY; //!< Is Scale

	eButtonState m_eState;

	//!< Special Scale
	float m_fScale;
	float m_fTargetScale;
	float m_fScaleMin;
	float m_fScaleMax;
	float m_fDtValue;

	bool m_bActioned;
	bool m_bPauseUpdate;

	bool m_bVisible;

	bool m_Sync;//!< 동기화 옵션 true시 기존 버튼 false시 사용자가 임의로 이미지 지정필요

public:
	CCSprite* m_pButtonImage[E_BUTTON_IMAGEMAX];

	bool m_bTouched;
	float m_fSpecScale;

	CCPoint m_CPoint;
	
	void Init(CCLayer* pThisScene, int nLayer, const char * m_pButtonImage_wait, const char * m_pButtonImage_overing, CCPoint CPoint,float fSpecScale, float fScaleMax = 1.0f, float fScaleMin = 0.8f, float fDtValue = 1.0f);

	void Update(float dt);

	void Exit();
	void setPositionY(float fPosY);

	bool CheckAction()
	{
		if(m_bPauseUpdate == true)
			return false;

		return m_bActioned;
	}
	void CheckActioned()
	{
		m_bPauseUpdate = true;
	}
public:

	bool TouchBegan(CCPoint stPos);
	void TouchEnded(CCPoint stPos);
	bool TouchMoved(CCPoint stPos);


public:
	void setVisible(bool bVisible)
	{
		m_bVisible = bVisible;

		if(m_Sync == false)
			return;

		//for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
		//{
		
		if(m_bVisible == false)
		{

			if(m_eState == E_BUTTON_WAIT)
			{
				m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			}
			else if(m_eState == E_BUTTON_OVERING)
			{
				m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
			}
			m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		}
		else if(m_bVisible == true)
		{
			if(m_eState == E_BUTTON_WAIT)
			{
				m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			}
			else if(m_eState == E_BUTTON_OVERING)
			{
				m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
			}
		}
		//}
	}
	void setColor(ccColor3B ccc3)
	{
		for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
		{
			m_pButtonImage[i]->setColor(ccc3);
		}
	}
	void setSync(bool bSync)
	{
		m_Sync = bSync;
	}
public:
	void Reset();

	void ChangeState(eButtonState eState);

};