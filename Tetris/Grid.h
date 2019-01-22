#pragma once

#include "Cell.h"
#include "Piece.h"
#include "resource.h"

const int ROW_COUNT = 20;
const int COL_COUNT = 15;

class CGrid
{
	friend class CTetrisDlg;

public:
	CGrid();
	CGrid(CRect rc);
	~CGrid();
	BOOL IsAllowChangeType(CPiece &refPiece);							// 是否允许变形
	BOOL IsAllowHorMove(CPiece &refPiece, BOOL bMoveLeft = TRUE);		// 是否允许水平移动
	BOOL GetBottomRowIndex(int nColumn, int nSize, CPiece &refPiece);
	void DrawGrid(CDC* pDC);											// 绘制表格

private:
	int		m_nRowCount;							// 行数
	int		m_nColCount;							// 列数
	int		m_nCellWidth;							// 单元格宽度
	int		m_nCellHeight;							// 单元格高度
	CRect	m_GridRC;								// 表格区域
	CBitmap m_Bmp;									// 单元格位图
	CBitmap m_BkBmp;								// 表格背景位图
	CCell	m_CellGrid[ROW_COUNT][COL_COUNT];		// 单元格集合

	void InitCellGrid();							// 初始化单元格
};

