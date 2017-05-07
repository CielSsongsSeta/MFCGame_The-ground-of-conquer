
// mfcGameView.cpp : CmfcGameView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "mfcGame.h"
#include "Land.h"

#include "MainFrm.h"
#include "mfcGameDoc.h"
#include "mfcGameView.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define STEP 10
#define MAX_X 540
#define MAX_Y 410

// CmfcGameView

IMPLEMENT_DYNCREATE(CmfcGameView, CView)

BEGIN_MESSAGE_MAP(CmfcGameView, CView)
	//{{AFX_MSG_MAP(CMy200211103_termView)
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_START, OnStart)
	ON_UPDATE_COMMAND_UI_RANGE(ID_RESTART,ID_LOAD, OnUpdateGame)
	ON_UPDATE_COMMAND_UI(ID_SAVE, OnUpdateSave)
	ON_COMMAND(ID_END, OnEnd)
	ON_UPDATE_COMMAND_UI(ID_END, OnUpdateEnd)
	ON_UPDATE_COMMAND_UI(ID_START, OnUpdateStart)
	ON_COMMAND(ID_RESTART, OnRestart)
	ON_COMMAND(ID_LOAD, OnLoad)
	ON_COMMAND(ID_SAVE, OnSave)
	//}}AFX_MSG_MAP
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmfcGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CmfcGameView ����/�Ҹ�

CmfcGameView::CmfcGameView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	
	m_bGame = FALSE; // �����ϸ� Ʈ��
	m_iClear = 0; // ���� Ŭ���� �ߴ���.
	Enemy_num = 5;
	m_iData_time = 0;
	m_iData_clear = 0;
}

CmfcGameView::~CmfcGameView()
{
}

BOOL CmfcGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CmfcGameView �׸���

void CmfcGameView::OnDraw(CDC* pDC)
{
	CmfcGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	if(!m_bGame){ //��Ʈ�� ȭ��
		CBitmap bitmap1;
		bitmap1.LoadBitmap(IDB_BG1);
		CBitmap *pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap1);
		pDC->BitBlt(0,0,545,440,&MemDC,0,0,SRCCOPY);
		return;
	}

	CBitmap bitmap1; // ������ ȭ��
	bitmap1.LoadBitmap(IDB_COVER);
	CBitmap *pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap1);
	pDC->BitBlt(0,0,845,585,&MemDC,0,0,SRCCOPY);

	CBitmap bitmap2; // ������ ȭ��
	bitmap2.LoadBitmap(IDB_BG);
	pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap2);
	
	for(int i=0;i<540;i++) // �������� ǥ�õ� 1�� �׷��ش�.
		for(int j=0;j<MAX_Y;j++)
			if(m_land[i][j] == 1)
			pDC->BitBlt(i,j,1,1,&MemDC,i,j,SRCCOPY);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CmfcGameView �μ�

BOOL CmfcGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CmfcGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CmfcGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}



// CmfcGameView ����

#ifdef _DEBUG
void CmfcGameView::AssertValid() const
{
	CView::AssertValid();
}

void CmfcGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfcGameDoc* CmfcGameView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcGameDoc)));
	return (CmfcGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcGameView �޽��� ó����
void CmfcGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_bGame) return;

	CString land;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CClientDC dc(this);

	m_Prev = m_cHero;
	
	if(nChar == VK_LEFT) m_cHero.x -= 5;
	else if(nChar == VK_RIGHT)m_cHero.x += 5;
	else if(nChar == VK_UP) m_cHero.y -= 5;
	else if(nChar == VK_DOWN) m_cHero.y += 5;
  	
	if(m_cHero.x < 0) m_cHero.x = 0;
	if(m_cHero.y < 0) m_cHero.y = 0;
	if(m_cHero.x > MAX_X ) m_cHero.x = MAX_X;
	if(m_cHero.y > MAX_Y ) m_cHero.y = MAX_Y;
	  
	if(++x> 3) x=0;

	if(m_pCurLn) //���� ���� �Դ� ���̰�
		if (m_land[m_cHero.x][m_cHero.y] == 1 ) // �� ���� ������.
		{	
			//MessageBox("�츮��");
			CPoint tmp ,tmp1;
			tmp = m_pCurLn->Get_big_point(); // ���� ������� ���� ū ��ǥ ã��
			tmp1 =m_pCurLn->Get_small_point(); // ���� ��ǥ ã��.

			for(int i=tmp1.x;i<tmp.x;i++)
				for(int j=tmp1.y;j<tmp.y;j++){
					m_land[i][j] = 1; // �ִ�,�ּ� ��ǥ ���ؼ� �Ա�. 1�� ǥ��
					
					for(int k=0;k<Enemy_num;k++)
						if(m_cEnemy[k].x == i && m_cEnemy[k].y ==j)
						{ //���� �� �����ȿ� ������ ����.
							m_cBoom[kill].x = i;
							m_cBoom[kill++].y = j;//����� �� ī��Ʈ.
						}
					if(i == m_cEnemy[4].x && j ==m_cEnemy[4].y)
					{
						MessageBox(_T("�ð��� 0���� �ǵ����ϴ�~"));
						Count = 0;
					}
					
					Count_land++; //���� �� ����
				}
	
			//	
			//land.Format("�츮�� : %.2f    Stage : %d", Count_land*0.00046, m_iClear+1); //  ���� �� %�Ծ��� ����
			////pFrame->m_wndStatusBar.SetPaneText(0, land);
			//land.Format("KILL : %2d", kill); //  �� ���׿���.
			////pFrame->m_wndStatusBar.SetPaneText(3, land);

			m_pCurLn = NULL;
			Invalidate();
			return;
		}
	else //���� �Դ� ���� �ƴϰ�
		if (m_land[m_cHero.x][m_cHero.y] == 1 ) //�� ���� ���� �ٴ� ��
		{	
			m_pCurLn = NULL;
			return;
		}

	if(m_land[m_cHero.x][m_cHero.y] == 0) // �� ���� ���̹Ƿ� �� ��ü �����.
	{
		if(m_pCurLn) 
		{ // ���� ���� �Դ� ���϶� ��� ����.
			m_pCurLn->AddPoint(&m_cHero);
			m_land[m_cHero.x][m_cHero.y] = 1;
			for(int k = 0; k < 5; k++)
				for(int k1 = 0; k1 < 5; k1++)
					m_land[m_cHero.x+k][m_cHero.y+k1] =1; //������ ������ ��������.
			Count_land++;
		}	
		else 
		{ // ���� �� ��ü�� ���� ����� �� �Ա� ����
			m_pCurLn = GetDocument()->GetNewLand();
			m_pCurLn->AddPoint(&m_cHero);
			//m_land[m_cHero.x][m_cHero.y] = 1;
			for(int k2 = 0; k2 < 5; k2++)
				for(int k3 = 0; k3 < 5; k3++)
				m_land[m_cHero.x+k2][m_cHero.y+k3] =1; //������ ������ ��������.
			Count_land++;
		}		
	}	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



int CmfcGameView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0,30,NULL); // ���ΰ� Ÿ�̸�
	SetTimer(1,6000,NULL); // ���� Ÿ�̸�

	return 0;
}

