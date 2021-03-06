
// TetrisDlg.h: 头文件
//

#pragma once

#include "Grid.h"
#include "MMsystem.h"
#pragma comment(lib,"winmm.lib")

#include <map>
#include <random>

// CTetrisDlg 对话框
class CTetrisDlg : public CDialogEx
{
// 构造
public:
	CTetrisDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRIS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void Accelerate();
	BOOL GameOver();
	void BeginNewPiece();
	int GradeHandle(CPiece &refPiece);
	int GetRandomPiece();
	void ChangePieceType(int nSrcType);
	void HorMovePiece(int nOffset);
	void OnCancel();
	void SetNextPiece();
	void PlayBGM();
	void StopPlayBGM();
	void StartPlayBGM();

private:
	CGrid*		m_pGrid;			// 表格对象
	CPiece		m_Piece;			// 方块图像
	BOOL		m_bKeyDown;			// 是否按键
	int			m_nKeyDown;			// 按键的次数
	int			m_nGrade;			// 记录游戏分数
	int			m_nCurPiece;		// 当前方块编号
	int			m_nNextPiece;		// 下一个方块编号
	int			m_nLevel;			// 游戏级别
	BOOL		m_bGameRunning;		// 游戏进行中
	BOOL		m_bPaused;			// 游戏是否暂停
	HRSRC		m_res;
	HANDLE		m_hSound;
	LPCWSTR		m_lpSound;

public:
	CStatic m_NextPiece;
	CStatic m_Grade;
	std::map<int, int> m_mapNextPiece;
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBeginGame();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL DestroyWindow();
};
