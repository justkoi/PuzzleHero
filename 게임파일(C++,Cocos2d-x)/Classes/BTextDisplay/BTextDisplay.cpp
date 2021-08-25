#include "stdafx.h"

//#define isHangul(str0, str1) ( (str0 >= 0xB0) && (str0 <= 0xC8) && (str1 >= 0xA1) && (str1 <= 0xFE) )

void BTextDisplay::Init(CCLayer* pThisScene,int nLayer, string stdName, float fX, float fY, int nLineWidth, int nLineHeight, CCPoint stSize, ccColor3B Color, string stdFont, bool Ortho2D)
{
	m_Color = Color;
	m_stdFont = stdFont;
	m_stSize = stSize;

	m_nLayer = nLayer = 0;

	m_stPos.x = fX;
	m_stPos.y = fY;
	m_nLineHeight = nLineHeight;
	m_pThisScene = pThisScene;

	m_nNowLine = 0;

	m_pTextList.clear();


	m_NowString = "";
	m_nNowChar = 0;

	m_fNowProgressTime = 0;
	m_nOffsetSpace = 0;

	m_nLineWidth_Basic = nLineWidth;
	m_nLineMaxChar = nLineWidth;
	m_nNowLineMaxChar = m_nLineMaxChar;

	m_nLineChanged = false;

	m_nHangulLevel = 0;

	m_bSkip = false;
	m_bPause = false;
	m_bFastView = false;
}

void BTextDisplay::SetText(string String)
{
	if(IsViewing() == false)
	{

		DestroyText();
		
		m_bSkip = false;
		m_bPause = false;
		m_bFastView = false;

		m_nNowChar = 0;
		m_nNowLine = 0;
		m_nOffsetSpace = 0;
		m_String.clear();
		m_String = String;
		m_nMaxChar = m_String.size();
		m_NowString = "";
		
		m_nLineMaxChar = m_nLineWidth_Basic;
		m_nNowLineMaxChar = m_nLineMaxChar;

		CCLabelTTF * m_pText = CCLabelTTF::create("", m_stdFont, 24);//new CEMText(m_stdFont, "");
		m_pText->setColor(ccColor3B(m_Color.r, m_Color.g, m_Color.b));
		m_pText->setPosition(m_stPos.x, m_stPos.y - (m_nNowLine * m_nLineHeight));
		m_pText->setScale(m_stSize.x,m_stSize.y);

		m_pTextList.push_back(m_pText);
		m_pThisScene->addChild(m_pText,m_nLayer);

	//	m_pThisScene->Commit(-1000, m_nNowLine, m_stdName, m_pText);

		m_fNowProgressTime = 0;
	}
}

void BTextDisplay::SetProgressTime(float fProgressTime)
{
	m_fProgressTime = fProgressTime;
}

