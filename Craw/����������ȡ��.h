// ����������ȡ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C����������ȡ��App:
// �йش����ʵ�֣������ ����������ȡ��.cpp
//

class C����������ȡ��App : public CWinApp
{
public:
	C����������ȡ��App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C����������ȡ��App theApp;