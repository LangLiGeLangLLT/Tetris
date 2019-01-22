#include "stdafx.h"
#include "Grid.h"


CGrid::CGrid()
{
}

CGrid::CGrid(CRect rc)
{
	m_GridRC = rc;
	m_nRowCount = ROW_COUNT;
	m_nColCount = COL_COUNT;
	m_nCellHeight = m_GridRC.Height() / m_nRowCount + 1;		// 单元格高度
	m_nCellWidth = m_GridRC.Width() / m_nColCount + 1;			// 单元格宽度
	m_Bmp.LoadBitmapW(IDB_CELLBMP);
	m_BkBmp.LoadBitmapW(IDB_BKBMP);
	InitCellGrid();
}


CGrid::~CGrid()
{
}

BOOL CGrid::IsAllowChangeType(CPiece &refPiece)
{
	//如果图像处于左边缘，不允许变形
	if (refPiece.m_nType == 33 || refPiece.m_nType == 35 ||
		refPiece.m_nType == 44 || refPiece.m_nType == 46 ||
		refPiece.m_nType == 11 || refPiece.m_nType == 55 ||
		refPiece.m_nType == 57 || refPiece.m_nType == 66 ||
		refPiece.m_nType == 77)
	{
		if (refPiece.m_nLeftIndex == 0)
		{
			return FALSE;
		}
		else if (refPiece.m_nLeftIndex >= COL_COUNT - 2 &&
			(refPiece.m_nType == 11 || refPiece.m_nType == 55 ||
				refPiece.m_nType == 57 || refPiece.m_nType == 66 ||
				refPiece.m_nType == 77))
		{
			return FALSE;
		}
	}
	//定义一个临时的piece,进行图像转换，判断转换后的图像是否合法，以决定当前图像是否允许变形
	//图像是否合法的检测是通过该图像是否在表格中已被占用来决定的
	CPiece piece = refPiece;
	piece.ChangePieceType();

	for (int i = 0; i < 4; i++)
	{
		int nColIndex = piece.m_ImagesPT[i].x;
		int nRowIndex = piece.m_ImagesPT[i].y;

		if (m_CellGrid[nRowIndex][nColIndex].m_bFixed)
			return FALSE;
	}
	return TRUE;
}

BOOL CGrid::IsAllowHorMove(CPiece &refPiece, BOOL bMoveLeft)
{
	//遍历Piece的4个单元格
	for (int i = 0; i < 4; i++)
	{
		int nColIndex = refPiece.m_ImagesPT[i].x;
		int nRowIndex = refPiece.m_ImagesPT[i].y;
		if (bMoveLeft)	//能否向左移动
		{
			int nGridCol = nColIndex - 1;
			if (nGridCol < 0)
				return FALSE;
			if (m_CellGrid[nRowIndex][nGridCol].m_bFixed)
				return FALSE;
		}
		else //能否向右移动	
		{
			int nGridCol = nColIndex + 1;
			if (nGridCol >= m_nColCount)
				return FALSE;
			if (m_CellGrid[nRowIndex][nGridCol].m_bFixed)
				return FALSE;
		}
	}
	return TRUE;
}

BOOL CGrid::GetBottomRowIndex(int nColumn, int nSize, CPiece &refPiece)
{
	//获取Piece图像的底部索引
	int nBottom = refPiece.m_nTopIndex + refPiece.m_nRowCount;
	if (nBottom >= m_nRowCount)
		return TRUE;
	//遍历Piece的4个单元格
	for (int n = 0; n < 4; n++)
	{
		int nColIndex = refPiece.m_ImagesPT[n].x;
		int nRowIndex = refPiece.m_ImagesPT[n].y;
		int nGridRow = nRowIndex + 1;
		if (nGridRow >= m_nRowCount - 1)
			nGridRow = m_nRowCount - 1;
		if (m_CellGrid[nGridRow][nColIndex].m_bFixed)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CGrid::DrawGrid(CDC* pDC)
{
	// 绘制单元格
	for (int m = 0; m < m_nRowCount; ++m)
	{
		for (int n = 0; n < m_nColCount; ++n)
		{
			// 计算单元格区域
			CRect cellRC;
			cellRC.left = m_GridRC.left + n * m_nCellWidth;
			cellRC.right = cellRC.left + m_nCellWidth;
			cellRC.top = m_GridRC.top + m * m_nCellHeight;
			cellRC.bottom = cellRC.top + m_nCellHeight;

			CDC memDC;
			memDC.CreateCompatibleDC(pDC);
			if (m_CellGrid[m][n].m_bUsed == TRUE || m_CellGrid[m][n].m_bFixed == TRUE)
			{
				// 使用位图填充单元格
				memDC.SelectObject(&m_Bmp);
				pDC->BitBlt(cellRC.left, cellRC.top, cellRC.Width(), cellRC.Height(), &memDC, 0, 0, SRCCOPY);
			}
			else
			{
				// 使用位图填充单元格
				memDC.SelectObject(&m_BkBmp);
				pDC->BitBlt(cellRC.left, cellRC.top, cellRC.Width(), cellRC.Height(), &memDC, 0, 0, SRCCOPY);
			}
			memDC.DeleteDC();
		}
	}
	// 绘制边框
	CRect clientRC;
	clientRC.left = m_GridRC.left;
	clientRC.top = m_GridRC.top;
	clientRC.right = clientRC.left + m_nCellWidth * m_nColCount;
	clientRC.bottom = clientRC.top + m_nCellHeight * m_nRowCount;
	pDC->FrameRect(clientRC, &CBrush(RGB(0, 0, 255)));
}

void CGrid::InitCellGrid()
{
	for (int i = 0; i < ROW_COUNT; ++i)
	{
		for (int j = 0; j < COL_COUNT; ++j)
		{
			m_CellGrid[i][j].m_nRowIndex = i;
			m_CellGrid[i][j].m_nColIndex = j;
			m_CellGrid[i][j].m_bUsed = FALSE;
			m_CellGrid[i][j].m_bFixed = FALSE;
		}
	}
}
