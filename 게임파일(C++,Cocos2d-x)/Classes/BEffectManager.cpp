#include "stdafx.h" 

void BEffectManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;

}

void BEffectManager::Pause()
{
	if(m_pEffectList.size() >= 1)
	{
		list<BAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end(); it++)
		{
			(*it)->setPause(true);
			//(*it)->m_pBlock->getActionManager()->pauseTarget((*it)->m_pBlock);
		}
	}
}

void BEffectManager::Resume()
{
	if(m_pEffectList.size() >= 1)
	{
		list<BAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end(); it++)
		{
			(*it)->setPause(false);
			//(*it)->m_pBlock->getActionManager()->resumeTarget((*it)->m_pBlock);
		}
	}
}
void BEffectManager::Exit()
{
	if(m_pEffectList.size() >= 1)
	{
		list<BAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end();)
		{
			(*it)->Exit();
			delete (*it);
			it = m_pEffectList.erase(it);
			//m_pThisScene->removeChild((*it)->m_pBlock,true);
			//delete (*it);
			//it = m_pEffectList.erase(it);
		}
	}
}
void BEffectManager::Update(float dt)
{
	if(m_pEffectList.size() >= 1)
	{
		list<BAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end();)
		{
			(*it)->Update(dt);

			if(  ( (*it)->m_nIndex >= 1 && (*it)->m_nIndex <= 6 ) && (*it)->m_fTimer >= 0.5f )
			{
				(*it)->Exit();
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else
			{
				it++;
			}

			//(*it)->m_fTimer += dt;
			//if((*it)->m_nIndex == 7)// || (*it)->m_nIndex == 8)
			//{
			//	if((*it)->m_fTimer >= 0.5f)
			//		(*it)->m_pBlock->setOpacity(255 * (1.0f - (((*it)->m_fTimer - 0.5f)*2)));
			//}
			//if((*it)->m_nIndex < 7 && (*it)->m_fTimer >= 0.5f)
			//{
			//	m_pThisScene->removeChild((*it)->m_pBlock,true);
			//	delete (*it);
			//	it = m_pEffectList.erase(it);
			//}
			//else if((*it)->m_nIndex == 7 && (*it)->m_fTimer >= 1.0f)
			//{
			//	
			//	m_pThisScene->removeChild((*it)->m_pBlock,true);
			//	delete (*it);
			//	it = m_pEffectList.erase(it);
			//}
			//else if((*it)->m_nIndex == 8 && (*it)->m_fTimer >= 1.0f)
			//{
			//	
			//	m_pThisScene->removeChild((*it)->m_pBlock,true);
			//	delete (*it);
			//	it = m_pEffectList.erase(it);
			//}
			//else if((*it)->m_nIndex == 9 && (*it)->m_fTimer >= 0.49f)
			//{
			//	
			//	m_pThisScene->removeChild((*it)->m_pBlock,true);
			//	delete (*it);
			//	it = m_pEffectList.erase(it);
			//}
			//else if((*it)->m_nIndex == 10 && (*it)->m_fTimer >= 0.81f)
			//{
			//	
			//	m_pThisScene->removeChild((*it)->m_pBlock,true);
			//	delete (*it);
			//	it = m_pEffectList.erase(it);
			//}
			//else
			//{
			//	it++;
			//}
		
		}
	}
}
void BEffectManager::Insert(int nIndex, float fX, float fY, float fSizeW , float fSizeH, float fAngle)
{
	char frameName[256];
	/*CCAnimation* m_pBlockAni;
	CCActionInterval * m_pBlockAnt;
	CCSprite * m_pBlock;
	stAnimation* pTempAni;
*/
	BAnimation* m_pEffectAni;

	nIndex++;

	const int nLayer = 2;

	switch(nIndex)
	{
	case 1:
		m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	case 2:
	m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	case 3:
		m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	case 4:
		m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	case 5:
		m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	case 6:
		m_pEffectAni = new BAnimation();
		m_pEffectAni->Init(m_pThisScene,nIndex,nLayer,ccp(fX,fY),0.05f);

		for(int i=0; i<10; i++)
		{
			sprintf(frameName,"Block_Pop_%d_%d.png",nIndex,i+1);
			m_pEffectAni->Insert(frameName);
		}

		m_pEffectList.push_back(m_pEffectAni);
		break;
	}
	
}
