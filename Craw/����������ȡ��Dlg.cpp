// 网络爬虫提取器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络爬虫提取器.h"
#include "网络爬虫提取器Dlg.h"
#include <vector>
using namespace std ;

#include "BugAnalasis.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C网络爬虫提取器Dlg 对话框




C网络爬虫提取器Dlg::C网络爬虫提取器Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C网络爬虫提取器Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C网络爬虫提取器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C网络爬虫提取器Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &C网络爬虫提取器Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C网络爬虫提取器Dlg 消息处理程序

BOOL C网络爬虫提取器Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C网络爬虫提取器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C网络爬虫提取器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR C网络爬虫提取器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C网络爬虫提取器Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDOK)->EnableWindow(FALSE) ;//将爬行按钮设为失效
	//1读取种子文件
	//2提取种子文件中的URL
	vector<CString>vStrURL ;
    CBugAnalasis BugAnalasis ;
	if ( BugAnalasis.AnalasisURL("http://bbs.jlu.edu.cn/cgi-bin/bbsdoc?board=CCST",vStrURL) == true)
	{
	  
	   //时间为参数创建文件夹名字
   
        CTime time ;
		CString strDirectoryName ;

		time = CTime::GetCurrentTime() ;
		strDirectoryName.Format("%d-%d-%d-%d-%d-%d" ,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()) ;

	   //设置属性
        SECURITY_ATTRIBUTES attribute;
        attribute.nLength = sizeof(attribute);
        attribute.lpSecurityDescriptor = NULL;
        attribute.bInheritHandle = FALSE;
        //创建
        if(CreateDirectoryA(strDirectoryName,&attribute))
		{
			BugAnalasis.SetDirectory(strDirectoryName) ;
			for( int i = 0 ; i < vStrURL.size() ;i++ )
			{
				BugAnalasis.ReadURLContentToFile(vStrURL[i]) ;
			}
		}

		GetDlgItem(IDOK)->EnableWindow(TRUE) ;
		MessageBox("爬行完毕");
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE) ;
		MessageBox("连接错误：http://bbs.jlu.edu.cn/cgi-bin/bbsdoc?board=CCST") ;
	}
	
	
}
