
// TetrisDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTetrisDlg 对话框



CTetrisDlg::CTetrisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pGrid = new CGrid(CRect(10, 10, 310, 410));
	m_bKeyDown = FALSE;
	m_nKeyDown = 0;
	m_nGrade = 0;
	m_nLevel = 500;
	m_bGameRunning = FALSE;
	m_bPaused = FALSE;
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEXTPIECE, m_NextPiece);
	DDX_Control(pDX, IDC_GRADE, m_Grade);
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BEGIN_GAME, &CTetrisDlg::OnBeginGame)
	ON_BN_CLICKED(IDC_PAUSE, &CTetrisDlg::OnPause)
	ON_BN_CLICKED(IDC_CONTINUE, &CTetrisDlg::OnContinue)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTetrisDlg 消息处理程序

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetNextPiece();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTetrisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	m_pGrid->DrawGrid(GetDC());
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTetrisDlg::Accelerate()
{
	KillTimer(1);
	SetTimer(1, 1, NULL);
}

BOOL CTetrisDlg::GameOver()
{
	for (int j = 0; j < m_pGrid->m_nColCount; j++)
	{
		if (m_pGrid->m_CellGrid[0][j].m_bFixed)
			return TRUE;
	}
	return FALSE;
}

void CTetrisDlg::BeginNewPiece()
{
	m_nNextPiece = GetRandomPiece();
	CBitmap bmp;
	bmp.LoadBitmap(m_mapNextPiece[m_nNextPiece]);
	m_NextPiece.SetBitmap(bmp);
	bmp.DeleteObject();
	m_Piece.InitPiece();
	m_Piece.SetPieceType(m_nCurPiece);
	m_nCurPiece = m_nNextPiece;
	SetTimer(1, m_nLevel, NULL);
}

int CTetrisDlg::GradeHandle(CPiece & refPiece)
{
	int nTop = refPiece.m_nTopIndex;
	int nBottom = refPiece.m_nTopIndex + refPiece.m_nRowCount - 1;

	int nFillCount = 0;						//记录总的填充行数
	int nFillRowList[4] = { -1, -1, -1, -1 };	//记录哪些行被完全填充
	for (int i = nTop; i <= nBottom; i++)
	{
		int nFixedCol = 0;

		for (int j = 0; j < m_pGrid->m_nColCount; j++)
		{
			if (m_pGrid->m_CellGrid[i][j].m_bFixed == TRUE)
				nFixedCol++;
		}
		if (nFixedCol == m_pGrid->m_nColCount)	//当前行被完全填充
		{
			nFillRowList[nFillCount] = i;	//记录当前行索引
			nFillCount++;
		}
	}

	int nGrade = 0;
	if (nFillCount > 1)
	{
		nGrade = nFillCount * 200;
	}
	else
	{
		nGrade = nFillCount * 100;
	}

	if (nFillCount > 0)	//某一行的所有列被完全填充
	{
		for (int n = 0; n < 4; n++)
		{
			if (nFillRowList[n] != -1)	//该行被完全填充，进行处理
			{
				//去除该行的填充标记
				for (int j = 0; j < m_pGrid->m_nColCount; j++)
				{
					m_pGrid->m_CellGrid[nFillRowList[n]][j].m_bFixed = FALSE;
				}
				for (int i = nFillRowList[n] - 1; i >= 0; i--)
				{
					for (int j = 0; j < m_pGrid->m_nColCount; j++)
					{
						m_pGrid->m_CellGrid[i + 1][j] = m_pGrid->m_CellGrid[i][j];
					}
				}

				for (int j = 0; j < m_pGrid->m_nColCount; j++)
				{
					m_pGrid->m_CellGrid[0][j].m_bFixed = FALSE;
				}
			}
		}
		m_nGrade += nGrade;
		CString szGrade;
		szGrade.Format(TEXT("分数： %d"), m_nGrade);
		m_Grade.SetWindowText(szGrade);
	}
	return nGrade;
}

