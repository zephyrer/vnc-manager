
// VNCManagerDlg.h : ���Y��
//

#pragma once
#include "afxcmn.h"
#include <map>
#include "HListTabDlg.h"


// CVNCManagerDlg ��ܤ��
class CVNCManagerDlg : public CDialog
{
// �غc
public:
	CVNCManagerDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_VNCMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
