
// MiniProjectGUIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MiniProjectGUI.h"
#include "MiniProjectGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMiniProjectGUIDlg 대화 상자



CMiniProjectGUIDlg::CMiniProjectGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINIPROJECTGUI_DIALOG, pParent)
	, m_strTxtThreatPosition_X(_T(""))
	, m_strTxtThreatPosition_Y(_T(""))
	, m_strTxtThreatTargetPosition_X(_T(""))
	, m_strTxtThreatTargetPosition_Y(_T(""))
	, m_strTxtMissilePosition_X(_T(""))
	, m_strTxtMissilePosition_Y(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniProjectGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THREAT_X, m_strTxtThreatPosition_X);
	DDX_Text(pDX, IDC_EDIT_THREAT_Y, m_strTxtThreatPosition_Y);
	DDX_Text(pDX, IDC_EDIT_THREAT_TARGET_X, m_strTxtThreatTargetPosition_X);
	DDX_Text(pDX, IDC_EDIT_THREAT_TARGET_Y, m_strTxtThreatTargetPosition_Y);
	DDX_Text(pDX, IDC_EDIT_MISSILE_X, m_strTxtMissilePosition_X);
	DDX_Text(pDX, IDC_EDIT_MISSILE_Y, m_strTxtMissilePosition_Y);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_ctrlDisplay);
	DDX_Text(pDX, IDC_EDIT_SERVER_ADDR, m_str_server_address);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_str_server_port);
}

BEGIN_MESSAGE_MAP(CMiniProjectGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CMiniProjectGUIDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_SET_POSITIONS, &CMiniProjectGUIDlg::OnBnClickedBtnSetPositions)
	ON_BN_CLICKED(IDC_BTN_RESET_POSITIONS, &CMiniProjectGUIDlg::OnBnClickedBtnResetPositions)
	ON_BN_CLICKED(IDC_BTN_START, &CMiniProjectGUIDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMiniProjectGUIDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_FIRE_MISSILE, &CMiniProjectGUIDlg::OnBnClickedBtnFireMissile)
	ON_BN_CLICKED(IDC_BUTTON_COMM_SET, &CMiniProjectGUIDlg::OnBnClickedButtonCommSet)
	//ON_LBN_SELCHANGE(IDC_LIST_EVENT, &CMiniProjectGUIDlg::OnLbnSelchangeListEvent)
END_MESSAGE_MAP()


// CMiniProjectGUIDlg 메시지 처리기

BOOL CMiniProjectGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	displayController.setDisplayObject(&this->m_ctrlDisplay);

	m_strTxtThreatTargetPosition_X = "0";
	m_strTxtThreatTargetPosition_Y = "0";
	m_strTxtThreatPosition_X = "0";
	m_strTxtThreatPosition_Y = "0";
	m_strTxtMissilePosition_X = "0";
	m_strTxtMissilePosition_Y = "0";
	m_str_server_address = "127.0.0.1";
	m_str_server_port = "5000";

	UpdateData(FALSE);

	testThread = nullptr;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMiniProjectGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMiniProjectGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		displayController.reset();

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMiniProjectGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMiniProjectGUIDlg::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SendMessage(WM_CLOSE, 0, 0);
}


void CMiniProjectGUIDlg::OnBnClickedBtnSetPositions()
{
	////////////////////////////////////////////////////
	// 추가 코드 작성
	////////////////////////////////////////////////////
}


void CMiniProjectGUIDlg::OnBnClickedBtnResetPositions()
{
	m_strTxtThreatTargetPosition_X = "0";
	m_strTxtThreatTargetPosition_Y = "0";
	m_strTxtThreatPosition_X = "0";
	m_strTxtThreatPosition_Y = "0";
	m_strTxtMissilePosition_X = "0";
	m_strTxtMissilePosition_Y = "0";

	UpdateData(FALSE);
}


void CMiniProjectGUIDlg::OnBnClickedBtnStart()
{
	// 화면 지우기
	displayController.reset();

	////////////////////////////////////////////////////
	// 추가 코드 작성
	////////////////////////////////////////////////////
}



void CMiniProjectGUIDlg::OnBnClickedBtnStop()
{
	////////////////////////////////////////////////////
	// 추가 코드 작성
	////////////////////////////////////////////////////
}


void CMiniProjectGUIDlg::OnBnClickedBtnFireMissile()
{
	////////////////////////////////////////////////////
	// 추가 코드 작성
	////////////////////////////////////////////////////
}


void CMiniProjectGUIDlg::OnLbnSelchangeListEvent(CString log_message)
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_EVENT);

	CTime currentTime;
	currentTime = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(L"(%02d:%02d:%02d) %s", currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond(),
		log_message);

	pList->AddString(strTime);
	pList->SetCurSel(pList->GetCount() - 1);
}


void CMiniProjectGUIDlg::OnBnClickedButtonCommSet()
{
	// 통신설정 버튼
	UpdateData(TRUE);

	string addr = CT2CA(m_str_server_address.operator LPCWSTR()); // cstring to string
	comm.setTcpConnectionInfo(addr, _ttoi(m_str_server_port));
	if (comm.connect()) {
		OnLbnSelchangeListEvent(L"TCP 연결: " + m_str_server_address +
			L", " + m_str_server_port);
	}
}

