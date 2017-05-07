
// mfcGameView.h : CmfcGameView Ŭ������ �������̽�
//
#include "Land.h"


#pragma once


class CmfcGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CmfcGameView();
	DECLARE_DYNCREATE(CmfcGameView)

// Ư���Դϴ�.
public:
	CmfcGameDoc* GetDocument() const;
	CLand * m_pCurLn;
	int m_land[550][450];

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
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
	int x; //���ΰ� ���ϸ��̼� ī����
	CPoint m_Prev;
	CPoint m_cHero;
	int Count_land;
};

#ifndef _DEBUG  // mfcGameView.cpp�� ����� ����
inline CmfcGameDoc* CmfcGameView::GetDocument() const
   { return reinterpret_cast<CmfcGameDoc*>(m_pDocument); }
#endif

