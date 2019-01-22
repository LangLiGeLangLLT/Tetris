#include "stdafx.h"
#include "Piece.h"


CPiece::CPiece()
{
	m_nLeftIndex = 5;
	m_nTopIndex = 0;
	m_nType = 0;
	m_nRowCount = 1;
	m_bMoving = TRUE;
	m_nWidth = 3;
}


CPiece::~CPiece()
{
}

void CPiece::ChangePieceType()
{
	int nDesType = GetChangedType(m_nType);
	if (m_nType == 1)
	{
		m_nLeftIndex++;
	}
	else if (m_nType == 11)
	{
		m_nLeftIndex--;
	}
	else if (m_nType == 3)
	{
		m_nLeftIndex++;
	}
	else if (m_nType == 33)
	{
		m_nLeftIndex--;
	}
	else if (m_nType == 34)
	{
		m_nLeftIndex++;
	}
	else if (m_nType == 35)
	{
		m_nLeftIndex--;
	}
	else if (m_nType == 4)
	{
		m_nLeftIndex++;
	}
	else if (m_nType == 44)
	{
		m_nLeftIndex--;
	}
	else if (m_nType == 45)
	{
		m_nLeftIndex++;
	}
	else if (m_nType == 46)
	{
		m_nLeftIndex--;
	}
	SetPieceType(nDesType);
}

int CPiece::GetChangedType(int nSrcType)
{
	if (nSrcType == 1)
	{
		return 11;
	}
	else if (nSrcType == 11)
	{
		return 1;
	}
	else if (nSrcType == 3)
	{
		return 33;
	}
	else if (nSrcType == 33)
	{
		return 34;
	}
	else if (nSrcType == 34)
	{
		return 35;
	}
	else if (nSrcType == 35)
	{
		return 3;
	}
	else if (nSrcType == 4)
	{
		return 44;
	}
	else if (nSrcType == 44)
	{
		return 45;
	}
	else if (nSrcType == 45)
	{
		return 46;
	}
	else if (nSrcType == 46)
	{
		return 4;
	}
	else if (nSrcType == 5)
	{
		return 55;
	}
	else if (nSrcType >= 55 && nSrcType <= 57)
	{
		if (nSrcType == 57)
			return 5;
		else
			return ++nSrcType;
	}
	else if (nSrcType == 6)
	{
		return 66;
	}
	else if (nSrcType == 66)
	{
		return 6;
	}
	else if (nSrcType == 7)
	{
		return 77;
	}
	else if (nSrcType == 77)
	{
		return 7;
	}
	else if (nSrcType == 2)
	{
		return 2;
	}
	return 0;
}

int CPiece::GetRowID(int nColumn)
{
	int nBottom = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_ImagesPT[i].x == nColumn)
		{
			if (nBottom < m_ImagesPT[i].y)
				nBottom = m_ImagesPT[i].y;
		}
	}
	return nBottom;
}

void CPiece::MovePiece(int nHor, int nVer, int nColCount)
{
	if (nHor >= 0 && nHor <= nColCount - m_nWidth)
	{
		m_nLeftIndex = nHor;
	}
	m_nTopIndex = nVer;
	SetPieceType(m_nType);
}

void CPiece::InitPiece()
{
	m_nLeftIndex = 5;
	m_nTopIndex = 0;
	m_nType = 0;
	m_nRowCount = 1;
	m_nWidth = 3;
	m_bMoving = TRUE;
}

void CPiece::SetTopIndex(int nTopIndex)
{
	if (nTopIndex != m_nTopIndex)
	{
		m_nTopIndex = nTopIndex;
		SetPieceType(m_nType);
	}
}

void CPiece::SetPieceType(int nType)
{
	m_nType = nType;
	if (nType == 1)
	{
		m_nRowCount = 1;
		m_nWidth = 4;
	}
	else if (nType == 2)
	{
		m_nRowCount = 2;
		m_nWidth = 2;
	}
	else if (nType == 11)
	{
		m_nRowCount = 4;
		m_nWidth = 1;
	}
	else if (nType == 33 || nType == 35 || nType == 44 || nType == 46 || nType == 55 || nType == 57 || nType == 66 || nType == 77)
	{
		m_nRowCount = 3;
		m_nWidth = 2;
	}
	else
	{
		m_nRowCount = 2;
		m_nWidth = 3;
	}

	switch (m_nType)
	{
	case 1:
		// ****
		for (int i = 0; i < 4; i++)
		{
			m_ImagesPT[i].x = m_nLeftIndex + i;
			m_ImagesPT[i].y = m_nTopIndex;
		}
		break;
	case 2:
		// **
		// **
		for (int i = 0; i < 4; i++)
		{
			if (i / 2 < 1)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 2;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 3:
		// *
		// ***
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 4:
		//   *
		// ***
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 2;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 5:
		//  *
		// ***
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 6:
		// **
		//  **
		for (int i = 0; i < 4; i++)
		{
			if (i / 2 < 1)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 7:
		//  **
		// **
		for (int i = 0; i < 4; i++)
		{
			if (i / 2 < 1)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i + 1;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 2;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 11:
		// *
		// *
		// *
		// *
		for (int i = 0; i < 4; i++)
		{
			m_ImagesPT[i].x = m_nLeftIndex;
			m_ImagesPT[i].y = m_nTopIndex + i;
		}
		break;
	case 33:
		// **
		// *
		// *
		for (int i = 0; i < 4; i++)
		{
			m_ImagesPT[i].y = m_nTopIndex;
			if (i == 1)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				if (i > 1)
				{
					m_ImagesPT[i].y = m_nTopIndex + i - 1;
				}
			}
		}
		break;
	case 34:
		// ***
		//   *
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + i - 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 35:
		//	*
		//  *
		// **
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + i - 1;
			}
		}
		break;
	case 44:
		// *
		// *
		// **
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i - 1;
			}
		}
		break;
	case 45:
		// ***
		// *
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 46:
		// **
		//  *
		//  *
		for (int i = 0; i < 4; i++)
		{
			if (i > 0)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i - 1;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex;
			}
		}
		break;
	case 55:
		// *
		// **
		// *
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 56:
		// ***
		//  *
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex + i;
				m_ImagesPT[i].y = m_nTopIndex;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 57:
		//  *
		// **
		//	*
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + 1;
			}
		}
		break;
	case 66:
		//  *
		// **
		// *
		for (int i = 0; i < 4; i++)
		{
			if (i < 2)
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + i - 1;
			}
		}
		break;
	case 77:
		// *
		// **
		//  *
		for (int i = 0; i < 4; i++)
		{
			if (i < 2)
			{
				m_ImagesPT[i].x = m_nLeftIndex;
				m_ImagesPT[i].y = m_nTopIndex + i;
			}
			else
			{
				m_ImagesPT[i].x = m_nLeftIndex + 1;
				m_ImagesPT[i].y = m_nTopIndex + i - 1;
			}
		}
		break;
	}
}
