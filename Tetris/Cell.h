#pragma once
class CCell
{
	friend class CGrid;
	friend class CTetrisDlg;

public:
	CCell();
	~CCell();

private:
	int		m_nRowIndex;		// ��Ԫ��������
	int		m_nColIndex;		// ��Ԫ��������
	BOOL	m_bUsed;			// �Ƿ�ʹ��
	BOOL	m_bFixed;			// �Ƿ񱻹̶�
};

