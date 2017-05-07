#include "stdafx.h"
#include "mfcGame.h"
#include "Land.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLand::CLand()
{

}

CLand::~CLand()
{

}

CPoint CLand::Get_big_point()
{ // 현재 먹은 땅덩어리에서 가장 큰 x,y값 추출.
	CPoint tmp;
	tmp.x = 0;
	tmp.y = 0;
	
	for(int j=0;j<m_Line.GetSize();j++){
		CPoint *tmp1 = (CPoint*)m_Line.GetAt(j);
		if( tmp.x < tmp1->x)
			tmp.x = tmp1->x;
	}
	for(int j1=0;j1<m_Line.GetSize();j1++){
		CPoint * tmp1 = (CPoint*)m_Line.GetAt(j1);
		if( tmp.y < tmp1->y)
			tmp.y = tmp1->y;
	}

	return tmp;
}

CPoint CLand::Get_small_point()
{// 현재 먹은 땅덩어리에서 가장 작은 x,y값 추출.
	CPoint tmp;
	tmp.x = 540;
	tmp.y = 440;
	for(int j=0;j<m_Line.GetSize();j++){
		CPoint * tmp1 = (CPoint*)m_Line.GetAt(j);
		if( tmp.x > tmp1->x)
			tmp.x = tmp1->x;
	}
	for(int j1=0;j1<m_Line.GetSize();j1++){
		CPoint * tmp1 = (CPoint*)m_Line.GetAt(j1);
		if( tmp.y > tmp1->y)
			tmp.y = tmp1->y;
	}

	return tmp;
}