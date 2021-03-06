

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define MAXX 1000000
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


int random(int minN, int maxN) 
{
	return minN + rand() % (maxN + 1 - minN);
}
int *Arr, N;
int nItem;
void RandomMang(int n) 
{
	Arr = new int[n];
	srand((int)time(0));
	int r;
	for (int i = 0; i < n; i++) {
		r = random(1, 1000);
		Arr[i] = r;
		
	}
}


void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// Selection sort Khong song song
void selectionSort(int *b,int arr[], int n)
{
	int i, j, min_idx;
	
	
	for (int i = 0; i < n; i++)
	{
		b[i] = arr[i];
	}
	
	for (i = 0; i < n - 1; i++)
	{ 
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (b[j] < b[min_idx])
				min_idx = j;

		swap(&b[min_idx], &b[i]);
	}
	
}

// Selection sort song song
void SelectionSortParallel(int *b,int a[], int n, int _thread)
{

	for (int i = 0; i < n; i++)
	{
		b[i] = a[i];
	}
	
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;


#pragma omp parallel num_threads(_thread)
		{
#pragma omp for
			for (int j = i + 1; j < n; j++)
			{
				if (b[min] > b[j])
					min = j;
			}
		}
		swap(&b[min], &b[i]);
	}
}




CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_TIME2, m_time2);
	DDX_Control(pDX, IDC_TIME3, m_time3);
	DDX_Control(pDX, IDC_EDIT1, m_ncount);
	DDX_Control(pDX, IDC_LIST2, m_listbox1);
	DDX_Control(pDX, IDC_LIST3, m_listbox2);
	DDX_Control(pDX, IDC_LIST1, m_listbox3);
	DDX_Control(pDX, IDC_CHECK1, m_ctlCheck);
	DDX_Control(pDX, IDC_LIST5, m_cListCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
	ON_STN_CLICKED(IDC_TIME4, &CMFCApplication1Dlg::OnStnClickedTime4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()



BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	
	CString str;
	for (int i = 2; i <10;)
	{
		int n;
		str.Format(_T("%d"), i);
		n = m_combo1.AddString(str);
		m_combo1.SetItemData(n, i);
		i = i*2;
	}
	str.Format(_T("4"));
	m_combo1.SetWindowTextW(str);
	str.Format(_T("50"));
	m_ncount.SetWindowTextW(str);
	
	m_cListCtrl.InsertColumn(0, L"N", LVCFMT_LEFT, 45);
	m_cListCtrl.InsertColumn(1, L"Selection Sort", LVCFMT_LEFT, 100);
	m_cListCtrl.InsertColumn(2, L"Selection Sort OpenMP", LVCFMT_LEFT, 123);
	m_cListCtrl.InsertColumn(3, L"So luong", LVCFMT_LEFT, 123);

	return TRUE; 
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


//button random
void CMFCApplication1Dlg::OnBnClickedButton3()
{
	

	CString s1;
	m_ncount.GetWindowText(s1);
	std::wstring s((LPCTSTR)s1);
	if (s1.GetLength() <= 0)
	{
		MessageBox(L"Hãy nhập giá trị n", L"Thông báo");
		return;
	}

	N = std::stod(s);
	if (N <= 0) N = 50;
	RandomMang(N);

	int ChkBox = m_ctlCheck.GetCheck();
	if (ChkBox == BST_CHECKED)
	{
		CString strValue;
		for (int i = 0; i < N; i++)
		{
			strValue.Format(_T("a[%d] = %d"), i + 1, Arr[i]);
			m_listbox1.AddString(strValue);
		}
	}
	MessageBox(L"Khởi tạo mảng thành công", L"Thông báo");
	

}

// Button Selection Sort không song song
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	clock_t start, end;
	double time_used;
	int* b = new int[N];
	
	start = clock();
	selectionSort(b,Arr, N);
	end = clock();
	CString strValue;
	time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	strValue.Format(_T("%.6f s"), time_used);
	m_time2.SetWindowTextW(strValue);
	
	int ChkBox = m_ctlCheck.GetCheck();
	if (ChkBox == BST_CHECKED)
	{
		for (int i = 0; i < N; i++)
		{
			strValue.Format(_T("a[%d] = %d"), i + 1, b[i]);
			m_listbox2.AddString(strValue);
		}
	}
	MessageBox(L"Sắp xếp thành công", L"Thông báo");
}

// Button Selection sort su su dung song song
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	clock_t start, end;
	double time_used;
	// Nhap so luong
	CString s1;
	m_combo1.GetWindowText(s1);
	std::wstring s((LPCTSTR)s1);
	
	if (s1.GetLength() <= 0)
	{
		MessageBox(L"Hãy chọn hoặc nhập số luồng", L"Thông báo");
		return;
	}

	int _thre = std::stod(s);
	if (_thre <= 0) _thre = 4; // mặc định là 4 luồng

	int* b = new int[N];
	start = clock();
	SelectionSortParallel(b, Arr, N,_thre);
	CString strValue;
	end = clock();
	time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	strValue.Format(_T("%.6f s"), time_used);
	m_time3.SetWindowTextW(strValue);

	int ChkBox = m_ctlCheck.GetCheck();
	if (ChkBox == BST_CHECKED)
	{
		
		for (int i = 0; i < N; i++)
		{
			strValue.Format(_T("a[%d] = %d"), i + 1, b[i]);
			m_listbox3.AddString(strValue);
		}
	}
	MessageBox(L"Sắp xếp thành công", L"Thông báo");
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	m_listbox1.ResetContent();
	m_listbox2.ResetContent();
	m_listbox3.ResetContent();
	m_time2.SetWindowTextW(L"0.000");
	m_time3.SetWindowTextW(L"0.000");
}

