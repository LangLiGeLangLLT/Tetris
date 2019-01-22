#pragma once
class CPiece
{
	friend class CGrid;
	friend class CTetrisDlg;

public:
	CPiece();
	~CPiece();
	void ChangePieceType();
	int GetChangedType(int nSrcType);
	int GetRowID(int nColumn);
	void MovePiece(int nHor, int nVer, int nColCount);
	void InitPiece();

private:
	int		m_nLeftIndex;		// 图像左边索引
	int		m_nTopIndex;		// 图像顶部索引
	int		m_nType;			// 类型
	int		m_nRowCount;		// 图像占用行数
	int		m_nWidth;			// 图像的宽度，单位为一个单元格
	CPoint	m_ImagesPT[4];		// 图像的构成，表示方块使用的4个方块
	BOOL	m_bMoving;			// 移动过程中

	void SetTopIndex(int nTopIndex);
	void SetPieceType(int nType);
};