int CTetrisDlg::GetRandomPiece()
{
	static std::default_random_engine e((unsigned)time(0));
	static std::uniform_int_distribution<unsigned> u(1, 7);
	int nRet = u(e);
	return nRet;
}

void CTetrisDlg::ChangePieceType(int nSrcType)
{
	if (m_Piece.m_bMoving == FALSE)
	{
		return;
	}
	BOOL bRet = m_pGrid->GetBottomRowIndex(m_Piece.m_nLeftIndex, m_Piece.m_nWidth, m_Piece);
	if (bRet)
	{
		return;
	}
	//图像是否允许变形
	if (!m_pGrid->IsAllowChangeType(m_Piece))
	{
		return;
	}
	m_Piece.ChangePieceType();
	HorMovePiece(0);
}

void CTetrisDlg::HorMovePiece(int nOffset)
{
	if (m_Piece.m_bMoving == FALSE)
	{
		return;
	}
	//防止左右穿透图像
	BOOL bLeftMove = (nOffset < 1) ? TRUE : FALSE;
	if (!m_pGrid->IsAllowHorMove(m_Piece, bLeftMove))
	{
		//如果不能左右移动，则在OnTimer中继续向下移动
		m_bKeyDown = FALSE;
		return;
	}

	m_Piece.MovePiece(m_Piece.m_nLeftIndex + nOffset, m_Piece.m_nTopIndex, COL_COUNT);
	//显示图像
	for (int i = 0; i < 4; i++)
	{
		int nX = m_Piece.m_ImagesPT[i].x;
		int nY = m_Piece.m_ImagesPT[i].y;
		m_pGrid->m_CellGrid[nY][nX].m_bUsed = TRUE;
	}

	m_pGrid->DrawGrid(GetDC());
	//在绘制下一次图像时使之前的图像消失
	for (int i = 0; i < 4; i++)
	{
		int nX = m_Piece.m_ImagesPT[i].x;
		int nY = m_Piece.m_ImagesPT[i].y;
		m_pGrid->m_CellGrid[nY][nX].m_bUsed = FALSE;
	}

	BOOL bRet = m_pGrid->GetBottomRowIndex(m_Piece.m_nLeftIndex, m_Piece.m_nWidth, m_Piece);
	if (bRet)
	{
		for (int i = 0; i < 4; i++)
		{
			int nX = m_Piece.m_ImagesPT[i].x;
			int nY = m_Piece.m_ImagesPT[i].y;
			m_pGrid->m_CellGrid[nY][nX].m_bUsed = FALSE;
			if (m_nKeyDown > 3)
			{
				m_pGrid->m_CellGrid[nY][nX].m_bFixed = TRUE;
				m_Piece.m_bMoving = FALSE;
				GradeHandle(m_Piece);
				if (GameOver())
				{
					m_bGameRunning = FALSE;
					MessageBox(TEXT("游戏结束!"));
				}
			}
		}
	}
}

void CTetrisDlg::OnCancel()
{
	delete m_pGrid;
	CDialogEx::OnCancel();
}

void CTetrisDlg::SetNextPiece()
{
	m_mapNextPiece[1] = IDB_TYPE1;
	m_mapNextPiece[2] = IDB_TYPE2;
	m_mapNextPiece[3] = IDB_TYPE3;
	m_mapNextPiece[4] = IDB_TYPE4;
	m_mapNextPiece[5] = IDB_TYPE5;
	m_mapNextPiece[6] = IDB_TYPE6;
	m_mapNextPiece[7] = IDB_TYPE7;
}

void CTetrisDlg::PlayBGM()
{
	m_res = FindResource(::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_BGM), TEXT("WAVE"));
	m_hSound = LoadResource(::AfxGetApp()->m_hInstance, m_res);
	m_lpSound = (LPCWSTR)LockResource(m_hSound);

	PlaySound(m_lpSound, AfxGetApp()->m_hInstance, SND_LOOP | SND_ASYNC | SND_MEMORY);
}

void CTetrisDlg::StopPlayBGM()
{
	PlaySound(NULL, NULL, SND_FILENAME);
}

