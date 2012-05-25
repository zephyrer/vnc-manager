// HListTabDlg.cpp : ��@��
//

#include "stdafx.h"
#include "VNCManager.h"
#include "HListTabDlg.h"
#include "CsvLoader.h"

using namespace std;
// CHListTabDlg ��ܤ��

IMPLEMENT_DYNAMIC(CHListTabDlg, CDialog)

CHListTabDlg::CHListTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHListTabDlg::IDD, pParent)
	, m_iPageNum(0)
	, m_iNowStyle(0)
{

}

CHListTabDlg::~CHListTabDlg()
{
}

void CHListTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_HOST_LIST, m_oHostList);
}


BEGIN_MESSAGE_MAP(CHListTabDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_HOST_LIST, &CHListTabDlg::OnLvnItemchangedHostList)
	//ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CHListTabDlg::OnHdnItemdblclickHostList)
	ON_NOTIFY(NM_DBLCLK, IDC_HOST_LIST, &CHListTabDlg::OnNMDblclkHostList)
	ON_NOTIFY(NM_RCLICK, IDC_HOST_LIST, &CHListTabDlg::OnNMRClickHostList)
END_MESSAGE_MAP()


// CHListTabDlg �T���B�z�`��
BOOL CHListTabDlg::OnInitDialog()
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
	

	// TODO: �b���[�J�B�~����l�]�w
	DWORD dwStyle = m_oHostList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_AUTOSIZECOLUMNS;
	//dwStyle |= LVS_EX_CHECKBOXES;
	m_oHostList.SetExtendedStyle(dwStyle);

	m_oHostList.InsertColumn( 0, _T("No"), LVCFMT_CENTER, 30 );
	m_oHostList.InsertColumn( 1, _T("NAME"), LVCFMT_CENTER, 150 );
	m_oHostList.InsertColumn( 2, _T("HOST"), LVCFMT_CENTER, 150 );
	//Open();

	int iBold_ = theApp.m_iFontBold * 100;
	
	//m_smallFont.CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, 1, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("�L�n������"));
	m_bigFont.CreateFont(theApp.m_iFontSize, 0, 0, 0, /*FW_HEAVY:FW_NORMAL*/ iBold_, 0, 0, 0, 1, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, theApp.m_wsFontFace.c_str());
	CFont* f_ = m_oHostList.GetFont();
	m_smallFont.Attach(f_->m_hObject);
	
	m_oHostList.SetFont( &m_bigFont );

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}


void CHListTabDlg::Open(int page)
{
	m_iPageNum = page;

	m_oHostList.DeleteAllItems();	

	std::vector<HOST_PAIR> list_;
	theApp.GetHostRows( m_iPageNum, list_ );

	
	if(!list_.empty())
	{
		wchar_t awcStr_[255];
		ZeroMemory(awcStr_, sizeof(wchar_t)*255);
		int nRow = 0;
		int iCnt_ = 0;
		for(size_t i=0;i<list_.size();i++)
		{
			
			ZeroMemory(awcStr_, sizeof(wchar_t)*255);

			wsprintf(awcStr_, L"%d", iCnt_);

			nRow = m_oHostList.InsertItem(iCnt_, awcStr_);

			theApp.ctow( awcStr_, list_[i].third.c_str() );
			

			m_oHostList.SetItemText( nRow, 1, awcStr_);

			theApp.ctow( awcStr_, list_[i].first.c_str() );

			m_oHostList.SetItemText( nRow, 2, awcStr_);
			
			m_oHostList.SetItemData( nRow, (DWORD_PTR)list_[i].forth );
			
			

			++iCnt_;
		}
	}
}

