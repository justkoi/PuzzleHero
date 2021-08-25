#include "stdafx.h"


void BStyleButton::Init(CCLayer* pThisScene, int nLayer, const char * m_pButtonImage_wait, const char * m_pButtonImage_overing, CCPoint CPoint,float fSpecScale, float fScaleMax, float fScaleMin, float fDtValue)
{
	m_pThisScene = pThisScene;
	m_nLayer = nLayer;
	m_CPoint = CPoint;

	m_eState = E_BUTTON_WAIT;
	m_fScale = fScaleMax;
	m_fScaleMin = fScaleMin;
	m_fScaleMax = fScaleMax;
	m_fTargetScale = fScaleMin;
	m_fDtValue = fDtValue;
	m_bPauseUpdate = false;
	m_bVisible = true;
	m_Sync = true;

	m_fSpecScale = fSpecScale;


	m_pButtonImage[E_BUTTON_WAIT] = CCSprite::create(m_pButtonImage_wait);
	m_pButtonImage[E_BUTTON_WAIT]->setPosition( m_CPoint );

	//!< 자동 해상도 지원(주석처리)

	m_pButtonImage[E_BUTTON_WAIT]->setScaleX(m_fScaleMax * m_fSpecScale);
	m_pButtonImage[E_BUTTON_WAIT]->setScaleY(m_fScaleMax * m_fSpecScale);

    pThisScene->addChild(m_pButtonImage[E_BUTTON_WAIT], nLayer);
	m_CHitRect[E_BUTTON_WAIT].m_fWidth = m_pButtonImage[E_BUTTON_WAIT]->getTextureRect().getMaxX() * m_fSpecScale;// * D_SCALE_WIDTH;
	m_CHitRect[E_BUTTON_WAIT].m_fHeight = m_pButtonImage[E_BUTTON_WAIT]->getTextureRect().getMaxY() * m_fSpecScale;// * D_SCALE_HEIGHT;
	
	m_pButtonImage[E_BUTTON_OVERING] = CCSprite::create(m_pButtonImage_overing);
	m_pButtonImage[E_BUTTON_OVERING]->setPosition( m_CPoint );
	
	//!< 자동 해상도 지원(주석처리)

	m_pButtonImage[E_BUTTON_OVERING]->setScaleX(m_fScaleMax * m_fSpecScale); //!< 원본 m_fScaleMax * D_SCALE_WIDTH
	m_pButtonImage[E_BUTTON_OVERING]->setScaleY(m_fScaleMax * m_fSpecScale); //!< 원본 m_fScaleMax * D_SCALE_HEIGHT

    pThisScene->addChild(m_pButtonImage[E_BUTTON_OVERING], nLayer);
	m_CHitRect[E_BUTTON_OVERING].m_fWidth = m_pButtonImage[E_BUTTON_OVERING]->getTextureRect().getMaxX() * m_fSpecScale;// * D_SCALE_WIDTH;
	m_CHitRect[E_BUTTON_OVERING].m_fHeight = m_pButtonImage[E_BUTTON_OVERING]->getTextureRect().getMaxY() * m_fSpecScale;// * D_SCALE_HEIGHT;
	
	//m_bTouched = false;
	m_bActioned = false;
	ChangeState(E_BUTTON_WAIT);
}

void BStyleButton::setPositionY(float fPosY)
{
	m_CPoint.y = fPosY;
	for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
	{
		m_pButtonImage[i]->setPositionY(m_CPoint.y);
	}
}
void BStyleButton::ChangeState(eButtonState eState)
{
	m_eState = eState;

	

	if(m_eState == E_BUTTON_WAIT)
	{
		if(m_Sync == true)
		{
			m_pButtonImage[E_BUTTON_WAIT]->setVisible(true);
			m_pButtonImage[E_BUTTON_OVERING]->setVisible(false);
		}
		m_fTargetScale = m_fScaleMax;
	}
	else if(m_eState == E_BUTTON_OVERING)
	{
		if(m_Sync == true)
		{
			m_pButtonImage[E_BUTTON_WAIT]->setVisible(false);
			m_pButtonImage[E_BUTTON_OVERING]->setVisible(true);
		}
		m_fTargetScale = m_fScaleMin;
	}
}
void BStyleButton::Update(float dt)
{
	if(m_bPauseUpdate == true)
		return;

	if(m_bActioned == false)
	{
		if(m_eState == E_BUTTON_WAIT)
		{
			if(m_fScale < m_fTargetScale)
			{
				//!< 눌렀다 떌대 효과
				//!< 요 밑부분을 주석걸면 효과 없음
				////////////////////////////
				m_fScale += dt * m_fDtValue;
				if(m_fScale >= m_fTargetScale)
				{
					m_fScale = m_fTargetScale;
				}
				//////////////////////////
			}
		}
		else if(m_eState == E_BUTTON_OVERING)
		{
			if(m_fScale > m_fTargetScale)
			{
				//!< 눌렀다 떌대 효과
				//!< 요 밑부분을 주석걸면 효과 없음
				////////////////////////////
				m_fScale -= dt * m_fDtValue;
				if(m_fScale <= m_fTargetScale)
				{
					m_fScale = m_fTargetScale;
				}
				//////////////////////////
			}
		}
	}
	//!< 자동 해상도 지원(주석처리)

	for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
	{
		m_pButtonImage[i]->setScaleX(m_fScale * m_fSpecScale); //!< 원본 m_fScaleMax * D_SCALE_WIDTH
		m_pButtonImage[i]->setScaleY(m_fScale * m_fSpecScale); //!< 원본 m_fScaleMax * D_SCALE_HEIGHT
	}

}

