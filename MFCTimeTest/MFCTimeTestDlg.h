
// MFCTimeTestDlg.h: 標頭檔
//

#include <mmsystem.h>                                   // 包含 timeGetTime 函數的標頭
#include <random>

#pragma once

// 加入 mmysystem.h 中的 timeGetTime 時需加入以下連接庫
// "winmm.lib" 是 Windows Multimedia API
#pragma comment(lib, "winmm.lib ")

// CMFCTimeTestDlg 對話方塊
class CMFCTimeTestDlg : public CDialogEx
{
// 建構
public:
	CMFCTimeTestDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_editStartBtn;
	CButton m_editStopBtn;

	CString m_strCalculateTime;
	CString m_strRealTime;

	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_staticCalculateTime;
	CStatic m_staticElapseTime;
};