void CHListTabDlg::OnLvnItemchangedHostList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �b���[�J����i���B�z�`���{���X
	*pResult = 0;
}

//void CHListTabDlg::OnHdnItemdblclickHostList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: �b���[�J����i���B�z�`���{���X
//	
//
//	*pResult = 0;
//}

void CHListTabDlg::OnNMDblclkHostList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �b���[�J����i���B�z�`���{���X
	
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pResult;
	
	UINT i, uSelectedCount = m_oHostList.GetSelectedCount();
	int  nItem = -1;

	// Update all of the selected items.
	if (uSelectedCount > 0)
	{
		for (i=0;i < uSelectedCount;i++)
		{
			nItem = m_oHostList.GetNextItem(nItem, LVNI_SELECTED);
			ASSERT(nItem != -1);
			m_oHostList.Update(nItem); 

			int id_ = (int)m_oHostList.GetItemData(nItem);

			std::vector<HOST_PAIR> list_;
			theApp.GetHostRows( m_iPageNum, list_ );

			HOST_PAIR temp_("", "", "", 0);
			if(!list_.empty())
			{
				for(size_t i=0;i<list_.size();i++)
				{
					if(list_[i].forth==id_)
					{
						temp_ = list_[i];
						break;
					}
				}

				

				

				//	�P�_�O�_��IP
				if(temp_.first.find("==")!=(-1))
				{
					continue;
				}

				wchar_t paramRes_[0xff];
				ZeroMemory(paramRes_, sizeof(wchar_t)*0xff);
				wsprintf( paramRes_, theApp.m_wsParameter.c_str(), theApp.ctow(temp_.first).c_str(), theApp.ctow(temp_.second).c_str() );
				wstring str_(paramRes_);

				::ShellExecute(NULL, L"", theApp.m_wsPath.c_str(), str_.c_str(), L".\\", SW_SHOWNORMAL );

				
			}
		}
	}

	
	

	*pResult = 0;
}

void CHListTabDlg::OnNMRClickHostList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �b���[�J����i���B�z�`���{���X
	CMenu menu;
	int pMenuID = 0;
	DWORD SelectionMade;
	VERIFY(menu.LoadMenu(IDR_MENU1));

	CMenu* pPopup = menu.GetSubMenu(pMenuID);
	ASSERT(pPopup != NULL);

	POINT pp;
	GetCursorPos(&pp);
	SelectionMade = pPopup->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
		pp.x,pp.y,AfxGetMainWnd());

	pPopup->DestroyMenu();

	switch(SelectionMade)
	{
	case OPEN_VNC:
		{
			UINT i, uSelectedCount = m_oHostList.GetSelectedCount();
			int  nItem = -1;

			// Update all of the selected items.
			if (uSelectedCount > 0)
			{
				for (i=0;i < uSelectedCount;i++)
				{
					nItem = m_oHostList.GetNextItem(nItem, LVNI_SELECTED);
					ASSERT(nItem != -1);
					m_oHostList.Update(nItem); 

					int id_ = (int)m_oHostList.GetItemData(nItem);

					std::vector<HOST_PAIR> list_;
					theApp.GetHostRows( m_iPageNum, list_ );

					HOST_PAIR temp_("", "", "", 0);
					if(!list_.empty())
					{
						for(size_t i=0;i<list_.size();i++)
						{
							if(list_[i].forth==id_)
							{
								temp_ = list_[i];
								break;
							}
						}





						//	�P�_�O�_��IP
						if(temp_.first.find("==")!=(-1))
						{
							continue;
						}

						wchar_t paramRes_[0xff];
						ZeroMemory(paramRes_, sizeof(wchar_t)*0xff);
						wsprintf( paramRes_, theApp.m_wsParameter.c_str(), theApp.ctow(temp_.first).c_str(), theApp.ctow(temp_.second).c_str() );
						wstring str_(paramRes_);

						::ShellExecute(NULL, L"", theApp.m_wsPath.c_str(), str_.c_str(), L".\\", SW_SHOWNORMAL );


					}

					
				}
			}
			break;
		}
	case ID__PINGIT:
		{
			UINT i, uSelectedCount = m_oHostList.GetSelectedCount();
			int  nItem = -1;

			// Update all of the selected items.
			if (uSelectedCount > 0)
			{
				for (i=0;i < uSelectedCount;i++)
				{
					nItem = m_oHostList.GetNextItem(nItem, LVNI_SELECTED);
					ASSERT(nItem != -1);
					m_oHostList.Update(nItem); 

					int id_ = (int)m_oHostList.GetItemData(nItem);

					std::vector<HOST_PAIR> list_;
					theApp.GetHostRows( m_iPageNum, list_ );

					HOST_PAIR temp_("", "", "", 0);
					if(!list_.empty())
					{
						for(size_t i=0;i<list_.size();i++)
						{
							if(list_[i].forth==id_)
							{
								temp_ = list_[i];
								break;
							}
						}





						//	�P�_�O�_��IP
						if(temp_.first.find("==")!=(-1))
						{
							continue;
						}

						wchar_t paramRes_[0xff];
						ZeroMemory(paramRes_, sizeof(wchar_t)*0xff);
						wsprintf( paramRes_, theApp.m_wsParameter.c_str(), theApp.ctow(temp_.first).c_str(), theApp.ctow(temp_.second).c_str() );
						wstring str_(paramRes_);

						char cmd_[0xff];
						ZeroMemory(cmd_, sizeof(char)*0xff);
						sprintf( cmd_, "start ping %s -t", temp_.first.c_str() );
						::system(cmd_);


					}

					
				}
			}
			break;
		}
	case OPEN_REMOTE:
		{
			UINT i, uSelectedCount = m_oHostList.GetSelectedCount();
			int  nItem = -1;

			// Update all of the selected items.
			if (uSelectedCount > 0)
			{
				for (i=0;i < uSelectedCount;i++)
				{
					nItem = m_oHostList.GetNextItem(nItem, LVNI_SELECTED);
					ASSERT(nItem != -1);
					m_oHostList.Update(nItem); 

					int id_ = (int)m_oHostList.GetItemData(nItem);

					std::vector<HOST_PAIR> list_;
					theApp.GetHostRows( m_iPageNum, list_ );

					HOST_PAIR temp_("", "", "", 0);
					if(!list_.empty())
					{
						for(size_t i=0;i<list_.size();i++)
						{
							if(list_[i].forth==id_)
							{
								temp_ = list_[i];
								break;
							}
						}





						//	�P�_�O�_��IP
						if(temp_.first.find("==")!=(-1))
						{
							continue;
						}

						wchar_t paramRes_[0xff];
						ZeroMemory(paramRes_, sizeof(wchar_t)*0xff);
						wsprintf( paramRes_, L"/v:%s /admin /w:%d /h:%d", theApp.ctow(temp_.first).c_str(), theApp.m_iRemoteWidth, theApp.m_iRemoteHeight );
						wstring str_(paramRes_);

						::ShellExecute(NULL, L"", L"mstsc", str_.c_str(), L".\\", SW_SHOWNORMAL );


					}

					
				}
			}
			break;
		}
	case ID_CHANGE_STYLE:
		{
			m_iNowStyle = !m_iNowStyle;

			//DWORD dwStyle = m_oHostList.GetStyle();

			
			
			

			//DWORD add_ = 0;
			//DWORD rmv_ = 0;
			if(!m_iNowStyle)
			{
				//DWORD add_ = LVS_REPORT;
				//DWORD rmv_ = LVS_SMALLICON;
				
				//font_.CreateFont(9, 0, 0, 0, 100, 0, 0, 0, 1, 0, 0, 0, 0, _T("�L�n������"));
				m_oHostList.SetFont( &m_bigFont );
			}
			else
			{
				//DWORD add_ = LVS_SMALLICON;
				//DWORD rmv_ = LVS_REPORT;

				
				
				m_oHostList.SetFont( &m_smallFont );
			}

			
			//m_oHostList.ModifyStyle(rmv_, add_);
			m_oHostList.Invalidate();


			break;
		}
		

	}

	*pResult = 0;
}