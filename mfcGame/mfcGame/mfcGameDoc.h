
// mfcGameDoc.h : CmfcGameDoc 클래스의 인터페이스
//
#if !defined(AFX_200211103_TERMDOC_H__82F3FADD_56E6_48D9_95DB_6942F87840CF__INCLUDED_)
#define AFX_200211103_TERMDOC_H__82F3FADD_56E6_48D9_95DB_6942F87840CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Land.h"


class CmfcGameDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CmfcGameDoc();
	DECLARE_DYNCREATE(CmfcGameDoc)

// 특성입니다.
public:
	CObArray m_land;
// 작업입니다.
public:
	CLand* GetLineAt(int i) {return (CLand*)m_land.GetAt(i);}
	int GetLineSize() {return m_land.GetSize();}
	CLand* GetNewLand();

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CmfcGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
//
	
};
//#ifdef SHARED_HANDLERS
//	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
//	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