void CmfcGameView::OnTimer(UINT nIDEvent) 
{
	if(!m_bGame) return;

	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap;
		
	CBitmap bitmap1;// ������ ���
	bitmap1.LoadBitmap(IDB_BG);
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap1);
	dc.BitBlt(m_Prev.x,m_Prev.y,5,5,&MemDC,m_Prev.x,m_Prev.y,SRCCOPY);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_HERO); //���ΰ� �׸���
	pOldBitmap = MemDC.SelectObject(&bitmap);
	dc.BitBlt(m_cHero.x,m_cHero.y,5,5,&MemDC,5*x,0,SRCCOPY);

	CBitmap bitmap21;// ���� ���� ��Ÿ��.
	bitmap21.LoadBitmap(IDB_BOOM);
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap21);
	for(int i=0;i<kill;i++)//���� �ڸ� ǥ��.
		dc.BitBlt(m_cBoom[i].x,m_cBoom[i].y,35,35,&MemDC,0,0,SRCCOPY);

	if(Count++ < 3000 && Count_land > (216000*0.6) && kill >= 5) 
	{
		m_bGame=FALSE;
		++m_iClear;
		m_iData_time = Count*0.025; // Ŭ����ð� ����.
		MessageBox(_T("Mission Clear!!"));
	}
	else if(Count++ > 3000) 
	{
		m_bGame=FALSE;MessageBox(_T("Time Over!"));
		exit(1);
	}
	// Ŭ���� ���� ����
	
	if(nIDEvent == 1)
	{ //Ÿ�̸� �ΰ� �����ؼ�.

		for(int i=0;i<Enemy_num;i++)
		{
			m_cEnemy[i].x = rand()%MAX_X;
			m_cEnemy[i].y = rand()%MAX_Y;

			if(m_land[m_cEnemy[i].x][m_cEnemy[i].y] == 0) // ���� ���� ��ǥ���� �� ���� ���� ����.
			{
				CBitmap bitmap3;
				bitmap3.LoadBitmap(IDB_COVER); // ���� �����
				pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap3);
				dc.BitBlt(m_cPrev_enemy[i].x,m_cPrev_enemy[i].y,25,25,&MemDC,0,0,SRCCOPY);
				
				if(i==4) { // ������ �Ѹ���.
					CBitmap bitmap211;
					bitmap211.LoadBitmap(IDB_CLOCK);
					pOldBitmap = MemDC.SelectObject(&bitmap211);
					dc.BitBlt(m_cEnemy[i].x,m_cEnemy[i].y,25,25,&MemDC,0,0,SRCCOPY);
					dc.SelectObject(pOldBitmap);
				}
				else{
					CBitmap bitmap2; // ���� �׸���.
					bitmap2.LoadBitmap(IDB_ENEMY);
					pOldBitmap = MemDC.SelectObject(&bitmap2);
					dc.BitBlt(m_cEnemy[i].x,m_cEnemy[i].y,25,25,&MemDC,25*(rand()%4),0,SRCCOPY);
					dc.SelectObject(pOldBitmap);
				}
				
				m_cPrev_enemy[i] = m_cEnemy[i];
			}
		}
	}
	CString tmp; // ī��Ʈ ����.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	/*tmp.Format(" %3.1f Sec",Count*0.025);
	pFrame->m_wndStatusBar.SetPaneText(2, tmp);
	tmp.Format("������ ����! ���� �׿�");
	pFrame->m_wndStatusBar.SetPaneText(1, tmp);*/
	
	if(m_pCurLn)
	{// ���� ���� �Դ� ���̰�
		/*tmp.Format("���� ���� �԰� �ִ���! �� ����!");
		pFrame->m_wndStatusBar.SetPaneText(1, tmp);*/

		for(int j=0;j < m_pCurLn->m_Line.GetSize();j++)
		{					
			CPoint *p2 = (CPoint*)m_pCurLn->m_Line.GetAt(j);
			for(int k=0;k<Enemy_num;k++)
			if(m_cEnemy[k].x <= p2->x && p2->x<=m_cEnemy[k].x+25 &&
				m_cEnemy[k].y <= p2->y && p2->y <=m_cEnemy[k].y+25)
			{ //���� �����̰� �ִ� ������ ������ �״´�.
			m_bGame = FALSE;
			MessageBox(_T("������ ���ױ� ������ ������ �ߴܵ˴ϴ�"));
			return;
			}
		}
	}

	CView::OnTimer(nIDEvent);
}