void BStyleButton::Exit()
{

}


bool BStyleButton::TouchBegan(CCPoint stPos)
{
	//!< 원형충돌
	float fLine = sqrt(((stPos.x - m_CPoint.x)*(stPos.x - m_CPoint.x)) + ((stPos.y- m_CPoint.y)*(stPos.y- m_CPoint.y)));

	if(m_bPauseUpdate == true)
		return false;
	if(m_bVisible == false)
		return false;
	//!< 주석부분은 사각형충돌
	/*if(stPos.x >= m_CPoint.x - (m_CHitRect[m_eState].m_fWidth/2) && stPos.x <= m_CPoint.x +  (m_CHitRect[m_eState].m_fWidth/2) &&
		stPos.y <= m_CPoint.y + (m_CHitRect[m_eState].m_fHeight/2) && stPos.y >= m_CPoint.y - (m_CHitRect[m_eState].m_fHeight/2)  )
	{*/
	if(fLine <= m_CHitRect[m_eState].m_fWidth/2)
	{
		if(efsound == true)		
			D_SOUNDMNG->playEffect("Select.mp3");
		ChangeState(E_BUTTON_OVERING);
		m_bTouched = true;
		/*for(int i=0; i<E_BUTTON_IMAGEMAX; i++)
		{
			m_pButtonImage[i]->setOpacity(255 * 0.5f);
		}*/
		return true;
	}
}

bool BStyleButton::TouchMoved(CCPoint stPos)
{
	//!< 원형충돌
	float fLine = sqrt(((stPos.x - m_CPoint.x)*(stPos.x - m_CPoint.x)) + ((stPos.y- m_CPoint.y)*(stPos.y- m_CPoint.y)));

	if(m_bPauseUpdate == true)
		return false;
	if(m_bVisible == false)
		return false;
	if(fLine <= m_CHitRect[m_eState].m_fWidth/2)
	{
		return true;
	}
}
void BStyleButton::TouchEnded(CCPoint stPos)
{
	//!< 원형충돌
	float fLine = sqrt(((stPos.x - m_CPoint.x)*(stPos.x - m_CPoint.x)) + ((stPos.y- m_CPoint.y)*(stPos.y- m_CPoint.y)));

	if(m_bPauseUpdate == true)
		return;
	if(m_bVisible == false)
		return;
	//!< 주석부분은 사각형충돌
	/*if(stPos.x >= m_CPoint.x - (m_CHitRect[m_eState].m_fWidth/2) && stPos.x <= m_CPoint.x +  (m_CHitRect[m_eState].m_fWidth/2) &&
		stPos.y <= m_CPoint.y + (m_CHitRect[m_eState].m_fHeight/2) && stPos.y >= m_CPoint.y - (m_CHitRect[m_eState].m_fHeight/2)  )
	{*/
	if(fLine <= m_CHitRect[m_eState].m_fWidth/2)
	{
		
		if(m_eState == E_BUTTON_OVERING)
			m_bActioned = true;
		ChangeState(E_BUTTON_WAIT);
		//ChangeState(E_BUTTON_OVERING);
	}
	else
	{
		ChangeState(E_BUTTON_WAIT);
	}
}
void BStyleButton::Reset()
{
	m_bActioned = false;
	ChangeState(E_BUTTON_WAIT);
}