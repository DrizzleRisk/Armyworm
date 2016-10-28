
// ArmywormDlg.h : 头文件
// Code By Drizzle.Risk
#include "MYEDIT.h"
#pragma once


// CArmywormDlg 对话框
class CArmywormDlg : public CDialogEx
{
// 构造
public:
	CArmywormDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_ARMYWORM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int InitList(void);
	CListCtrl m_list;
	afx_msg void OnBnClickedButton3();
	int flag;
	afx_msg void OnBnClickedButton4();
	bool IsPlaintext;
	bool IsFindAPassEdit;
	CStatic m_tips;
	MYEDIT * me[100];
	HWND already_done[1024];
	int me_flag;
	void ClearAllMe(void);
	void CheckParam(void);
	void InitAllMe(void);
	bool CArmywormDlg::FindIfAlreadyDone(HWND hwnd);
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	bool IsHideUse;
	HWND ParamMainHwnd;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
