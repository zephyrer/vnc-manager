
// VNCManagerDlg.h : 標頭檔
//

#pragma once
#include "afxcmn.h"
#include <map>
#include "HListTabDlg.h"


// CVNCManagerDlg 對話方塊
class CVNCManagerDlg : public CDialog
{
// 建構
public:
	CVNCManagerDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_VNCMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	

private:
	
public:
	
private:
	

public:
	
	CTabCtrl m_oHListTab;
	CHListTabDlg m_oListContent;
	afx_msg void OnTcnSelchangeHlistTab(NMHDR *pNMHDR, LRESULT *pResult);
};
