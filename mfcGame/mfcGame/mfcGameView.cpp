
// mfcGameView.cpp : CmfcGameView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmfcGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CmfcGameView 생성/소멸

CmfcGameView::CmfcGameView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
	m_bGame = FALSE; // 시작하면 트루
	m_iClear = 0; // 몇판 클리어 했는지.
	Enemy_num = 5;
	m_iData_time = 0;
	m_iData_clear = 0;
}

CmfcGameView::~CmfcGameView()
{
}

BOOL CmfcGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CmfcGameView 그리기

void CmfcGameView::OnDraw(CDC* pDC)
{
	CmfcGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	if(!m_bGame){ //인트로 화면
		CBitmap bitmap1;
		bitmap1.LoadBitmap(IDB_BG1);
		CBitmap *pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap1);
		pDC->BitBlt(0,0,545,440,&MemDC,0,0,SRCCOPY);
		return;
	}

	CBitmap bitmap1; // 가리는 화면
	bitmap1.LoadBitmap(IDB_COVER);
	CBitmap *pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap1);
	pDC->BitBlt(0,0,845,585,&MemDC,0,0,SRCCOPY);

	CBitmap bitmap2; // 가려진 화면
	bitmap2.LoadBitmap(IDB_BG);
	pOldBitmap1 = (CBitmap *)MemDC.SelectObject(&bitmap2);
	
	for(int i=0;i<540;i++) // 내땅으로 표시된 1은 그려준다.
		for(int j=0;j<MAX_Y;j++)
			if(m_land[i][j] == 1)
			pDC->BitBlt(i,j,1,1,&MemDC,i,j,SRCCOPY);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CmfcGameView 인쇄

BOOL CmfcGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CmfcGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CmfcGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}



// CmfcGameView 진단

#ifdef _DEBUG
void CmfcGameView::AssertValid() const
{
	CView::AssertValid();
}

void CmfcGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfcGameDoc* CmfcGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcGameDoc)));
	return (CmfcGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcGameView 메시지 처리기
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

	if(m_pCurLn) //현재 땅을 먹는 중이고
		if (m_land[m_cHero.x][m_cHero.y] == 1 ) // 내 땅에 왔을때.
		{	
			//MessageBox("우리땅");
			CPoint tmp ,tmp1;
			tmp = m_pCurLn->Get_big_point(); // 현재 땅덩어리의 가장 큰 좌표 찾기
			tmp1 =m_pCurLn->Get_small_point(); // 작은 좌표 찾기.

			for(int i=tmp1.x;i<tmp.x;i++)
				for(int j=tmp1.y;j<tmp.y;j++){
					m_land[i][j] = 1; // 최대,최소 좌표 구해서 먹기. 1로 표시
					
					for(int k=0;k<Enemy_num;k++)
						if(m_cEnemy[k].x == i && m_cEnemy[k].y ==j)
						{ //적이 내 범위안에 있으면 저장.
							m_cBoom[kill].x = i;
							m_cBoom[kill++].y = j;//사살한 적 카운트.
						}
					if(i == m_cEnemy[4].x && j ==m_cEnemy[4].y)
					{
						MessageBox(_T("시간을 0으로 되돌립니다~"));
						Count = 0;
					}
					
					Count_land++; //땅의 수 증가
				}
	
			//	
			//land.Format("우리땅 : %.2f    Stage : %d", Count_land*0.00046, m_iClear+1); //  땅을 몇 %먹었나 측정
			////pFrame->m_wndStatusBar.SetPaneText(0, land);
			//land.Format("KILL : %2d", kill); //  몇 명죽였나.
			////pFrame->m_wndStatusBar.SetPaneText(3, land);

			m_pCurLn = NULL;
			Invalidate();
			return;
		}
	else //땅을 먹는 중이 아니고
		if (m_land[m_cHero.x][m_cHero.y] == 1 ) //내 땅을 돌아 다닐 때
		{	
			m_pCurLn = NULL;
			return;
		}

	if(m_land[m_cHero.x][m_cHero.y] == 0) // 안 먹은 땅이므로 땅 객체 만들기.
	{
		if(m_pCurLn) 
		{ // 새로 땅을 먹는 중일때 계속 저장.
			m_pCurLn->AddPoint(&m_cHero);
			m_land[m_cHero.x][m_cHero.y] = 1;
			for(int k = 0; k < 5; k++)
				for(int k1 = 0; k1 < 5; k1++)
					m_land[m_cHero.x+k][m_cHero.y+k1] =1; //움직인 흔적도 내땅으로.
			Count_land++;
		}	
		else 
		{ // 현재 땅 객체을 새로 만들고 땅 먹기 시작
			m_pCurLn = GetDocument()->GetNewLand();
			m_pCurLn->AddPoint(&m_cHero);
			//m_land[m_cHero.x][m_cHero.y] = 1;
			for(int k2 = 0; k2 < 5; k2++)
				for(int k3 = 0; k3 < 5; k3++)
				m_land[m_cHero.x+k2][m_cHero.y+k3] =1; //움직인 흔적도 내땅으로.
			Count_land++;
		}		
	}	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



int CmfcGameView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0,30,NULL); // 주인공 타이머
	SetTimer(1,6000,NULL); // 적들 타이머

	return 0;
}

