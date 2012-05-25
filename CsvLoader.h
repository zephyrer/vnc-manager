#ifndef __CSVLOADER_H__
#define __CSVLOADER_H__
#pragma once

#include <map>
#include <vector>
#include <string>


class CsvLoader 
{
public:
	CsvLoader();
	virtual ~CsvLoader();
	bool Load(const char* path, bool isContainCol);
	
	bool Fetch();
	std::string GetValue( const char* col );
	std::string GetValue( int col );
protected:
	void Tokenize(std::string& input, const char* deli, std::vector<std::string>& tokens);
private:
	typedef std::map<std::string, std::string> ROW_MAP;
	typedef ROW_MAP* ROW_MAP_PTR;
	 
	std::vector<ROW_MAP_PTR> m_oDataRows;
	int m_iCursor;
	
};



#endif	//	__CSVLOADER_H__