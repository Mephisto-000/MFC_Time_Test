
// MFCTimeTestDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCTimeTest.h"
#include "MFCTimeTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DWORD g_dwCurrentTime;
double g_dTimeCurrentSpan;


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMFCTimeTestDlg 對話方塊



CMFCTimeTestDlg::CMFCTimeTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTIMETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTimeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_editStartBtn);
	DDX_Control(pDX, IDC_STOP, m_editStopBtn);
	DDX_Control(pDX, IDC_STATIC_CALCULATE_TIME, m_staticCalculateTime);
	DDX_Control(pDX, IDC_STATIC_ELAPSE_TIME, m_staticElapseTime);
}

BEGIN_MESSAGE_MAP(CMFCTimeTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMFCTimeTestDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CMFCTimeTestDlg::OnBnClickedStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCTimeTestDlg 訊息處理常式

BOOL CMFCTimeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCTimeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCTimeTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCTimeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTimeTestDlg::OnBnClickedStart()
{

	UINT nInterval = 1000;  // 1秒

	g_dwCurrentTime = timeGetTime();

	SetTimer(1, nInterval, NULL);
	SetTimer(2, nInterval, NULL);
}


void CMFCTimeTestDlg::OnBnClickedStop()
{
	KillTimer(1);
	KillTimer(2);
}


void CMFCTimeTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	DWORD dwRecordTime = timeGetTime();

	if (nIDEvent == 1)
	{
		// 一千萬次迴圈時間測試
		int intLoopCount = 100000000;


		// 隨機產生數字
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> dist(1, 100);

		for (int i = 0; i < intLoopCount; i++)
		{
			int iRandomA = dist(rng);
			int iRandomB = dist(rng);
			int iResult = iRandomA * iRandomB;
		}

		DWORD dwElapsedTime = dwRecordTime - g_dwCurrentTime;
		double seconds = static_cast<double>(dwElapsedTime) / 1000.0;

		m_strCalculateTime.Format(_T("%.7f"), seconds);

		m_staticCalculateTime.SetWindowText(m_strCalculateTime);
	}
	else if (nIDEvent == 2)
	{
		DWORD dwElapsedTime = dwRecordTime - g_dwCurrentTime;

		double seconds = static_cast<double>(dwElapsedTime) / 1000.0;

		m_strRealTime.Format(_T("%.7f"), seconds);

		m_staticElapseTime.SetWindowText(m_strRealTime);

	}


	CDialogEx::OnTimer(1);
	CDialogEx::OnTimer(2);
}
