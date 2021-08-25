#include "stdafx.h"

class CBlokingBlock
{
protected:
	CCPoint m_stPos;
public:
	CCPoint m_stIndex;
	CBlokingBlock(CCPoint stPos)
	{
		m_stPos = stPos;
	};
	~CBlokingBlock()
	{

	};
public:
	CCPoint getPos();
	void setPos(CCPoint stPos);
	
};