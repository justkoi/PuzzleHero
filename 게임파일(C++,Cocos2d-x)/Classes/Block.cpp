#include "stdafx.h"

USING_NS_CC;
static int Random = 0;
void CBlock::Init(CCLayer* pThisScene, int nId)
{
	char frameName[256];
	m_pThisScene = pThisScene;

	m_bLive = false;

	m_nId = nId;
	m_fNextDistance = D_BLOCK_HEIGHT;
	m_stOffsetPos = ccp(0,0);

	m_stIndex.m_nX = 0;
	m_stIndex.m_nY = 0;
	m_fEyeContact = 0.0f;

	
	m_nHpMax = 100.0f;
	m_nHpNow = 100.0f;
	m_nDamage = 10.0f;


	m_stIndex = m_stIndex;

	m_stPos.x = D_LINE_START_X + (m_stIndex.m_nX * D_BLOCK_WIDTH);
	m_stPos.y = D_LINE_START_Y - (m_stIndex.m_nY * D_BLOCK_HEIGHT);

	Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = (E_BLOCKNUMBER)Random;

	m_eBlockItem = E_BLOCKITEM_NONE;


	m_fStartY			= m_stPos.y;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_FALL_NONE;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;
	m_bNoSelect = true;

	m_bChecked = false;
	m_bFocused = false;
	
	m_fTargetColorAlpha = 0.0f;
	m_fNowColorAlpha = 0.0f;

	m_fTargetAlpha = 1.0f;
	m_fNowAlpha = 1.0f;
	
	m_pNoSelect = CCSprite::create("Block_Select.png");
	m_pNoSelect->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pNoSelect->setScaleX(1.30f * D_SCALE_WIDTH);
	m_pNoSelect->setScaleY(1.30f * D_SCALE_HEIGHT);
	m_pNoSelect->setOpacity(255 * 0.0f);
	m_pNoSelect->setVisible(true);
	m_pNoSelect->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pNoSelect, 21);


	m_bFallFinished = false;
	m_fGPM = 0.0f;

	
	m_nBounceLevel = 0;
	m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
	m_fBounceLine = 0.0f;
}

