#include "stdafx.h"

bool BHitTest::HitTest_Square(newRECT rc1, newRECT rc2)
{
	if (rc1.left < rc2.right &&
		rc1.top > rc2.bottom &&
		rc1.right > rc2.left &&
		rc1.bottom < rc2.top )
	{
		return true;
	}
	return false;
}