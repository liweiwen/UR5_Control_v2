
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "tcp.h"
#include "ur5.h"

// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nId);
	DECLARE_MESSAGE_MAP()
	CUR5 m_ur5;
public:
	afx_msg void OnBnClickedMove();
	afx_msg void OnBnClickedStop();
};
