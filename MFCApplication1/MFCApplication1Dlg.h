

#pragma once


class CMFCApplication1Dlg : public CDialogEx
{

public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	



protected:
	HICON m_hIcon;

	
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_combo1;
	CStatic m_time1;
	CStatic m_time2;
	CStatic m_time3;
	CEdit m_ncount;
	afx_msg void OnBnClickedButton3();
	CListBox m_listbox1;
	afx_msg void OnBnClickedButton1();
	CListBox m_listbox2;
	afx_msg void OnBnClickedButton2();
	CListBox m_listbox3;
	CButton m_ctlCheck;
	afx_msg void OnBnClickedButton4();
	CListCtrl m_cListCtrl;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnStnClickedTime4();
	afx_msg void OnBnClickedButton6();
};
