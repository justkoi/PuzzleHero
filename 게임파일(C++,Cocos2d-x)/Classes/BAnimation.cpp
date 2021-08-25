#include "stdafx.h"

void BAnimation::Init(CCLayer* pThisScene,int nIndex, int nLayer, CCPoint stPos, float fDurationTime)
{
	m_pThisScene = pThisScene;
	m_nLayer = nLayer;
	m_stPos = stPos;
	m_fDurationTime = fDurationTime;
	m_bPause = false;
	m_fDurationTimer = 0.0f;
	m_nCurrentFrame = 1;
	m_bFrameOnce = false;
	m_nIndex = nIndex;
	m_fTimer = 0.0f;

	/*auto sprite = Sprite::create("StageMenu_1.png");
    sprite->setPosition(Point(400,240));
	sprite->setRotation(90.0f);
    this->addChild(sprite, 0);*/
}

void BAnimation::Update(float dt)
{
	if(m_bPause == true)
		return;

	m_fDurationTimer += dt;
	m_fTimer += dt;

	if(m_fDurationTimer > m_fDurationTime)
	{
		m_fDurationTimer -= m_fDurationTime;
		m_nCurrentFrame++;
		if(m_nCurrentFrame > m_pList.size())
		{
			m_bFrameOnce = true;
			m_nCurrentFrame = 1;
		}
		ChangeSprite();
	}
	

	setPosition(m_stPos);
}


void BAnimation::Exit()
{
	vector<CCSprite*>::iterator itr;
	for(itr = m_pList.begin(); itr != m_pList.end();)
	{
		m_pThisScene->removeChild((*itr),true);
//s		delete (*itr);
		itr = m_pList.erase(itr);
	}
}

void BAnimation::Insert(string strFilePath)
{
	if(strFilePath.size() == NULL)
		return;

	Sprite* pSprite = Sprite::create(strFilePath);
	pSprite->setVisible(false);
	m_pThisScene->addChild(pSprite,m_nLayer);

	m_pList.push_back(pSprite);
}

void BAnimation::setDuration(float fDurationTime)
{
	m_fDurationTime = fDurationTime;
}

float BAnimation::getDuration()
{
	return m_fDurationTime;
}

void BAnimation::setPause(bool bPause)
{
	m_bPause = bPause;
}
bool BAnimation::getPause()
{
	return m_bPause;
}

void BAnimation::setPosition(CCPoint stPos)
{
	m_stPos = stPos;

	vector<CCSprite*>::iterator it;

	for(it = m_pList.begin(); it != m_pList.end(); it++)
	{
		(*it)->setPosition(m_stPos.x,m_stPos.y);
	}
}


void BAnimation::setScale(float fScale)
{
	m_fScale = fScale;

	vector<CCSprite*>::iterator it;

	for(it = m_pList.begin(); it != m_pList.end(); it++)
	{
		(*it)->setScale(m_fScale);
	}
}

float BAnimation::getScale()
{
	return m_fScale;
}

CCPoint BAnimation::getPosition()
{
	return m_stPos;
}

void BAnimation::setCurrentFrame(int nCurrentFrame)
{
	if(nCurrentFrame <= 0 || nCurrentFrame > m_pList.size())
		return;
	m_nCurrentFrame = nCurrentFrame;
	ChangeSprite();
	m_fDurationTimer = 0.0f;
}

int BAnimation::getCurrentFrame()
{
	return m_nCurrentFrame;
}

void BAnimation::ChangeSprite()
{
	vector<CCSprite*>::iterator it;
	int nFrame = 1;

	for(it = m_pList.begin(); it != m_pList.end(); it++, nFrame++)
	{
		if(nFrame == m_nCurrentFrame)
			(*it)->setVisible(true);
		else
			(*it)->setVisible(false);
	}
}

bool BAnimation::getVisible()
{
	return m_bVisible;
}

void BAnimation::setVisible(bool bVisible)
{
	m_bVisible = bVisible;

	vector<CCSprite*>::iterator it;
	int nFrame = 1;

	for(it = m_pList.begin(); it != m_pList.end(); it++, nFrame++)
	{
		if(nFrame == m_nCurrentFrame)
			(*it)->setVisible(bVisible);
		else
			(*it)->setVisible(false);
	}

}

float BAnimation::getRotation()
{
	return m_fRotation;
}

void BAnimation::setRotation(float fRotation)
{
	
	m_fRotation = fRotation;

	vector<CCSprite*>::iterator it;

	for(it = m_pList.begin(); it != m_pList.end(); it++)
	{
		(*it)->setRotation(m_fRotation);
	}

}

void BAnimation::setAnchorPoint(float fX, float fY)
{
	vector<CCSprite*>::iterator it;

	for(it = m_pList.begin(); it != m_pList.end(); it++)
	{
		(*it)->setAnchorPoint(CCPoint(fX, fY));
	}
}

bool BAnimation::getFrameOnce()
{
	return m_bFrameOnce;
}

void BAnimation::setFrameOnceReset()
{
	m_bFrameOnce = false;
}