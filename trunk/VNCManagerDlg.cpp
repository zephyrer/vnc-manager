
// VNCManagerDlg.cpp : ��@��
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

// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
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


// CVNCManagerDlg ��ܤ��




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


// CVNCManagerDlg �T���B�z�`��

BOOL CVNCManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	// �إ�tab
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

	//	�w�]�}��
	CRect rTab, rItem;

    m_oHListTab.GetItemRect(0, &rItem);

    m_oHListTab.GetClientRect(&rTab);

    int x = rItem.left;
    int y = rItem.bottom + 1;
    int cx = rTab.right - rItem.left - 3;
    int cy = rTab.bottom - y -2;
	m_oListContent.Open( 1 );
	m_oListContent.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CVNCManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CVNCManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CVNCManagerDlg::OnTcnSelchangeHlistTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �b���[�J����i���B�z�`���{���X
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