void CBlock::Create(stVec2i stIndex)
{
	
	



	char frameName[256];


	m_bNoSelect = true;

	m_bLive = true;

	m_bFallFinished = false;
	
	m_bChecked = false;
	m_bFocused = false;

	m_nBounceLevel = 0;
	m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
	m_fBounceLine = 0.0f;

	m_stIndex = stIndex;
	m_fNextDistance = D_BLOCK_HEIGHT;
	m_stOffsetPos = ccp(0,0);

	m_stPos.x = D_LINE_START_X + (stIndex.m_nX * D_BLOCK_WIDTH);
	m_stPos.y = D_LINE_START_Y - (stIndex.m_nY * D_BLOCK_HEIGHT);
	
	m_eBlockItem = E_BLOCKITEM_NONE;
	
	m_pBlockItemParticle = NULL;

	Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = (E_BLOCKNUMBER)Random;
	
	m_fStartY			= m_stPos.y;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	
	if(m_eBlockNumber == (E_BLOCKNUMBER)0 || m_eBlockNumber == (E_BLOCKNUMBER)3)
	{
		m_nHpMax = 100.0f;
		m_nHpNow = 100.0f;
		m_nDamage = 10.0f;
	}
	else
	{
		m_nHpMax = 50.0f;
		m_nHpNow = 50.0f;
		m_nDamage = 15.0f;
	}

	Random = (rand()%100) + 1;

	if(Random >= 1 && Random < 94)
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
	}
	else if(Random >= 95 && Random <= 97)
	{
		m_eBlockItem = E_BLOCKITEM_HP_PLUS;
			
		//CCParticleSystem* m_pBlockItemParticle;
		m_pBlockItemParticle = CCParticleFire::create();
		m_pBlockItemParticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		m_pBlockItemParticle->setTotalParticles(D_BLOCKITEM_PARTICLE_MAX);
		//!< 주의 다시 메모리 해제해주는 방법 찾을것
		//m_pBlockItemParticle->setAutoRemoveOnFinish(true);
		m_pBlockItemParticle->setLife(0.7f);
		m_pBlockItemParticle->setLifeVar(0.2f);
		m_pBlockItemParticle->setPosition(ccp( 200.0f, 950.0f));
		//m_pBlockItemParticle->setGravity(ccp(0,0));
		//emitter->setRotatePerSecond(10.0f);
		//emitter->setRotatePerSecondVar(20.0f);
		m_pBlockItemParticle->setOpacity(255.0f * 0.3f);
		m_pBlockItemParticle->setScale(1.0f);
		//m_pBlockItemParticle->setStartSize(1.0f);
		//m_pBlockItemParticle->setStartSizeVar(1.0f);
		//m_pBlockItemParticle->setEndSize(1.5f);
		//m_pBlockItemParticle->setEndSizeVar(1.5f);
		//m_pBlockItemParticle->setDuration(20.0f);
		//m_pBlockItemParticle->setSpeed(160);
		//m_pBlockItemParticle->setSpeedVar(0);
		//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
		m_pBlockItemParticle->setEmissionRate(30.0f);
		//emitter->setAngle(0.0f);
		//emitter->setAngleVar(360.0f);

		m_pBlockItemParticle->setStartColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 80, (1.0f/255) * 80, 1.0f));
		m_pBlockItemParticle->setEndColor(ccc4f((1.0f/255) * 255, (1.0f/255) * 150, (1.0f/255) * 150, 0.0f));
	
		m_pThisScene->addChild(m_pBlockItemParticle,3);

	}
	else if(Random >= 98 && Random < 100)
	{
		m_eBlockItem = E_BLOCKITEM_MP_PLUS;
			
		//CCParticleSystem* m_pBlockItemParticle;
		m_pBlockItemParticle = CCParticleFire::create();
		m_pBlockItemParticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		m_pBlockItemParticle->setTotalParticles(D_BLOCKITEM_PARTICLE_MAX);
		//!< 주의 다시 메모리 해제해주는 방법 찾을것
		//m_pBlockItemParticle->setAutoRemoveOnFinish(true);
		m_pBlockItemParticle->setLife(0.7f);
		m_pBlockItemParticle->setLifeVar(0.2f);
		m_pBlockItemParticle->setPosition(ccp( 200.0f, 950.0f));
		//m_pBlockItemParticle->setGravity(ccp(0,0));
		//emitter->setRotatePerSecond(10.0f);
		//emitter->setRotatePerSecondVar(20.0f);
		m_pBlockItemParticle->setOpacity(255.0f * 0.3f);
		m_pBlockItemParticle->setScale(1.0f);
		//m_pBlockItemParticle->setStartSize(1.0f);
		//m_pBlockItemParticle->setStartSizeVar(1.0f);
		//m_pBlockItemParticle->setEndSize(1.5f);
		//m_pBlockItemParticle->setEndSizeVar(1.5f);
		//m_pBlockItemParticle->setDuration(20.0f);
		//m_pBlockItemParticle->setSpeed(160);
		//m_pBlockItemParticle->setSpeedVar(0);
		//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
		m_pBlockItemParticle->setEmissionRate(30.0f);
		//emitter->setAngle(0.0f);
		//emitter->setAngleVar(360.0f);

		m_pBlockItemParticle->setStartColor(ccc4f((1.0f/255) * 80, (1.0f/255) * 80, (1.0f/255) * 255, 1.0f));
		m_pBlockItemParticle->setEndColor(ccc4f((1.0f/255) * 150, (1.0f/255) * 150, (1.0f/255) * 255, 0.0f));
	
		m_pThisScene->addChild(m_pBlockItemParticle,3);

	}



	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_FALL_NONE;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;
	m_pNoSelect->setPosition(ccp(-100.0f,-100.0f));
	m_pNoSelect->setVisible(true);

	sprintf(frameName,"Block_%d.png",(int)m_eBlockNumber + 1);

	m_pBlock = CCSprite::create(frameName);
	m_pBlock->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX((1.00f/64.0f)*D_BLOCK_WIDTH);
	m_pBlock->setScaleY((1.00f/64.0f)*D_BLOCK_HEIGHT);
	m_pBlock->setColor(ccc3(255 * 1.0f,255 * 1.0f,255 * 1.0f));
	m_pBlock->setAnchorPoint(ccp(0.5f,0.5f));

	if((int)m_eBlockNumber == 0)
	{
		m_pBlock->setScaleX((1.00f/64.0f)*D_BLOCK_WIDTH);
		m_pBlock->setScaleY((1.00f/64.0f)*D_BLOCK_WIDTH * (55.0f/75.0f));
	}
	m_pThisScene->addChild(m_pBlock, 2);

	m_pBlock->setVisible(true);

	m_fTargetColorAlpha = 0.0f;
	m_fNowColorAlpha = 0.0f;

	m_fTargetAlpha = 1.0f;
	m_fNowAlpha = 1.0f;

	m_fGPM = 0.0f;

	
	m_fChangeDistance = 0.0f;
	m_eDerection = E_DERECTION_LEFT;

}