void CmfcGameView::OnStart() 
{
	// TODO: Add your command handler code here
	m_bGame = TRUE;
	
	kill = 0;
	if(m_iClear >= 1 && m_iClear < 2 )  Enemy_num=7; // ���� ����.
	if(m_iClear >= 2 && m_iClear < 3 )  Enemy_num=10;
	for(int i=0;i<100;i++)
		m_cBoom[i] = -30;
	Count_land=0;
	Count = 0;
	m_cHero.x = 0;
	m_cHero.y = 0;
	m_Prev = 0;	
	x=0; // ���ΰ� �ִϸ��̼ǿ�
	m_pCurLn = NULL;

	for(int i=0;i<10;i++)
	{
		m_cEnemy[i].x = rand()%MAX_X;
		m_cEnemy[i].y = rand()%MAX_Y;
		m_cPrev_enemy[i] = -1;
	}
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
			m_land[i][j] = 0; // �ʱ�ȭ
	
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<5;j++)
		{
			m_land[i][0+j] = 1;
			m_land[i][MAX_Y-j]= 1; // �� 1�� �ʱ�ȭ
		}
	for(int i=0;i<MAX_Y;i++) 
		for(int j1=0;j1<5;j1++)
		{
			m_land[0+j1][i] = 1;
			m_land[MAX_X-j1][i] = 1;  // �� 1�� �ʱ�ȭ
		}
	Invalidate();
}

void CmfcGameView::OnUpdateStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_bGame) pCmdUI->Enable();
    else pCmdUI->Enable(FALSE);
}

void CmfcGameView::OnUpdateGame(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGame) pCmdUI->Enable();
    else pCmdUI->Enable(FALSE);
}

void CmfcGameView::OnUpdateSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_iClear != 0 && !m_bGame) pCmdUI->Enable(); // ���������� ������ Ŭ���� �������� ���� ����
    else pCmdUI->Enable(FALSE);
}

void CmfcGameView::OnEnd() 
{
	// TODO: Add your command handler code here
	exit(1);
}

void CmfcGameView::OnUpdateEnd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGame) pCmdUI->Enable();
    else pCmdUI->Enable(FALSE);
}


void CmfcGameView::OnRestart() 
{
	m_bGame = TRUE;
	kill = 0;
	for(int i=0;i<100;i++)
		m_cBoom[i] = -30;
	Count_land=0;
	Count = 0;
	m_cHero.x = 0;
	m_cHero.y = 0;
	m_Prev = 0;	
	x=0; // ���ΰ� �ִϸ��̼ǿ�
	m_iClear = 0; // ���� Ŭ���� �ߴ���.
	m_pCurLn = NULL;
	for(int i=0;i<10;i++)
	{
		m_cEnemy[i].x = 100;//rand()%MAX_X;
		m_cEnemy[i].y = 100;//rand()%MAX_Y;
		m_cPrev_enemy[i] = -1;
	}
	
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
			m_land[i][j] = 0; // �ʱ�ȭ

	for(int i=0;i<MAX_Y;i++) 
	{
		m_land[i][0] = 1;
		m_land[i][MAX_Y]= 1; // �� 1�� �ʱ�ȭ
	}
		
	for(int i=0;i<MAX_X;i++) 
	{
		m_land[0][i] = 1;
		m_land[MAX_X][i] = 1;  // �� 1�� �ʱ�ȭ
	}
	Invalidate();
	//GetDocument()-UpdateAllData();
}


void CmfcGameView::OnLoad() 
{ //�ٷ� ���� ���� �ε�� ����
	// TODO: Add your command handler code here
	CFile file;
	file.Open(_T("save.bu"),CFile::modeRead);
	CArchive ar(&file,CArchive::load); // 

	ar >>m_iData_clear>>m_iData_time;
	CString tmp;
	//tmp.Format("Stage %d(%.2fSec Cleared.) Loading..",m_iData_clear,m_iData_time);
	MessageBox(tmp);
	m_iClear = m_iData_clear;
	OnStart(); // ���� ���������̶� �ҷ��� ������������ �ٽ� �ʱ�ȭ�ϰ� ����.
	
}

void CmfcGameView::OnSave() 
{ // ������ Ŭ���� �ߴ����� Ŭ���� �ð��� ����.
	// TODO: Add your command handler code here
	CFile file;
	file.Open(_T("save.bu"),CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	CString tmp;
	//tmp.Format("Stage %d(%.2fSec Cleared.) Saving..",m_iData_clear,m_iData_time);
	MessageBox(tmp);
	ar <<m_iClear<<m_iData_time;
	
}