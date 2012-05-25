#include "stdafx.h"
#include "CsvLoader.h"
#include <fstream>

using namespace std;


CsvLoader::CsvLoader()
: m_iCursor(-1)
{
}

CsvLoader::~CsvLoader()
{
	if(!m_oDataRows.empty())
	{
		for(size_t i=0;i<m_oDataRows.size();i++)
		{
			delete m_oDataRows[i];
		}

		m_oDataRows.clear();
	}
}

bool CsvLoader::Load(const char* path, bool isContainCol)
{	
	const int LINE_LENGTH = 128;	//	一行字串最大長度

	ifstream reader_;
	std::vector<std::string> columns_;
	std::vector<std::string> tokens_;

	int iRow_ = 0;
	
	try
	{
		reader_.open( path, ifstream::in );	

		if(!reader_)
		{
			return false;
		}
		
		string line_;
		//getline(reader_, line_);
		
		do
		{
			
			line_ = "";
			getline(reader_, line_);
			
			if(isContainCol)
			{
				if(iRow_==0)
				{
					Tokenize(line_, ",", columns_);
				}
				else
				{
					Tokenize(line_, ",", tokens_);
					string test_ = tokens_[0];
					ROW_MAP_PTR rowmap_(new ROW_MAP());
					if(tokens_.size()==columns_.size())
					{
						for(size_t i=0;i<columns_.size();i++)
						{
							rowmap_->insert( make_pair(columns_[i], tokens_[i]) );							
						}
						m_oDataRows.push_back( rowmap_ );
					}
					/*else
					{
						break;
					}*/
				}
			}
			else
			{
				Tokenize(line_, ",", tokens_);
				ROW_MAP_PTR rowmap_ = new ROW_MAP();
				if(!line_.empty())
				{
					char temp_[LINE_LENGTH];
					
					for(size_t i=0;i<tokens_.size();i++)
					{
						sprintf( temp_, "%d", i );
						rowmap_->insert( make_pair(temp_, tokens_[i]) );
						
					}
					m_oDataRows.push_back( rowmap_ );
				}
				/*else
				{
					break;
				}*/
				

			}

			++iRow_;

			
		}while(!reader_.eof());
	
		reader_.close();

		
	}
	catch(...)
	{
		if(reader_)
			reader_.close();

		return false;
	}

	m_iCursor = -1;

	return true;
}

void CsvLoader::Tokenize(std::string& input, const char* deli, std::vector<std::string>& tokens)
{
	if(!tokens.empty())
	{
		tokens.clear();
	}


	string::size_type last_pos = 0;
	string::size_type pos = 0; 
	string delimiters = deli;

	while(true)
	{
		pos = input.find_first_of(delimiters, last_pos);
		if( pos == string::npos )
		{
			tokens.push_back(input.substr(last_pos));
			break;
		}
		else
		{
			tokens.push_back(input.substr(last_pos, pos - last_pos));
			last_pos = pos + 1;
		} 
	}
}

bool CsvLoader::Fetch()
{
	if(m_iCursor>=(int)m_oDataRows.size())
	{		
		m_iCursor = -1;
	}
	else
	{		
		++m_iCursor;		
	}

	return m_iCursor<(int)m_oDataRows.size();	
}

std::string CsvLoader::GetValue( const char* col )
{
	string colstr_ = col;
	if(m_iCursor>=0&&m_iCursor<(int)m_oDataRows.size())
	{
		if(m_oDataRows[m_iCursor])
		{
			ROW_MAP::iterator it_ = m_oDataRows[m_iCursor]->find( colstr_ );
			if(it_!=m_oDataRows[m_iCursor]->end())
			{
				return it_->second;
			}
		}
	}

	return "";
}

std::string CsvLoader::GetValue( int col )
{
	
	if(m_iCursor>=0&&m_iCursor<(int)m_oDataRows.size())
	{
		if(m_oDataRows[m_iCursor])
		{
			ROW_MAP::iterator it_ = m_oDataRows[m_iCursor]->begin();
			
			
			for(int i=0;it_!=m_oDataRows[m_iCursor]->end()&&i<col;it_++,i++)
			{
				
			}

			if(it_!=m_oDataRows[m_iCursor]->end())
			{
				return it_->second;
			}
		}
	}

	return "";
}

