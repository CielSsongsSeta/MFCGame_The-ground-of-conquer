
// mfcGameDoc.h : CmfcGameDoc Ŭ������ �������̽�
//
#if !defined(AFX_200211103_TERMDOC_H__82F3FADD_56E6_48D9_95DB_6942F87840CF__INCLUDED_)
#define AFX_200211103_TERMDOC_H__82F3FADD_56E6_48D9_95DB_6942F87840CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Land.h"


class CmfcGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CmfcGameDoc();
	DECLARE_DYNCREATE(CmfcGameDoc)

// Ư���Դϴ�.
public:
	CObArray m_land;
// �۾��Դϴ�.
public:
	CLand* GetLineAt(int i) {return (CLand*)m_land.GetAt(i);}
	int GetLineSize() {return m_land.GetSize();}
	CLand* GetNewLand();

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CmfcGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
//
	
};
//#ifdef SHARED_HANDLERS
//	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
//	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

