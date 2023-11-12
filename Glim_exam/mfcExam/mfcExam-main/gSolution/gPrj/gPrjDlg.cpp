
// gPrjDlg.cpp : ���� ����
//

#include<iostream>
#include "stdafx.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
int static cnt;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CgPrjDlg ��ȭ ����



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_Test, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDOK, &CgPrjDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_Process, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_make_pattern, &CgPrjDlg::OnBnClickedBtnmakepattern)
	ON_BN_CLICKED(IDC_BUTTON_CIRCLE, &CgPrjDlg::OnBnClickedButtonCircle)
END_MESSAGE_MAP()


// CgPrjDlg �޽��� ó����

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);//���׶��

	m_pDlgResult = new CDlgImage;
	m_pDlgResult->Create(IDD_DLGIMAGE, this);
	m_pDlgResult->ShowWindow(SW_SHOW);
	m_pDlgResult->MoveWindow(640, 0, 640, 480);//���׶��
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CgPrjDlg::OnBnClickedBtnDlg()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pDlgImage)  delete m_pDlgImage;
	if(m_pDlgResult) delete m_pDlgResult;
}

#include <iostream>
void CgPrjDlg::callFunc(int n)
{
//	int nData = n;
	std::cout << n << std::endl;
}

void CgPrjDlg::OnBnClickedBtnTest()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);
	for (int k = 0; k < 500; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%255;
		
	}
	int nIndex = 0;
	m_pDlgResult->m_nDataCount = 0;
	
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] >100) {			
				if (m_pDlgResult->m_nDataCount < 100) {
					cout << nIndex << ":" << i << ":" << j << endl;
				m_pDlgResult->m_ptData[nIndex].x = i;
				m_pDlgResult->m_ptData[nIndex].y = j;
				m_pDlgResult->m_nDataCount = ++nIndex;}
				
			}
				
	     }
	}
			
	
	m_pDlgImage->Invalidate();
	m_pDlgResult->Invalidate();
}


void CgPrjDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}

#include"CProcess.h";
#include<chrono>
void CgPrjDlg::OnBnClickedBtnProcess()
{
	
	CProcess process;

	auto start = std::chrono::system_clock::now();
	int nRent = process.getStarInfo(&m_pDlgImage->m_image); 
	auto end= std::chrono::system_clock::now();
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << nRent <<"\t" <<millisec.count() <<"ms" << endl;
}


void CgPrjDlg::OnBnClickedBtnmakepattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);
	
	int nTh = 10;

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	CRect rect(100, 100, 200, 400);
	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			fm[j * nPitch + i] = 100;
		}
	}
	


	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] > nTh)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;
	cout << dCenterX << "\t" << dCenterY << endl;

	m_pDlgImage->Invalidate();
}








void CgPrjDlg::OnBnClickedButtonCircle()
{
	CString circleSize_str;
	GetDlgItemText(IDC_XPOINT, circleSize_str);
	

	double circleSize = _wtof(circleSize_str);
	

	cnt++;
	CClientDC dc(this);
	int startX = (rand() % 300) + 100;// to locate the circle 
	int startY = (rand() % 300) + 100;
	int endX = circleSize + startX;
	int endY = circleSize + startY;
	dc.Ellipse(startX, startY, endX, endY);
	double CenterX = ((double)(endX - startX) / 2)+startX;
	double CenterY = ((double)(endY - startY) / 2)+startY;
	cout << cnt <<"'s Circle" << " center point : " << CenterX << ", " << CenterY << endl;


}