void BTextDisplay::Update(float dt)
{ 
	if(m_bPause == true)
		return;

	m_fNowProgressTime += dt;

	if(m_bSkip == false)
	{
		if(m_bFastView == true || m_fNowProgressTime >= m_fProgressTime)
		{
			if(m_fNowProgressTime >= m_fProgressTime)
				m_fNowProgressTime -= m_fProgressTime;

			if(m_nNowChar < m_nMaxChar)
			{
				if(m_nLineChanged == true)
				{
					m_nLineChanged = false;
					m_NowString.clear();
				}

				m_NowString.push_back(m_String[m_nNowChar]);
				m_nNowChar++;
				if(m_NowString[m_NowString.size() - 1] == '/')
				{
					NextLine();
				}
				else
				{

					if(m_nHangulLevel == 1 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 0;
					}
					else if(m_nHangulLevel == 0 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 1;
					}

					if(m_nNowChar >= m_nNowLineMaxChar - 1)
					{
						if( m_NowString[m_NowString.size() - 1] & 0x80 && m_nHangulLevel == 0)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 2;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80&& m_nHangulLevel == 1)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80 )
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else
						{
							m_nNowChar -= 1;
						}
						NextLine();
					}
				}
				
			}
			if(!(m_nNowChar < m_nMaxChar))
			{
				if(m_bFastView == true)
					m_bFastView = false;
			}
		

			if(m_NowString.size() >= 1 && (m_NowString.size() + m_nOffsetSpace)%2 == 1)
			{
				if( m_NowString[m_NowString.size() - 1] & 0x80 )
				{
					m_nHangulLevel = 1;

					string strTemp;
					strTemp = m_NowString;
					strTemp.pop_back();

					list<CCLabelTTF*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->setString(strTemp);//(*it)->SetOutPutString(strTemp);
					m_ViewString = strTemp;
				}
				else
				{
					m_nHangulLevel = 0;
					m_nOffsetSpace++;
					list<CCLabelTTF*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->setString(m_NowString);//(*it)->SetOutPutString(m_NowString);
					m_ViewString = m_NowString;
				}
			}
			else
			{
				if( (m_NowString[m_NowString.size() - 1] & 0x80) == false)
				{
					m_nOffsetSpace++;
				}
				list<CCLabelTTF*>::iterator it;
				it = m_pTextList.begin();
				for(int i = 0; i < m_nNowLine; i++, it++)
				{
				
				}
				(*it)->setString(m_NowString);//(*it)->SetOutPutString(m_NowString);
				m_ViewString = m_NowString;
			}
	
		
			list<CCLabelTTF*>::iterator it;
			it = m_pTextList.begin();
			for(int i = 0; i < m_nNowLine; i++, it++)
			{
			
			}
			(*it)->setString(m_ViewString);//(*it)->SetOutPutString(m_ViewString);
		}
	
	}
	else if(m_bSkip == true)
	{
	
		while(m_nNowChar < m_nMaxChar)
		{
			if(m_nNowChar < m_nMaxChar)
			{
				if(m_nLineChanged == true)
				{
					m_nLineChanged = false;
					m_NowString.clear();
				}

				m_NowString.push_back(m_String[m_nNowChar]);
				m_nNowChar++;
				if(m_NowString[m_NowString.size() - 1] == '/')
				{
					NextLine();
				}
				else
				{
					if(m_nHangulLevel == 1 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 0;
					}
					else if(m_nHangulLevel == 0 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 1;
					}

					if(m_nNowChar >= m_nNowLineMaxChar - 1)
					{
						if( m_NowString[m_NowString.size() - 1] & 0x80 && m_nHangulLevel == 0)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 2;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80&& m_nHangulLevel == 1)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80 )
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						NextLine();
					}
				}
				
			}
		

			if(m_NowString.size() >= 1 && (m_NowString.size() + m_nOffsetSpace)%2 == 1)
			{
				if( m_NowString[m_NowString.size() - 1] & 0x80 )
				{
					m_nHangulLevel = 1;

					string strTemp;
					strTemp = m_NowString;
					strTemp.pop_back();

					list<CCLabelTTF*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->setString(strTemp);//(*it)->SetOutPutString(strTemp);
					m_ViewString = strTemp;
				}
				else
				{
					m_nHangulLevel = 0;
					m_nOffsetSpace++;
					list<CCLabelTTF*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->setString(m_NowString);//(*it)->SetOutPutString(m_NowString);
					m_ViewString = m_NowString;
				}
			}
			else
			{
				if( (m_NowString[m_NowString.size() - 1] & 0x80) == false)
				{
					m_nOffsetSpace++;
				}
				list<CCLabelTTF*>::iterator it;
				it = m_pTextList.begin();
				for(int i = 0; i < m_nNowLine; i++, it++)
				{
				
				}
				(*it)->setString(m_NowString);//(*it)->SetOutPutString(m_NowString);
				m_ViewString = m_NowString;
			}
	
		
			list<CCLabelTTF*>::iterator it;
			it = m_pTextList.begin();
			for(int i = 0; i < m_nNowLine; i++, it++)
			{
			
			}
			(*it)->setString(m_ViewString);//(*it)->SetOutPutString(m_ViewString);
		
		}
		if(!(m_nNowChar < m_nMaxChar))
		{
			m_bSkip = false;
		}
	
	}

}

void BTextDisplay::Exit()
{
	DestroyText();
}


bool BTextDisplay::IsViewing()
{
	if(m_nNowChar < m_nMaxChar)
		return true;

	return false;
}


void BTextDisplay::DestroyText()
{
	//if(IsViewing() == false)
	//{
		list<CCLabelTTF*>::iterator itr;
		for(itr = m_pTextList.begin(); itr != m_pTextList.end();itr++)
		{
			m_pThisScene->removeChild(*itr);
			//m_pThisScene->DeletePlane(*itr);
			//itr = m_pTextList.erase(itr);
		}
		m_pTextList.clear();
	//}
}

void BTextDisplay::Skip()
{
	m_bSkip = true;
}


void BTextDisplay::SetFastView(bool bFastView)
{
	m_bFastView = bFastView;
}
void BTextDisplay::SetPause(bool bPause)
{
	m_bPause = bPause;
}

bool BTextDisplay::GetFastView()
{
	return m_bFastView;
}
bool BTextDisplay::GetPause()
{
	return m_bPause;
}


void BTextDisplay::NextLine()
{
	m_nOffsetSpace = 1;
	m_nNowLine++;
	m_nNowLineMaxChar += m_nLineMaxChar;
	m_NowString = " ";


	list<CCLabelTTF*>::iterator it;
	it = m_pTextList.begin();
	CCLabelTTF * m_pText = CCLabelTTF::create("",m_stdFont, 24);//new CEMText(m_stdFont, " ");
	m_pText->setColor(ccColor3B(m_Color.r, m_Color.g, m_Color.b));
	m_pText->setPosition(m_stPos.x, m_stPos.y - (m_nNowLine * m_nLineHeight));
	m_pText->setScale(m_stSize.x,m_stSize.y);
	m_pTextList.push_back(m_pText);
	m_pThisScene->addChild(m_pText,m_nLayer);
	//m_pThisScene->Commit(-1000, m_nNowLine, m_stdName, m_pText);
	m_nLineChanged = true;
}


void BTextDisplay::SetShow(bool bShow)
{
	list<CCLabelTTF*>::iterator itr;
	for(itr = m_pTextList.begin(); itr != m_pTextList.end(); itr++)
	{
		(*itr)->setVisible(bShow);
		//(*itr)->SetShow(bShow);
	}
	
}