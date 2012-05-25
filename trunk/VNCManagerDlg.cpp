
// VNCManagerDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "VNCManager.h"
#include "VNCManagerDlg.h"
#include "CsvLoader.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVNCManagerDlg 對話方塊




CVNCManagerDlg::CVNCManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVNCManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVNCManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_HLIST_TAB, m_oHListTab);
}

BEGIN_MESSAGE_MAP(CVNCManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	
	ON_NOTIFY(TCN_SELCHANGE, IDC_HLIST_TAB, &CVNCManagerDlg::OnTcnSelchangeHlistTab)
END_MESSAGE_MAP()


// CVNCManagerDlg 訊息處理常式

BOOL CVNCManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	// 建立tab
	wchar_t str_[0xff];
	ZeroMemory(str_, sizeof(wchar_t)*0xff);
	for(int i=0;i<theApp.m_iPage;i++)
	{
		std::map<int, std::wstring>::iterator it_ = theApp.m_oTagNames.find(i+1);
		if(it_!=theApp.m_oTagNames.end())
		{
			
			m_oHListTab.InsertItem(i, it_->second.c_str());
		}
	}

	m_oListContent.Create(IDD_TAB_DLG, &m_oHListTab);

	//	預設開啟
	CRect rTab, rItem;

    m_oHListTab.GetItemRect(0, &rItem);

    m_oHListTab.GetClientRect(&rTab);

    int x = rItem.left;
    int y = rItem.bottom + 1;
    int cx = rTab.right - rItem.left - 3;
    int cy = rTab.bottom - y -2;
	m_oListContent.Open( 1 );
	m_oListContent.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}





void CVNCManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CVNCManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CVNCManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CVNCManagerDlg::OnTcnSelchangeHlistTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CRect rTab, rItem, r0Item;

	m_oHListTab.GetItemRect(0, &r0Item);

	int nsel_ = m_oHListTab.GetCurSel();
    m_oHListTab.GetItemRect(nsel_, &rItem);

    m_oHListTab.GetClientRect(&rTab);

    int x = r0Item.left;
    int y = rItem.bottom + 1;
    int cx = rTab.right - r0Item.left - 3;
    int cy = rTab.bottom - y -2;
    int tab = m_oHListTab.GetCurSel();

    //m_oListContent.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	
	m_oListContent.Open( tab+1 );
	m_oListContent.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);

    


	*pResult = 0;
}
