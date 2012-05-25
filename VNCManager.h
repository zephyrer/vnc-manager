
// VNCManager.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�

#include <string>
#include <vector>
#include <map>
// CVNCManagerApp:
// �аѾ\��@�����O�� VNCManager.cpp
//

template< typename T1, typename T2, typename T3, typename T4 >
struct PAIR_4
{
	explicit PAIR_4( T1 p1, T2 p2, T3 p3, T4 p4 )
		: first( p1 )
		, second( p2 )
		, third( p3 )
		, forth( p4 )
	{}

	T1 first;
	T2 second;
	T3 third;
	T4 forth;
};

typedef PAIR_4<std::string, std::string, std::string, int> HOST_PAIR;

class CVNCManagerApp : public CWinAppEx
{
public:
	CVNCManagerApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()

public:
	void Initialize();
	void LoadHostTable();
	void ctow(wchar_t *pwstr, const char *str);
	std::wstring ctow(std::string& str);
	bool GetHostRows(int page, std::vector<HOST_PAIR>& pairs);
	
public:
	std::wstring m_wsPath;
	std::wstring m_wsParameter;
	int m_iPage;
	std::map<int, std::wstring> m_oTagNames;
	int m_iRemoteWidth;
	int m_iRemoteHeight;
	int m_iFontSize;
	std::wstring m_wsFontFace;
	int m_iFontBold;

protected:
	//typedef std::pair< std::string, std::string > HOST_PAIR;
	
	
	//	key=pageNum, value=id and .......
	std::multimap< int, HOST_PAIR > m_oHostTable;
	
	
	
};

extern CVNCManagerApp theApp;