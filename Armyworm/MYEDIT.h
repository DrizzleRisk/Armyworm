#pragma once
// Code By Drizzle.Risk

// MYEDIT �Ի���

class MYEDIT : public CDialogEx
{
	DECLARE_DYNAMIC(MYEDIT)

public:
	MYEDIT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MYEDIT();

// �Ի�������
	enum { IDD = IDD_DIALOGEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
		afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	HWND hwnd;
	virtual BOOL OnInitDialog();
	RECT rect;
	CEdit m_edit;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	HWND parent;
	HWND message_hwnd;
	afx_msg void OnEnChangeEdit1();
	int num;
	long lwidth;
	long lheight;
};
