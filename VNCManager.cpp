
// VNCManager.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "VNCManager.h"
#include "VNCManagerDlg.h"
#include "CsvLoader.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVNCManagerApp

BEGIN_MESSAGE_MAP(CVNCManagerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVNCManagerApp �غc

CVNCManagerApp::CVNCManagerApp()
: m_iPage(0)
, m_iRemoteWidth(1024)
, m_iRemoteHeight(768)
, m_iFontSize(9)
, m_iFontBold(0)
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
	m_wsFontFace = L"�s�ө���";
}


// �Ȧ����@�� CVNCManagerApp ����

CVNCManagerApp theApp;


// CVNCManagerApp ��l�]�w

BOOL CVNCManagerApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));

	//	��l�ƨt��
	Initialize();

	CVNCManagerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �b����m��ϥ� [�T�w] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �b����m��ϥ� [����] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}

	// �]���w�g������ܤ���A�Ǧ^ FALSE�A�ҥH�ڭ̷|�������ε{���A
	// �ӫD���ܶ}�l���ε{�����T���C
	return FALSE;
}

void CVNCManagerApp::Initialize()
{
	wchar_t path_[0xff];
	ZeroMemory(path_, sizeof(wchar_t)*0xff);
	GetPrivateProfileString( L"vnc", L"path", L"", path_, 0xff, L".\\config.ini" );
	m_wsPath = path_;

	wchar_t param_[0xff];
	ZeroMemory(param_, sizeof(wchar_t)*0xff);
	GetPrivateProfileString( L"vnc", L"parameter", L"", param_, 0xff, L".\\config.ini" );
	m_wsParameter = param_;

	
	m_iPage = GetPrivateProfileInt( L"vnc", L"page", 0, L".\\config.ini" );

	m_iRemoteWidth = GetPrivateProfileInt( L"remote", L"width", 0, L".\\config.ini" );
	m_iRemoteHeight = GetPrivateProfileInt( L"remote", L"height", 0, L".\\config.ini" );

	m_iFontSize = GetPrivateProfileInt( L"vnc", L"font", 0, L".\\config.ini" );
	GetPrivateProfileString( L"vnc", L"face", L"", param_, 0xff, L".\\config.ini" );
	m_wsFontFace = param_;

	m_iFontBold = GetPrivateProfileInt( L"vnc", L"bold", 0, L".\\config.ini" );
	

	LoadHostTable();
}

void CVNCManagerApp::LoadHostTable()
{
	CsvLoader csv_;
	if(csv_.Load( "hosts.csv", false ))
	{
		int iCnt_ = 0;
		int iNowPage_ = 0;
		while(csv_.Fetch())
		{
			if(csv_.GetValue(0).find("[")!=(-1) && csv_.GetValue(0).find("]")!=(-1) && csv_.GetValue(0).find("::")!=(-1))
			{

				string str_ = csv_.GetValue(0);

				string num_ = str_.substr(str_.find("[")+1, str_.find("::")-1);

				if(num_.length()>0)
				{
					iNowPage_ = atoi( num_.c_str() );
				}

				string desc_;
				desc_ = str_.substr(str_.find("::")+2, str_.find("]")-1);

				if(desc_.length()>0)
				{
					theApp.m_oTagNames.insert( make_pair( iNowPage_, theApp.ctow(desc_.substr(0, desc_.length()-1)) ) );
					
				}
			}
			else
			{
				m_oHostTable.insert( make_pair( iNowPage_, HOST_PAIR( csv_.GetValue(1).c_str(), csv_.GetValue(2).c_str(), csv_.GetValue(0).c_str(), iCnt_ ) ) );
			}
			
			++iCnt_;
		}
	}
}

bool CVNCManagerApp::GetHostRows(int page, std::vector<HOST_PAIR>& pairs)
{
	std::multimap< int, HOST_PAIR >::iterator it,itlow,itup;

	itlow = m_oHostTable.lower_bound (page);  // itlow points to b
	itup = m_oHostTable.upper_bound (page);   // itup points to e (not d)

	
	for ( it=itlow ; it != itup; it++ )
	{
		pairs.push_back( (*it).second );
	}

	return true;
}

void CVNCManagerApp::ctow(wchar_t *pwstr, const char *str)
{
	wchar_t* buffer = NULL;

	if(str)
	{

		size_t nu = strlen(str);

		size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),NULL,0);

		buffer=0;

		buffer = new wchar_t[n+1];
		ZeroMemory(buffer, sizeof(wchar_t)*(n+1));

		//if(n>=len) n=len-1;

		::MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),buffer,int(n));    

		CopyMemory( pwstr, buffer, sizeof(wchar_t)*(n+1) );

		pwstr[n+1] = L'\0';

		delete[] buffer;
	}

	
}

std::wstring CVNCManagerApp::ctow(std::string& str)
{
	wchar_t* buffer = NULL;

	if(str.length()>0)
	{

		size_t nu = str.length();

		size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str.c_str(),int(nu),NULL,0);

		buffer=0;

		buffer = new wchar_t[n+1];
		ZeroMemory(buffer, sizeof(wchar_t)*(n+1));

		//if(n>=len) n=len-1;

		::MultiByteToWideChar(CP_ACP,0,(const char *)str.c_str(),int(nu),buffer,int(n));    



		wstring res_(buffer);

		delete[] buffer;

		return res_;
	}
	return wstring(L"");
}