void CTetrisDlg::StartPlayBGM()
{
	PlaySound(m_lpSound, AfxGetApp()->m_hInstance, SND_LOOP | SND_ASYNC | SND_MEMORY);
}

void CTetrisDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_bGameRunning)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			m_bKeyDown = FALSE;
			if (pMsg->wParam == VK_LEFT)
			{
				m_bKeyDown = TRUE;
				m_nKeyDown++;
				//向左移动
				HorMovePiece(-1);
			}
			else if (pMsg->wParam == VK_RIGHT)
			{
				m_bKeyDown = TRUE;
				m_nKeyDown++;
				//向右移动
				HorMovePiece(1);
			}
			else if (pMsg->wParam == VK_UP)
			{
				//变形
				ChangePieceType(m_Piece.m_nType);
			}
			else if (pMsg->wParam == VK_DOWN)
			{
				//加速
				Accelerate();
			}
			return TRUE;
		}
		else if (pMsg->message == WM_KEYUP)
		{
			m_bKeyDown = FALSE;
			m_nKeyDown = 0;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bKeyDown && m_nKeyDown < 3)
	{
		return;
	}
	if (!m_Piece.m_bMoving)		//图像已经移动到底部
	{
		KillTimer(1);
		BeginNewPiece();
		return;
	}
	//显示图像
	for (int i = 0; i < 4; i++)
	{
		int nX = m_Piece.m_ImagesPT[i].x;
		int nY = m_Piece.m_ImagesPT[i].y;
		m_pGrid->m_CellGrid[nY][nX].m_bUsed = TRUE;
	}
	m_pGrid->DrawGrid(GetDC());
	//在绘制下一次图像时使之前的图像消失
	for (int i = 0; i < 4; i++)
	{
		int nX = m_Piece.m_ImagesPT[i].x;
		int nY = m_Piece.m_ImagesPT[i].y;
		m_pGrid->m_CellGrid[nY][nX].m_bUsed = FALSE;
	}

	//获取表格中底部的某些列的图像高度
	BOOL bRet = m_pGrid->GetBottomRowIndex(m_Piece.m_nLeftIndex, m_Piece.m_nWidth, m_Piece);
	//如果当前图像没有达到所在列的已有图像的高度，继续向下移动图像
	if (!bRet)
	{
		m_Piece.SetTopIndex(m_Piece.m_nTopIndex + 1);
	}
	else		//图像移动到结尾，在表格底部固定图像
	{
		for (int i = 0; i < 4; i++)
		{
			int nX = m_Piece.m_ImagesPT[i].x;
			int nY = m_Piece.m_ImagesPT[i].y;
			m_pGrid->m_CellGrid[nY][nX].m_bUsed = FALSE;
			m_pGrid->m_CellGrid[nY][nX].m_bFixed = TRUE;
		}
		m_Piece.m_bMoving = FALSE;
		KillTimer(1);
		GradeHandle(m_Piece);

		if (GameOver())
		{
			m_bGameRunning = FALSE;
			MessageBox(TEXT("游戏结束"));
		}
		else
		{
			BeginNewPiece();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTetrisDlg::OnBeginGame()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pGrid->InitCellGrid();
	m_nCurPiece = GetRandomPiece();
	m_Grade.SetWindowText(TEXT("分数： 0"));
	m_nGrade = 0;
	BeginNewPiece();
	m_bGameRunning = TRUE;
	PlayBGM();
}


void CTetrisDlg::OnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bGameRunning)
	{
		if (m_bPaused == FALSE)
		{
			KillTimer(1);
			m_bPaused = TRUE;
			StopPlayBGM();
		}
	}
}


void CTetrisDlg::OnContinue()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bGameRunning)
	{
		if (m_bPaused == TRUE)
		{
			SetTimer(1, m_nLevel, NULL);
			m_bPaused = FALSE;
			StartPlayBGM();
		}
	}
}


HBRUSH CTetrisDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CTetrisDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	UnlockResource(m_hSound);
	FreeResource(m_hSound);
	return CDialogEx::DestroyWindow();
}
