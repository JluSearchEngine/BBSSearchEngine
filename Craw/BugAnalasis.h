#pragma once
#include <vector>
using namespace std ;


class CBugAnalasis
{
public:
	CBugAnalasis(void);
	bool AnalasisURL(CString strURL,vector<CString>&vStrURL) ;
	void SetDirectory(CString strDiretory) ;
	void ReadURLContentToFile(CString strSubURL) ;
private:
	void extractUrl(CString strPageData,vector<CString>&vStrURL) ;
	bool getHTMLFileContent(CString strURL,CString &strContent) ;
private:
	CString m_strDirectory ;
public:
	~CBugAnalasis(void);
};
