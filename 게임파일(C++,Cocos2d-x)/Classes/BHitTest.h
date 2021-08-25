#pragma once

typedef struct __tagRECT
{
    long    left;
    long    top;
    long    right;
    long    bottom;
}newRECT;

class BHitTest
{
public:

	static bool HitTest_Square(newRECT rc1, newRECT rc2);
};