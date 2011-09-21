// ����������ȡ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����������ȡ��.h"
#include "����������ȡ��Dlg.h"
#include <vector>
using namespace std ;

#include "BugAnalasis.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C����������ȡ��Dlg �Ի���




C����������ȡ��Dlg::C����������ȡ��Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C����������ȡ��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����������ȡ��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C����������ȡ��Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &C����������ȡ��Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C����������ȡ��Dlg ��Ϣ�������

BOOL C����������ȡ��Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C����������ȡ��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C����������ȡ��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR C����������ȡ��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C����������ȡ��Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDOK)->EnableWindow(FALSE) ;//�����а�ť��ΪʧЧ
	//1��ȡ�����ļ�
	//2��ȡ�����ļ��е�URL
	vector<CString>vStrURL ;
    CBugAnalasis BugAnalasis ;
	if ( BugAnalasis.AnalasisURL("http://bbs.jlu.edu.cn/cgi-bin/bbsdoc?board=CCST",vStrURL) == true)
	{
	  
	   //ʱ��Ϊ���������ļ�������
   
        CTime time ;
		CString strDirectoryName ;

		time = CTime::GetCurrentTime() ;
		strDirectoryName.Format("%d-%d-%d-%d-%d-%d" ,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()) ;

	   //��������
        SECURITY_ATTRIBUTES attribute;
        attribute.nLength = sizeof(attribute);
        attribute.lpSecurityDescriptor = NULL;
        attribute.bInheritHandle = FALSE;
        //����
        if(CreateDirectoryA(strDirectoryName,&attribute))
		{
			BugAnalasis.SetDirectory(strDirectoryName) ;
			for( int i = 0 ; i < vStrURL.size() ;i++ )
			{
				BugAnalasis.ReadURLContentToFile(vStrURL[i]) ;
			}
		}

		GetDlgItem(IDOK)->EnableWindow(TRUE) ;
		MessageBox("�������");
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE) ;
		MessageBox("���Ӵ���http://bbs.jlu.edu.cn/cgi-bin/bbsdoc?board=CCST") ;
	}
	
	
}
