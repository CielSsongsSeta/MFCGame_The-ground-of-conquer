#if !defined(AFX_LAND_H__B5F90B0D_50C1_4D1B_8EC3_C70502D06197__INCLUDED_)
#define AFX_LAND_H__B5F90B0D_50C1_4D1B_8EC3_C70502D06197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLand : public CObject  
{
public:
	CPoint Get_big_point();
	CPoint Get_small_point();
	CLand();
	virtual ~CLand();
	CPtrArray m_Line;	
	void AddPoint(CPoint* p) // 좌표를 컨테이너에 삽입.
	{
		CPoint* pt = new CPoint(*p);
		m_Line.Add(pt);
	}

private:

};

#endif