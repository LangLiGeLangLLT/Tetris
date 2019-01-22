#include "stdafx.h"
#include "Cell.h"


CCell::CCell()
{
	m_nRowIndex = 0;
	m_nColIndex = 0;
	m_bUsed = FALSE;
	m_bFixed = FALSE;
}


CCell::~CCell()
{
}
