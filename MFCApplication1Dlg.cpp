
// MFCApplication1Dlg.cpp : ʵ���ļ�
//
#include <string.h>
#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "ur5.h"
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MOVE, &CMFCApplication1Dlg::OnBnClickedMove)
	ON_BN_CLICKED(IDC_STOP, &CMFCApplication1Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ur5.Connect("192.168.1.102", 30003);
	SetTimer(0, 100, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::OnTimer(UINT nId)
{
	WCHAR szTemp[0x100];
	UR5_POSE ur5Pose;
	m_ur5.GetActualToolPose(&ur5Pose);
	swprintf(szTemp, L"%0.2lf", ur5Pose.x * 1000);
	SetDlgItemText(6000, szTemp);

	swprintf(szTemp, L"%0.2lf", ur5Pose.y * 1000 );
	SetDlgItemText(6001, szTemp);

	swprintf(szTemp, L"%0.2lf", ur5Pose.z * 1000); 
	SetDlgItemText(6002, szTemp);

	swprintf(szTemp, L"%0.4lf", ur5Pose.rx);
	SetDlgItemText(6003, szTemp);

	swprintf(szTemp, L"%0.4lf", ur5Pose.ry);
	SetDlgItemText(6004, szTemp);

	swprintf(szTemp, L"%0.4lf", ur5Pose.rz);
	SetDlgItemText(6005, szTemp);
}
void CMFCApplication1Dlg::OnBnClickedMove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CHAR szDouble[0x10];
	double x, y, z, rx, ry, rz;
	::GetDlgItemTextA(m_hWnd, 5000, szDouble, 0x10);
	x = atof(szDouble);
	::GetDlgItemTextA(m_hWnd, 5001, szDouble, 0x10);
	y = atof(szDouble);
	::GetDlgItemTextA(m_hWnd, 5002, szDouble, 0x10);
	z = atof(szDouble);
	::GetDlgItemTextA(m_hWnd, 5003, szDouble, 0x10);
	rx = atof(szDouble);
	::GetDlgItemTextA(m_hWnd, 5004, szDouble, 0x10);
	ry = atof(szDouble);
	::GetDlgItemTextA(m_hWnd, 5005, szDouble, 0x10);
	rz = atof(szDouble);
	Sleep(2000);
	m_ur5.Move(x, y, z, rx, ry, rz);

}	







void CMFCApplication1Dlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ur5.Stop();
}
