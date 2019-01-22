#pragma once
class CCell
{
	friend class CGrid;
	friend class CTetrisDlg;

public:
	CCell();
	~CCell();

private:
	int		m_nRowIndex;		// 单元格行索引
	int		m_nColIndex;		// 单元格列索引
	BOOL	m_bUsed;			// 是否被使用
	BOOL	m_bFixed;			// 是否被固定
};

