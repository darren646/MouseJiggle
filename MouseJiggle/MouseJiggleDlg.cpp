
// MouseJiggleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseJiggle.h"
#include "MouseJiggleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMouseJiggleDlg dialog



CMouseJiggleDlg::CMouseJiggleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MOUSEJIGGLE_DIALOG, pParent)
	, m_enjiggle(0)
	, m_dwflashtime(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseJiggleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ENJIGGLE, m_enjiggle);
	//  DDX_Text(pDX, IDC_FLUSHTIME, m_cstrflushtime);

	DDX_Text(pDX, IDC_FLUSHTIME, m_dwflashtime);
}

BEGIN_MESSAGE_MAP(CMouseJiggleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENJIGGLE, &CMouseJiggleDlg::OnBnClickedEnjiggle)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMouseJiggleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_MINIMIZE, &CMouseJiggleDlg::OnBnClickedMinimize)

	ON_MESSAGE(WM_SHOWTASK, &CMouseJiggleDlg::OnShowtask)
	ON_EN_CHANGE(IDC_FLUSHTIME, &CMouseJiggleDlg::OnEnChangeFlushtime)
END_MESSAGE_MAP()


// CMouseJiggleDlg message handlers

BOOL CMouseJiggleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_enjiggle = 0;
	((CButton*)GetDlgItem(IDC_ENJIGGLE))->SetCheck(TRUE);
	UpdateData(TRUE);
	m_countClickEnjiggle = 0;

	m_dwflashtime = 9 * 1000;
	UpdateData(false);//移动鼠标间隔毫秒数设置默认值为9秒，并显示在text上

	SetTimer(1, m_dwflashtime, NULL);
	SetTimer(2, 500, NULL);
	MessageBox(_T("Start mouse jiggle!"));


	// 在托盘区添加图标
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	_tcscpy_s(m_nid.szTip, _T("服务器程序"));            // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数	
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMouseJiggleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMouseJiggleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseJiggleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseJiggleDlg::OnBnClickedEnjiggle()
{
	// TODO: Add your control notification handler code here
	m_countClickEnjiggle++;
	CButton *pCheckbox = (CButton*)GetDlgItem(IDC_ENJIGGLE);
	int checkstatus=pCheckbox->GetCheck();
	if (pCheckbox->GetCheck())
	{

		if (m_countClickEnjiggle > 1)
		{
			UpdateData(TRUE); //get m_dwflashtime;
			SetTimer(1, m_dwflashtime, 0);

			MessageBox(_T("Start mouse jiggle!"));
		}


	}

	else
	{
		KillTimer(1);

		MessageBox(_T("Stop mouse jiggle!"));
	}

}



void CMouseJiggleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:   //定时器1处理函数，定时发送数据进行更新
	{
		POINT point;
		::GetCursorPos(&point);

		mouse_event(MOUSEEVENTF_MOVE, 1, 1, 0, 0);
		Sleep(100);
		mouse_event(MOUSEEVENTF_MOVE, -1, -1, 0, 0);

		::SetCursorPos(point.x, point.y);  //位置还原
		break;
	}

	case 2:   //定时器2位为状态栏时间信息,定时自动刷新移动鼠标毫秒数
	{
		UpdateData(TRUE);
		break;
	}

	}


	CDialog::OnTimer(nIDEvent);
}


void CMouseJiggleDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//CMouseJiggleDlg::OnCancel();
	//CDialog::OnCancel();
	PostMessage(WM_QUIT, 0, 0);

}


void CMouseJiggleDlg::OnBnClickedMinimize()
{
	// TODO: Add your control notification handler code here
	//SendMessage(WM_MINIMIZE)
	//CDialog::OnSize(SIZE_MINIMIZED, 0, 0);
	//ShowWindow(SW_HIDE);


	ShowWindow(SW_HIDE);
}



afx_msg LRESULT CMouseJiggleDlg::OnShowtask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)

		return 1;

	switch (lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单

	{

		CMenu menu;
		LPPOINT lpoint = new tagPOINT;
		menu.CreatePopupMenu();                    // 声明一个弹出式菜单
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("EXIT"));



		::GetCursorPos(lpoint);                    // 得到鼠标位置
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);

		HMENU hmenu = menu.Detach();

		menu.DestroyMenu();

		delete lpoint;

	}

	break;

	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理

	{

		this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口

	}

	break;

	}

	return 0;
}


void CMouseJiggleDlg::OnEnChangeFlushtime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
