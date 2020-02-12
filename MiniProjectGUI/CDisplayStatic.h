#pragma once
#include <afxwin.h>
class CDisplayStatic :
	public CStatic
{
public:
	CDisplayStatic();
	~CDisplayStatic();

	void OnPaint();

protected:
	DECLARE_MESSAGE_MAP()
};

