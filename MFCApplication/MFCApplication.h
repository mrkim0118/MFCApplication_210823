
// MFCApplication.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCApplicationApp:
// �� Ŭ������ ������ ���ؼ��� MFCApplication.cpp�� �����Ͻʽÿ�.
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationApp theApp;