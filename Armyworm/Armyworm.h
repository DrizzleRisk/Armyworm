
// Armyworm.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
// Code By Drizzle.Risk

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CArmywormApp:
// �йش����ʵ�֣������ Armyworm.cpp
//

class CArmywormApp : public CWinApp
{
public:
	CArmywormApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CArmywormApp theApp;