//button them
void CMFCApplication1Dlg::OnBnClickedButton5()
{
	CString str1,str2,str3,s;
	s.Format(_T("%d"), N);
	nItem = m_cListCtrl.InsertItem(0, s);

	m_time2.GetWindowTextW(str1);
	m_cListCtrl.SetItemText(nItem, 1, str1);

	m_time3.GetWindowTextW(str2);
	m_cListCtrl.SetItemText(nItem, 2, str2);

	m_combo1.GetWindowTextW(str3);
	m_cListCtrl.SetItemText(nItem, 3, str3);
	
}

void CMFCApplication1Dlg::OnBnClickedCheck1()
{

}


void CMFCApplication1Dlg::OnStnClickedTime4()
{
	// TODO: Add your control notification handler code here
}

//chay ca 2 selection sort
void CMFCApplication1Dlg::OnBnClickedButton6()
{
	//selection sort
	clock_t start, end;
	double time_used;
	int* a = new int[N];

	start = clock();
	selectionSort(a, Arr, N);
	end = clock();
	CString strValue;
	time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	strValue.Format(_T("%.6f s"), time_used);
	m_time2.SetWindowTextW(strValue);

	int ChkBox = m_ctlCheck.GetCheck();
	if (ChkBox == BST_CHECKED)
	{
		for (int i = 0; i < N; i++)
		{
			strValue.Format(_T("a[%d] = %d"), i + 1, a[i]);
			m_listbox2.AddString(strValue);
		}
	}
	MessageBox(L"Sắp xếp thành công", L"Thông báo");

	//selection sort Omp
	// Nhap so luong
	CString s1;
	m_combo1.GetWindowText(s1);
	std::wstring s((LPCTSTR)s1);

	if (s1.GetLength() <= 0)
	{
		MessageBox(L"Hãy chọn hoặc nhập số luồng", L"Thông báo");
		return;
	}

	int _thre = std::stod(s);
	if (_thre <= 0) _thre = 4; 

	int* b = new int[N];
	start = clock();
	SelectionSortParallel(b, Arr, N, _thre);
	CString strValue1;
	end = clock();
	time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	strValue.Format(_T("%.6f s"), time_used);
	m_time3.SetWindowTextW(strValue);

	int ChkBox1 = m_ctlCheck.GetCheck();
	if (ChkBox1 == BST_CHECKED)
	{

		for (int i = 0; i < N; i++)
		{
			strValue.Format(_T("a[%d] = %d"), i + 1, b[i]);
			m_listbox3.AddString(strValue1);
		}
	}
	MessageBox(L"Sắp xếp thành công", L"Thông báo");
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