void CBlock::Create_Hero(stVec2i stIndex)
{
	
	m_nHpMax = g_nHeroHpConst;
	m_nHpNow = g_nHeroHpConst;
	m_nDamage = g_nHeroAtk;



	char frameName[256];

	m_bNoSelect = true;

	m_bLive = true;

	m_bFallFinished = false;
	
	m_bChecked = false;
	m_bFocused = false;

	m_nBounceLevel = 0;
	m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
	m_fBounceLine = 0.0f;

	m_stIndex = stIndex;
	m_fNextDistance = D_BLOCK_HEIGHT;
	m_stOffsetPos = ccp(0,0);

	m_stPos.x = D_LINE_START_X + (stIndex.m_nX * D_BLOCK_WIDTH);
	m_stPos.y = D_LINE_START_Y - (stIndex.m_nY * D_BLOCK_HEIGHT);
	
	m_eBlockItem = E_BLOCKITEM_NONE;
	m_pBlockItemParticle = NULL;

	//Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = E_BLOCKNUMBER_HERO;
	
	m_fStartY			= m_stPos.y;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_FALL_NONE;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;
	m_pNoSelect->setPosition(ccp(-100.0f,-100.0f));
	m_pNoSelect->setVisible(true);

	sprintf(frameName,"Block_%d.png",(int)m_eBlockNumber + 1);

	m_pBlock = CCSprite::create(frameName);
	m_pBlock->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX((1.00f/64.0f)*D_BLOCK_WIDTH);
	m_pBlock->setScaleY((1.00f/64.0f)*D_BLOCK_HEIGHT);
	m_pBlock->setColor(ccc3(255 * 1.0f,255 * 1.0f,255 * 1.0f));
	m_pBlock->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pBlock, 3);

	m_pBlock->setVisible(true);

	m_fTargetColorAlpha = 0.0f;
	m_fNowColorAlpha = 0.0f;

	m_fTargetAlpha = 1.0f;
	m_fNowAlpha = 1.0f;

	m_fGPM = 0.0f;

	
	m_fChangeDistance = 0.0f;
	m_eDerection = E_DERECTION_LEFT;

}
void CBlock::Update(float dt)
{		

	if(m_eBlockNumber == E_BLOCKNUMBER_HERO)
	{
		g_nHeroHp = m_nHpNow;
		g_nHeroHpMax = m_nHpMax;
		g_stHeroIdx = m_stIndex;
	}
	if(m_bLive == true)

	{
		if(m_eBlockState == E_BLOCKSTATE_FALL_FALLING && m_bDraged == false && m_bFallFinished == false)
		{
			if(m_fNowDistance < m_fDistance)
			{
				m_stPos.y -= (m_fSpeed * dt) ;
				m_fNowDistance += (m_fSpeed * dt) ;
				m_fSpeed += (m_fPlusSpeed * dt);
				if(m_fNowDistance >= m_fDistance)
				{
					m_fGPM = (m_fStartY - m_fDistance) - m_stPos.y;
					m_stPos.y		    = m_fStartY - m_fDistance;
					// m_fSpeed			= D_BLOCK_SPEED;
					// m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
					m_fNowDistance		= 0.0f;
					m_fDistance			= D_BLOCK_HEIGHT;
					//m_eBlockState		= E_BLOCKSTATE_FALL_NONE;
					m_bFallFinished = true;
				}
			}
		}

		if(m_nBounceLevel > 0)
		{
			m_stPos.y += m_fBouncePower * dt;
			m_fBouncePower -= 300 * dt;
			if(m_stPos.y <= m_fBounceLine)
			{
				m_nBounceLevel--;
				m_fBouncePower = D_BLOCK_BOUNCE_FOWER;
				m_stPos.y = m_fBounceLine;
			}
		}

		if(m_fNowColorAlpha < m_fTargetColorAlpha)
		{
			m_fNowColorAlpha += dt * 1.5;
			if(m_fNowColorAlpha > m_fTargetColorAlpha)
				m_fNowColorAlpha = m_fTargetColorAlpha;
		}
		else if(m_fNowColorAlpha > m_fTargetColorAlpha)
		{
			m_fNowColorAlpha -= dt * 1.2f ; //!< 마나가 빠지는 속도는 차오르는 속도의 70%
			if(m_fNowColorAlpha < m_fTargetColorAlpha)
				m_fNowColorAlpha = m_fTargetColorAlpha;
		}

		if(m_fNowAlpha > m_fTargetAlpha)
		{
			m_fNowAlpha -= dt * 2.2f;
			if(m_fNowAlpha < m_fTargetAlpha)
				m_fNowAlpha = m_fTargetAlpha;
		}
	
		m_pBlock->setPosition(ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT ));
		//m_pBlock[E_BLOCKSTATE_ACT_NONE]->setColor(ccc3(255 * (1.0f - m_fNowColorAlpha),255 * m_fNowColorAlpha,255 * (1.0f - m_fNowColorAlpha)));
		m_pBlock->setOpacity(255 * m_fNowAlpha);

		if(m_eBlockItem != E_BLOCKITEM_NONE)
			m_pBlockItemParticle->setPosition(ccp( m_stPos.x * D_SCALE_WIDTH, (m_stPos.y - 15.0f) * D_SCALE_HEIGHT ));

		//if(m_nHpNow < 100)
			m_pBlock->setColor(Color3B(255 * (float)((float)m_nHpNow/(float)m_nHpMax),255 * (float)((float)m_nHpNow/(float)m_nHpMax),255 * (float)((float)m_nHpNow/(float)m_nHpMax)));
		/*if(m_eBlockItem != E_BLOCKITEM_NONE)
			m_pItem->setOpacity(255 * m_fNowAlpha);
*/
		m_pNoSelect->setOpacity(255 * m_fNowColorAlpha);
		
		if(m_fNowAlpha < 1.0f)
			m_pNoSelect->setVisible(false);

		m_pNoSelect->setPosition(ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT ));
		

	}
	else if(m_bLive == false)
	{
		
	}
}
void CBlock::Alphaing()
{
	m_fTargetAlpha = 0.0f;
}
void CBlock::Exit()
{
	if(m_bLive == true)
	{
		m_pThisScene->removeChild(m_pBlock,true);
		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			//m_pBlockItemParticle->release();
			m_pThisScene->removeChild(m_pBlockItemParticle);
			m_pBlockItemParticle = NULL;
		}
	}
}
void CBlock::Die()
{
	if(m_bLive == true)
	{
		m_pThisScene->removeChild(m_pBlock,true);
		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			//m_pBlockItemParticle->release();
			m_pThisScene->removeChild(m_pBlockItemParticle);
			m_pBlockItemParticle = NULL;
		}

	//	m_pBlockItemParticle->removeFromParentAndCleanup(true);

		//!< 아이템이 있을경우 효과발동
		if(m_eBlockItem == E_BLOCKITEM_MP_PLUS)
		{
			g_nHeroMp += D_BLOCK_ITEM_MP_PLUS;
			if(efsound == true)
				D_SOUNDMNG->playEffect("Item_Mp.mp3");
			//!< MP 더해주고 최대치 넘지못하게 해주는 구문
			if(g_nHeroMp >= g_nHeroMpMax)
			{
				g_nHeroMp = g_nHeroMpMax;
			}
		}
		else if(m_eBlockItem == E_BLOCKITEM_HP_PLUS)
		{
			g_BlockList[g_nHeroIdx].m_nHpNow += D_BLOCK_ITEM_HP_PLUS;
			if(efsound == true)
				D_SOUNDMNG->playEffect("Item_Mp.mp3");
			//!< MP 더해주고 최대치 넘지못하게 해주는 구문
			if(g_BlockList[g_nHeroIdx].m_nHpNow >= g_BlockList[g_nHeroIdx].m_nHpMax)
			{
				g_BlockList[g_nHeroIdx].m_nHpNow = g_BlockList[g_nHeroIdx].m_nHpMax;
			}
		}
	
	}
	// printf("블록이미지삭제\n");
	
	
	
	m_bLive = false;