void CmfcGameView::OnTimer(UINT nIDEvent) 
{
	if(!m_bGame) return;

	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap;
		
	CBitmap bitmap1;// 가려진 배경
	bitmap1.LoadBitmap(IDB_BG);
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap1);
	dc.BitBlt(m_Prev.x,m_Prev.y,5,5,&MemDC,m_Prev.x,m_Prev.y,SRCCOPY);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_HERO); //주인공 그리기
	pOldBitmap = MemDC.SelectObject(&bitmap);
	dc.BitBlt(m_cHero.x,m_cHero.y,5,5,&MemDC,5*x,0,SRCCOPY);

	CBitmap bitmap21;// 죽인 적을 나타냄.
	bitmap21.LoadBitmap(IDB_BOOM);
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap21);
	for(int i=0;i<kill;i++)//죽인 자리 표시.
		dc.BitBlt(m_cBoom[i].x,m_cBoom[i].y,35,35,&MemDC,0,0,SRCCOPY);

	if(Count++ < 3000 && Count_land > (216000*0.6) && kill >= 5) 
	{
		m_bGame=FALSE;
		++m_iClear;
		m_iData_time = Count*0.025; // 클리어시간 저장.
		MessageBox(_T("Mission Clear!!"));
	}
	else if(Count++ > 3000) 
	{
		m_bGame=FALSE;MessageBox(_T("Time Over!"));
		exit(1);
	}
	// 클리어 종료 조건
	
	if(nIDEvent == 1)
	{ //타이머 두개 설정해서.

		for(int i=0;i<Enemy_num;i++)
		{
			m_cEnemy[i].x = rand()%MAX_X;
			m_cEnemy[i].y = rand()%MAX_Y;

			if(m_land[m_cEnemy[i].x][m_cEnemy[i].y] == 0) // 새로 받은 좌표값이 안 먹은 땅일 때만.
			{
				CBitmap bitmap3;
				bitmap3.LoadBitmap(IDB_COVER); // 흔적 지우기
				pOldBitmap = (CBitmap *)MemDC.SelectObject(&bitmap3);
				dc.BitBlt(m_cPrev_enemy[i].x,m_cPrev_enemy[i].y,25,25,&MemDC,0,0,SRCCOPY);
				
				if(i==4) { // 아이템 뿌리기.
					CBitmap bitmap211;
					bitmap211.LoadBitmap(IDB_CLOCK);
					pOldBitmap = MemDC.SelectObject(&bitmap211);
					dc.BitBlt(m_cEnemy[i].x,m_cEnemy[i].y,25,25,&MemDC,0,0,SRCCOPY);
					dc.SelectObject(pOldBitmap);
				}
				else{
					CBitmap bitmap2; // 적들 그리기.
					bitmap2.LoadBitmap(IDB_ENEMY);
					pOldBitmap = MemDC.SelectObject(&bitmap2);
					dc.BitBlt(m_cEnemy[i].x,m_cEnemy[i].y,25,25,&MemDC,25*(rand()%4),0,SRCCOPY);
					dc.SelectObject(pOldBitmap);
				}
				
				m_cPrev_enemy[i] = m_cEnemy[i];
			}
		}
	}
	CString tmp; // 카운트 세기.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	/*tmp.Format(" %3.1f Sec",Count*0.025);
	pFrame->m_wndStatusBar.SetPaneText(2, tmp);
	tmp.Format("지금은 내땅! 적을 죽여");
	pFrame->m_wndStatusBar.SetPaneText(1, tmp);*/
	
	if(m_pCurLn)
	{// 현재 땅을 먹는 중이고
		/*tmp.Format("현재 땅을 먹고 있는중! 적 조심!");
		pFrame->m_wndStatusBar.SetPaneText(1, tmp);*/

		for(int j=0;j < m_pCurLn->m_Line.GetSize();j++)
		{					
			CPoint *p2 = (CPoint*)m_pCurLn->m_Line.GetAt(j);
			for(int k=0;k<Enemy_num;k++)
			if(m_cEnemy[k].x <= p2->x && p2->x<=m_cEnemy[k].x+25 &&
				m_cEnemy[k].y <= p2->y && p2->y <=m_cEnemy[k].y+25)
			{ //현재 움직이고 있는 흔적을 닿으면 죽는다.
			m_bGame = FALSE;
			MessageBox(_T("적에게 들켰기 때문에 게임은 중단됩니다"));
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
	if(m_iClear >= 1 && m_iClear < 2 )  Enemy_num=7; // 레벨 지정.
	if(m_iClear >= 2 && m_iClear < 3 )  Enemy_num=10;
	for(int i=0;i<100;i++)
		m_cBoom[i] = -30;
	Count_land=0;
	Count = 0;
	m_cHero.x = 0;
	m_cHero.y = 0;
	m_Prev = 0;	
	x=0; // 주인공 애니매이션용
	m_pCurLn = NULL;

	for(int i=0;i<10;i++)
	{
		m_cEnemy[i].x = rand()%MAX_X;
		m_cEnemy[i].y = rand()%MAX_Y;
		m_cPrev_enemy[i] = -1;
	}
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
			m_land[i][j] = 0; // 초기화
	
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<5;j++)
		{
			m_land[i][0+j] = 1;
			m_land[i][MAX_Y-j]= 1; // 벽 1로 초기화
		}
	for(int i=0;i<MAX_Y;i++) 
		for(int j1=0;j1<5;j1++)
		{
			m_land[0+j1][i] = 1;
			m_land[MAX_X-j1][i] = 1;  // 벽 1로 초기화
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
	if (m_iClear != 0 && !m_bGame) pCmdUI->Enable(); // 게임정지와 한판은 클리어 했을때만 저장 가능
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
	x=0; // 주인공 애니매이션용
	m_iClear = 0; // 몇판 클리어 했는지.
	m_pCurLn = NULL;
	for(int i=0;i<10;i++)
	{
		m_cEnemy[i].x = 100;//rand()%MAX_X;
		m_cEnemy[i].y = 100;//rand()%MAX_Y;
		m_cPrev_enemy[i] = -1;
	}
	
	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
			m_land[i][j] = 0; // 초기화

	for(int i=0;i<MAX_Y;i++) 
	{
		m_land[i][0] = 1;
		m_land[i][MAX_Y]= 1; // 벽 1로 초기화
	}
		
	for(int i=0;i<MAX_X;i++) 
	{
		m_land[0][i] = 1;
		m_land[MAX_X][i] = 1;  // 벽 1로 초기화
	}
	Invalidate();
	//GetDocument()-UpdateAllData();
}


void CmfcGameView::OnLoad() 
{ //바로 직전 게임 로드와 시작
	// TODO: Add your command handler code here
	CFile file;
	file.Open(_T("save.bu"),CFile::modeRead);
	CArchive ar(&file,CArchive::load); // 

	ar >>m_iData_clear>>m_iData_time;
	CString tmp;
	//tmp.Format("Stage %d(%.2fSec Cleared.) Loading..",m_iData_clear,m_iData_time);
	MessageBox(tmp);
	m_iClear = m_iData_clear;
	OnStart(); // 한판 단위게임이라 불러온 스테이지부터 다시 초기화하고 시작.
	
}

void CmfcGameView::OnSave() 
{ // 몇판을 클리어 했는지와 클리어 시간도 저장.
	// TODO: Add your command handler code here
	CFile file;
	file.Open(_T("save.bu"),CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	CString tmp;
	//tmp.Format("Stage %d(%.2fSec Cleared.) Saving..",m_iData_clear,m_iData_time);
	MessageBox(tmp);
	ar <<m_iClear<<m_iData_time;
	
}