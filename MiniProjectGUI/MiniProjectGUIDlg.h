
// MiniProjectGUIDlg.h: 헤더 파일
//

#pragma once
#include "CDisplayStatic.h"
#include "DisplayController.h"
#include "CommunicationManager.h"

#include <thread>
#include <functional>
#include <chrono>

using std::thread;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

// CMiniProjectGUIDlg 대화 상자
class CMiniProjectGUIDlg : public CDialogEx
{
// 생성입니다.
public:
	CMiniProjectGUIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINIPROJECTGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	DisplayController displayController;

	thread* testThread;

	thread* atsThread;
	thread* mssThread;

	//void testFunc();

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnExit();
	CString m_strTxtThreatPosition_X;
	CString m_strTxtThreatPosition_Y;
	CString m_strTxtThreatTargetPosition_X;
	CString m_strTxtThreatTargetPosition_Y;
	CString m_strTxtMissilePosition_X;
	CString m_strTxtMissilePosition_Y;

	void changeType();
	void stopAndReset();
	void positionInit();

	void setPosition();

	void atsDraw();
	void mssDraw();

	static CMiniProjectGUIDlg* getInstance();

	afx_msg void OnBnClickedBtnSetPositions();
	afx_msg void OnBnClickedBtnResetPositions();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnFireMissile();
	CDisplayStatic m_ctrlDisplay;
	afx_msg void OnBnClickedBtnTest();

	afx_msg void OnEnChangeEditThreatTargetY();
	afx_msg void OnEnChangeEditThreatX();
	afx_msg void OnLbnSelchangeListEvent(CString log_message);
	afx_msg void OnStnClickedStaticDisplay();
	
	afx_msg void OnBnClickedButtonCommSet();
	afx_msg void OnEnChangeEditServerAddr();
	afx_msg void OnEnChangeEditServerPort();

	//@신재권 추가
	afx_msg void Alert(CString str);

	CStatic control_status;
	CString m_str_server_address;
	CString m_str_server_port;

private:
	float ThreatPosition_X;
	float ThreatPosition_Y;
	float ThreatTargetPosition_X;
	float ThreatTargetPosition_Y;
	float MissilePosition_X;
	float MissilePosition_Y;

	//운용 상태 확인.. 
	int checkStatus = 0;

	//float ATS_theta, ATS_x, ATS_y;
	double estimated_ATS_x, estimated_ATS_y;

	static CMiniProjectGUIDlg* projectGUIDlg;
public:
	afx_msg void OnLbnSelchangeListEvent();
};
