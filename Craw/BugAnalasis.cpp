#include "StdAfx.h"
#include "BugAnalasis.h"
#include "afxinet.h"
#pragma   comment(   lib,   "Wininet.lib "   )
CBugAnalasis::CBugAnalasis(void)
{
}

CBugAnalasis::~CBugAnalasis(void)
{
}

bool CBugAnalasis::AnalasisURL(CString strURL,vector<CString>&vStrURL) 
{
	 
    bool bSuccessful = false ;
	CString strPageData = "" ;

	bSuccessful = getHTMLFileContent(strURL,strPageData) ;
 

	if(bSuccessful)
	{  
		//为种子URL提取其中的URL
		
		extractUrl(strPageData,vStrURL) ;
		
		return true ;
	}
	else 
	{
		return false ;
	}
}

void CBugAnalasis::extractUrl(CString strPageData,vector<CString>&vStrURL) 
{
	int pos = 0 ;
	CString strURL =  "" ;
	CString strPrefix = "http://bbs.jlu.edu.cn/cgi-bin/" ;
	pos = strPageData.Find("a href=") ;//提取超链接

	while (pos != -1)
	{
		strPageData = strPageData.Right(strPageData.GetLength() - pos) ;

		pos = strPageData.Find('=') ;

		strPageData = strPageData.Right(strPageData.GetLength() - pos -1) ;

		pos = strPageData.Find('>') ;
		strURL = strPageData.Left(pos) ;
		//去掉引号
		if ( strURL.GetAt(0) == '"')
		{
			strURL = strURL.Right(strURL.GetLength() - 1) ;
			pos = strURL.Find('"') ;
			if(pos != -1)
			{
				strURL = strURL.Left(pos) ;
			}
		}
		strURL = strPrefix + strURL ;
        
		
		vStrURL.push_back(strURL) ;
       
        pos = strPageData.Find("a href=") ;//提取超链接
		
	}
	

}

void CBugAnalasis::SetDirectory(CString strDiretory) 
{
	m_strDirectory =  strDiretory ;
}

bool CBugAnalasis::getHTMLFileContent(CString strURL,CString &strContent) 
{
	 //获取HTML的信息
	HINTERNET Hhttpfile; 
	HINTERNET m_session;

	
	DWORD dwFileSize;
	DWORD dwbytesread;
	BOOL  bSuccessful=TRUE;

	CString strPageData = "";//保存URL页面信息

	m_session = InternetOpen(strURL,INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, 0) ;
	Hhttpfile = InternetOpenUrl(m_session, strURL, NULL, 0, 0, 0); 
	dwFileSize = 1024 ;

	if (Hhttpfile)
	{ 
		
	
		char* szBuffer=new char[dwFileSize+1];
		memset(szBuffer,0,dwFileSize+1);

		while( InternetReadFile(Hhttpfile,(LPVOID)szBuffer, dwFileSize, &dwbytesread))
		{
			if(!dwbytesread)
			{
				break;
			}
			strPageData+=(LPCSTR)szBuffer;
			memset(szBuffer,0,dwFileSize+1);
		}
		 
		
		/**********************************
		CStdioFile file ;
		file.Open("ts11.txt",CFile::modeCreate|CFile::modeWrite); 
		file.WriteString(strPageData) ;
		**************************************/
		delete[] szBuffer;

		::InternetCloseHandle(Hhttpfile); 
		
		
	}
	else 
	{  
		bSuccessful = FALSE;
		
	}  
	::InternetCloseHandle( m_session) ;

	strContent = strPageData ;
	return bSuccessful ;
}

void CBugAnalasis::ReadURLContentToFile(CString strSubURL) 
{
	//URL文件存档存档
	CString strPageData ;
	getHTMLFileContent(strSubURL,strPageData) ;

	CStdioFile file ;
	static int NO = 1;
	CString strFileName ;
	strFileName.Format("%d",NO) ;
	NO ++ ;
	strFileName = m_strDirectory + "//" +strFileName+".txt" ;

	file.Open(strFileName,CFile::modeCreate|CFile::modeWrite); 
	file.WriteString(strPageData) ;
	file.Close() ;
	
}