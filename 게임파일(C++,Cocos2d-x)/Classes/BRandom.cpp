#include "stdafx.h"

int BRandom::Range(int nMin, int nMax)
{
	int nRand = rand()%(nMax-nMin+1) + nMin;
	return nRand;
}