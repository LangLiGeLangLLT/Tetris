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
	int		m_nLeftIndex;		// ͼ���������
	int		m_nTopIndex;		// ͼ�񶥲�����
	int		m_nType;			// ����
	int		m_nRowCount;		// ͼ��ռ������
	int		m_nWidth;			// ͼ��Ŀ�ȣ���λΪһ����Ԫ��
	CPoint	m_ImagesPT[4];		// ͼ��Ĺ��ɣ���ʾ����ʹ�õ�4������
	BOOL	m_bMoving;			// �ƶ�������

	void SetTopIndex(int nTopIndex);
	void SetPieceType(int nType);
};

