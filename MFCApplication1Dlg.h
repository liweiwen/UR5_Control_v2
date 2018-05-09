
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "tcp.h"
#include "ur5.h"

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
