
// MouseJiggleDlg.h : header file
//

#pragma once


/////////////////////////////////////////////////////////////////////////////

#define WM_SHOWTASK     WM_USER + 100 //定义消息的值

// CMouseJiggleDlg dialog
class CMouseJiggleDlg : public CDialog
{
	// Construction
public:
	CMouseJiggleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSEJIGGLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int m_enjiggle;
	DWORD m_countClickEnjiggle;
	NOTIFYICONDATA m_nid;


	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEnjiggle();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	//	CString m_cstrflushtime;
	//	DWORD m_dwflushtime;
	DWORD m_dwflashtime;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedMinimize();

protected:
	afx_msg LRESULT OnShowtask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnEnChangeFlushtime();
};
