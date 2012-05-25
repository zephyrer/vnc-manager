#pragma once


// CHListTabDlg 對話方塊

class CHListTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CHListTabDlg)

public:
	CHListTabDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CHListTabDlg();
	virtual BOOL OnInitDialog();
	//afx_msg void OnHdnItemdblclickHostList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkHostList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedHostList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickHostList(NMHDR *pNMHDR, LRESULT *pResult);
	void Open(int page);

// 對話方塊資料
	enum { IDD = IDD_TAB_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

public:
	
	CListCtrl m_oHostList;
	int m_iPageNum;
	int m_iNowStyle;

	CFont m_smallFont;
	CFont m_bigFont;
};
