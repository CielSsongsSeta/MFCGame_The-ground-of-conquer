
// mfcGameView.h : CmfcGameView 클래스의 인터페이스
//
#include "Land.h"


#pragma once


class CmfcGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CmfcGameView();
	DECLARE_DYNCREATE(CmfcGameView)

// 특성입니다.
public:
	CmfcGameDoc* GetDocument() const;
	CLand * m_pCurLn;
	int m_land[550][450];

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	double m_iData_time;
	int m_iData_clear;
	int Enemy_num;
	int kill;
	CPoint m_cBoom[100];
	CPoint m_cPrev_enemy[5];
	virtual ~CmfcGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnUpdateGame(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI* pCmdUI);
	afx_msg void OnEnd();
	afx_msg void OnUpdateEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	afx_msg void OnRestart();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_cEnemy[10];
	int Count;
	int m_iClear;
	BOOL m_bGame;
	int x; //주인공 에니메이션 카운터
	CPoint m_Prev;
	CPoint m_cHero;
	int Count_land;
};

#ifndef _DEBUG  // mfcGameView.cpp의 디버그 버전
inline CmfcGameDoc* CmfcGameView::GetDocument() const
   { return reinterpret_cast<CmfcGameDoc*>(m_pDocument); }
#endif