//	if(m_bLive == true)
//	{
//		m_pThisScene->removeChild(m_pBlock,true);
//		m_pThisScene->removeChild(m_pBlock_Pause,true);
//		m_pThisScene->removeChild(m_pBlock_Freeze,true);
//		m_pThisScene->removeChild(m_pBlock_Angry,true);
//		if(m_eBlockItem != E_BLOCKITEM_NONE)
//		{
//			m_pThisScene->removeChild(m_pItem,true);
//			m_eBlockItem = E_BLOCKITEM_NONE;
//		}
//	}
//	/*delete m_pBlockAni;
//	delete m_pBlockAnt;*/
//
//	m_bLive = false;
//
//	m_pFreeze->setVisible(false);
//
//
//	
//	//m_pBlockAni->autorelease();
//	//m_pBlockAnt->autorelease();
//	//delete m_pBlockAni;
//	//delete m_pBlockAnt;
//
//	//!< m_pErosoin->setVisible(true);
//	//!< m_pErosoin_Border->setVisible(true);
///*
//	for(int i=0; i<E_BLOCKNUMBER_MAX ; i++)
//	{
//		m_pBlock[i]->setVisible(true);
//		m_pBlock_Pause[i]->setVisible(true);
//	}*/
//	/*m_pBlock->setVisible(true);
//	m_pBlock_Pause->setVisible(true);
//*/
//	m_pSelect->setVisible(false);

}
bool CBlock::HitTest(float nX, float nY)
{
	if(m_bLive == false)
		return false;
	if(nX >= (m_stPos.x - (D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH  && nX <= (m_stPos.x + (D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH  &&
		nY >= (m_stPos.y - (D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT  && nY <= (m_stPos.y + (D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT )
	{
		return true;
	}
	return false;
}



void CBlock::ShowUpdate()
{
	/*if(m_bLive == false)
	{
		m_pFreeze->setVisible(false);
		m_pSelect->setVisible(false);
	}*/
}

void CBlock::CheckReset()
{
	m_bChecked = false;
	m_bFocused = false;
}
void CBlock::NextBlockNumber()
{
	/*E_BLOCKNUMBER eBlockNumber = (E_BLOCKNUMBER)((int)m_eBlockNumber + 1);
	if((int)eBlockNumber >= (int)E_BLOCKNUMBER_MAX)
	{
		eBlockNumber = E_BLOCKNUMBER_RED;
	}

	SetBlockNumber(eBlockNumber);*/
}
void CBlock::SetBlockNumber(E_BLOCKNUMBER eBlockNumber)
{
	/*char frameName[256];
	m_eBlockNumber = eBlockNumber;

	m_pThisScene->removeChild(m_pBlock,true);

	sprintf(frameName,"Block_%d.png",(int)m_eBlockNumber + 1);
	m_pBlock = CCSprite::create(frameName);
	m_pBlock->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBlock->setAnchorPoint(ccp(0.5f,0.5f));
	m_pThisScene->addChild(m_pBlock, 20);*/
}