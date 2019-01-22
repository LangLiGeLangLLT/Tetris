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
	BOOL IsAllowChangeType(CPiece &refPiece);							// �Ƿ��������
	BOOL IsAllowHorMove(CPiece &refPiece, BOOL bMoveLeft = TRUE);		// �Ƿ�����ˮƽ�ƶ�
	BOOL GetBottomRowIndex(int nColumn, int nSize, CPiece &refPiece);
	void DrawGrid(CDC* pDC);											// ���Ʊ��

private:
	int		m_nRowCount;							// ����
	int		m_nColCount;							// ����
	int		m_nCellWidth;							// ��Ԫ����
	int		m_nCellHeight;							// ��Ԫ��߶�
	CRect	m_GridRC;								// �������
	CBitmap m_Bmp;									// ��Ԫ��λͼ
	CBitmap m_BkBmp;								// ��񱳾�λͼ
	CCell	m_CellGrid[ROW_COUNT][COL_COUNT];		// ��Ԫ�񼯺�

	void InitCellGrid();							// ��ʼ����Ԫ��
};

