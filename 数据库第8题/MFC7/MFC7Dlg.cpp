
// MFC7Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC7.h"
#include "MFC7Dlg.h"
#include "afxdialogex.h"

#include <winsock.h>
#include <mysql.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int SearchMode = 0;

//存信息，在修改教师界面，进行还原重新修改
char *store_id;
char *store_name;
char *store_gender;
char *store_title;
char *store_course_name;
char *store_class_name;
char *store_class_count;
char *store_theory_hour;
char *store_experiment_hour;
char *store_task_time;

//存储查询结果语句,在列表排序
char *store_sql;

//CRect  m_rect; //用于保存原对话框大小
CRect m_rect;

CTabCtrl *Tab;
//添加教师控件
CStatic *TextView_id;
CStatic *TextView_name;
CStatic *TextView_gender;
CStatic *TextView_title;
CStatic *TextView_course;
CStatic *TextView_class_name;
CStatic *TextView_class_count;
CStatic *TextView_theory_hour;
CStatic *TextView_experiment_hour;

CEdit *EditText_id;
CEdit *EditText_name;
CEdit *EditText_gender;
CEdit *EditText_title;
CEdit *EditText_course;
CEdit *EditText_class_name;
CEdit *EditText_class_count;
CEdit *EditText_theory_hour;
CEdit *EditText_experiment_hour;

CButton *Button_add;
CButton *Button_cls;

//删除教师控件
CStatic *TextView_id_delete;
CEdit *EditText_id_delete;
CButton *Button_id_delete;
CButton *Button_id_cls;

//查询教师控件
CStatic *TextView_an;
CComboBox *ComboBox;
CEdit *EditText_search;
CButton *Button_search;
CButton *Button_showAll;
CListCtrl *List;

//修改教师控件
CStatic *TextView_id_mod;
CEdit *EditText_id_mod;
CButton *Button_id_mod;
CButton *Button_modConfirm;
CButton *Button_modCancel;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFC7Dlg 对话框



CMFC7Dlg::CMFC7Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC7_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_Tab, &CMFC7Dlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_Button_add, &CMFC7Dlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_Button_cls, &CMFC7Dlg::OnBnClickedButtoncls)
	ON_BN_CLICKED(IDC_Button_id_delete, &CMFC7Dlg::OnBnClickedButtoniddelete)
	ON_CBN_SELCHANGE(IDC_ComboBox, &CMFC7Dlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_Button_search, &CMFC7Dlg::OnBnClickedButtonsearch)
	ON_BN_CLICKED(IDC_Button_id_cls, &CMFC7Dlg::OnBnClickedButtonidcls)
	ON_BN_CLICKED(IDC_Button_id_mod, &CMFC7Dlg::OnBnClickedButtonsearchmod)
	ON_BN_CLICKED(IDC_Button_modConfirm, &CMFC7Dlg::OnBnClickedButtonmodconfirm)
	ON_BN_CLICKED(IDC_Button_modCancel, &CMFC7Dlg::OnBnClickedButtonmodcancel)
	ON_BN_CLICKED(IDC_Button_showAll, &CMFC7Dlg::OnBnClickedButtonshowall)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_List, &CMFC7Dlg::OnLvnColumnclickList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_List, &CMFC7Dlg::OnLvnItemchangedList)
END_MESSAGE_MAP()



// CMFC7Dlg 消息处理程序

BOOL CMFC7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	
	// TODO: 在此添加额外的初始化代码
	GetClientRect(&m_rect); //获取对话框的大小


	Tab = (CTabCtrl *)GetDlgItem(IDC_Tab);
	Tab->InsertItem(0, _T("添加"));
	Tab->InsertItem(1, _T("修改"));
	Tab->InsertItem(2, _T("删除"));
	Tab->InsertItem(3, _T("查询"));

	//添加教师控件
	TextView_id = (CStatic *)GetDlgItem(IDC_TextView_id);
	TextView_name = (CStatic *)GetDlgItem(IDC_TextVeiw_name);
	TextView_gender = (CStatic *)GetDlgItem(IDC_TextVeiw_gender);
	TextView_title = (CStatic *)GetDlgItem(IDC_TextVeiw_title);
	TextView_course = (CStatic *)GetDlgItem(IDC_TextVeiw_course);
	TextView_class_name = (CStatic *)GetDlgItem(IDC_TextVeiw_class_name);
	TextView_class_count = (CStatic *)GetDlgItem(IDC_TextVeiw_class_count);
	TextView_theory_hour = (CStatic *)GetDlgItem(IDC_TextVeiw_theory_hour);
	TextView_experiment_hour = (CStatic *)GetDlgItem(IDC_TextVeiw_experiment_hour);

	EditText_id = (CEdit *)GetDlgItem(IDC_EditText_id);
	EditText_name = (CEdit *)GetDlgItem(IDC_EditText_name);
	EditText_gender = (CEdit *)GetDlgItem(IDC_EditText_gender);
	EditText_title = (CEdit *)GetDlgItem(IDC_EditText_title);
	EditText_course = (CEdit *)GetDlgItem(IDC_EditText_course);
	EditText_class_name = (CEdit *)GetDlgItem(IDC_EditText_class_name);
	EditText_class_count = (CEdit *)GetDlgItem(IDC_EditText_class_count);
	EditText_theory_hour = (CEdit *)GetDlgItem(IDC_EditText_theory_hour);
	EditText_experiment_hour = (CEdit *)GetDlgItem(IDC_EditText_experiment_hour);

	Button_add = (CButton *)GetDlgItem(IDC_Button_add);
	Button_cls = (CButton *)GetDlgItem(IDC_Button_cls);

	//删除教师控件
	TextView_id_delete = (CStatic *)GetDlgItem(IDC_TextView_id_delete);
	EditText_id_delete = (CEdit *)GetDlgItem(IDC_EditText_id_delete);
	Button_id_delete = (CButton *)GetDlgItem(IDC_Button_id_delete);
	Button_id_cls = (CButton *)GetDlgItem(IDC_Button_id_cls);

	//查询教师控件
	ComboBox = (CComboBox *)GetDlgItem(IDC_ComboBox);
	SetDlgItemText(IDC_ComboBox, "教师号");
	ComboBox->InsertString(0, "教师号");
	ComboBox->InsertString(1, "姓名");
	ComboBox->InsertString(2, "性别");
	ComboBox->InsertString(3, "职称");
	ComboBox->InsertString(4, "任教课程");
	ComboBox->InsertString(5, "班级名");
	ComboBox->InsertString(6, "班级数目");
	ComboBox->InsertString(7, "理论课时");
	ComboBox->InsertString(8, "实验课时");
	ComboBox->InsertString(9, "教学工作量");
	TextView_an = (CStatic *)GetDlgItem(IDC_TextView_an);
	ComboBox = (CComboBox *)GetDlgItem(IDC_ComboBox);
	EditText_search = (CEdit *)GetDlgItem(IDC_EditText_search);
	Button_search = (CButton *)GetDlgItem(IDC_Button_search);
	Button_showAll = (CButton *)GetDlgItem(IDC_Button_showAll);
	List = (CListCtrl *)GetDlgItem(IDC_List);

	//修改教师控件
	TextView_id_mod = (CStatic *)GetDlgItem(IDC_TextView_id_mod);
	EditText_id_mod = (CEdit *)GetDlgItem(IDC_EditText_id_mod);
	Button_id_mod = (CButton *)GetDlgItem(IDC_Button_id_mod);
	Button_modConfirm = (CButton *)GetDlgItem(IDC_Button_modConfirm);
	Button_modCancel = (CButton *)GetDlgItem(IDC_Button_modCancel);


	//设置文本编辑框只能输入数字
	SetInputOnlyNumber(EditText_id);
	SetInputOnlyNumber(EditText_class_count);
	SetInputOnlyNumber(EditText_theory_hour);
	SetInputOnlyNumber(EditText_experiment_hour);
	SetInputOnlyNumber(EditText_id_mod);
	SetInputOnlyNumber(EditText_id_delete);


	List->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	//List->InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	List->InsertColumn(0, _T("教师号"), LVCFMT_LEFT, 100);        // 插入第1列的列名  
	List->InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);        // 插入第2列的列名  
	List->InsertColumn(2, _T("性别"), LVCFMT_LEFT, 50);        // 插入第3列的列名  
	List->InsertColumn(3, _T("职称"), LVCFMT_LEFT, 75);
	List->InsertColumn(4, _T("任教课程"), LVCFMT_LEFT, 100);
	List->InsertColumn(5, _T("班级"), LVCFMT_LEFT, 140);
	List->InsertColumn(6, _T("班级数目"), LVCFMT_LEFT, 80);
	List->InsertColumn(7, _T("理论课时"), LVCFMT_LEFT, 80);
	List->InsertColumn(8, _T("实验课时"), LVCFMT_LEFT, 80);
	List->InsertColumn(9, _T("教学工作量"), LVCFMT_LEFT, 90);




	//隐藏控件
	TextView_id_delete->ShowWindow(SW_HIDE);
	EditText_id_delete->ShowWindow(SW_HIDE);
	Button_id_delete->ShowWindow(SW_HIDE);
	Button_id_cls->ShowWindow(SW_HIDE);

	TextView_an->ShowWindow(SW_HIDE);
	ComboBox->ShowWindow(SW_HIDE);
	EditText_search->ShowWindow(SW_HIDE);
	Button_search->ShowWindow(SW_HIDE);
	Button_showAll->ShowWindow(SW_HIDE);
	List->ShowWindow(SW_HIDE);

	TextView_id_mod->ShowWindow(SW_HIDE);
	EditText_id_mod->ShowWindow(SW_HIDE);
	Button_id_mod->ShowWindow(SW_HIDE);
	Button_modConfirm->ShowWindow(SW_HIDE);
	Button_modCancel->ShowWindow(SW_HIDE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC7Dlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: 在此添加控件通知处理程序代码
	int select = Tab->GetCurSel();
	switch (select)
	{
	case 0://添加教师
		//显示控件
		TextView_id->ShowWindow(SW_SHOW);
		TextView_name->ShowWindow(SW_SHOW);
		TextView_gender->ShowWindow(SW_SHOW);
		TextView_title->ShowWindow(SW_SHOW);
		TextView_course->ShowWindow(SW_SHOW);
		TextView_class_name->ShowWindow(SW_SHOW);
		TextView_class_count->ShowWindow(SW_SHOW);
		TextView_theory_hour->ShowWindow(SW_SHOW);
		TextView_experiment_hour->ShowWindow(SW_SHOW);

		EditText_id->ShowWindow(SW_SHOW);
		EditText_name->ShowWindow(SW_SHOW);
		EditText_gender->ShowWindow(SW_SHOW);
		EditText_title->ShowWindow(SW_SHOW);
		EditText_course->ShowWindow(SW_SHOW);
		EditText_class_name->ShowWindow(SW_SHOW);
		EditText_class_count->ShowWindow(SW_SHOW);
		EditText_theory_hour->ShowWindow(SW_SHOW);
		EditText_experiment_hour->ShowWindow(SW_SHOW);

		Button_add->ShowWindow(SW_SHOW);
		Button_cls->ShowWindow(SW_SHOW);

		//隐藏控件
		TextView_id_delete->ShowWindow(SW_HIDE);
		EditText_id_delete->ShowWindow(SW_HIDE);
		Button_id_delete->ShowWindow(SW_HIDE);
		Button_id_cls->ShowWindow(SW_HIDE);

		TextView_an->ShowWindow(SW_HIDE);
		ComboBox->ShowWindow(SW_HIDE);
		EditText_search->ShowWindow(SW_HIDE);
		Button_search->ShowWindow(SW_HIDE);
		Button_showAll->ShowWindow(SW_HIDE);
		List->ShowWindow(SW_HIDE);

		TextView_id_mod->ShowWindow(SW_HIDE);
		EditText_id_mod->ShowWindow(SW_HIDE);
		Button_id_mod->ShowWindow(SW_HIDE);

		Button_modConfirm->ShowWindow(SW_HIDE);
		Button_modCancel->ShowWindow(SW_HIDE);
		break;
	case 1://修改教师
		//显示控件
		TextView_id_mod->ShowWindow(SW_SHOW);
		EditText_id_mod->ShowWindow(SW_SHOW);
		Button_id_mod->ShowWindow(SW_SHOW);
		Button_modConfirm->ShowWindow(SW_SHOW);
		Button_modCancel->ShowWindow(SW_SHOW);

		TextView_id->ShowWindow(SW_SHOW);
		TextView_name->ShowWindow(SW_SHOW);
		TextView_gender->ShowWindow(SW_SHOW);
		TextView_title->ShowWindow(SW_SHOW);
		TextView_course->ShowWindow(SW_SHOW);
		TextView_class_name->ShowWindow(SW_SHOW);
		TextView_class_count->ShowWindow(SW_SHOW);
		TextView_theory_hour->ShowWindow(SW_SHOW);
		TextView_experiment_hour->ShowWindow(SW_SHOW);

		EditText_id->ShowWindow(SW_SHOW);
		EditText_name->ShowWindow(SW_SHOW);
		EditText_gender->ShowWindow(SW_SHOW);
		EditText_title->ShowWindow(SW_SHOW);
		EditText_course->ShowWindow(SW_SHOW);
		EditText_class_name->ShowWindow(SW_SHOW);
		EditText_class_count->ShowWindow(SW_SHOW);
		EditText_theory_hour->ShowWindow(SW_SHOW);
		EditText_experiment_hour->ShowWindow(SW_SHOW);

		//隐藏控件
		Button_add->ShowWindow(SW_HIDE);
		Button_cls->ShowWindow(SW_HIDE);

		TextView_id_delete->ShowWindow(SW_HIDE);
		EditText_id_delete->ShowWindow(SW_HIDE);
		Button_id_delete->ShowWindow(SW_HIDE);
		Button_id_cls->ShowWindow(SW_HIDE);

		TextView_an->ShowWindow(SW_HIDE);
		ComboBox->ShowWindow(SW_HIDE);
		EditText_search->ShowWindow(SW_HIDE);
		Button_search->ShowWindow(SW_HIDE);
		Button_showAll->ShowWindow(SW_HIDE);
		List->ShowWindow(SW_HIDE);
		break;
	case 2://删除教师
		//隐藏控件
		TextView_id->ShowWindow(SW_HIDE);
		TextView_name->ShowWindow(SW_HIDE);
		TextView_gender->ShowWindow(SW_HIDE);
		TextView_title->ShowWindow(SW_HIDE);
		TextView_course->ShowWindow(SW_HIDE);
		TextView_class_name->ShowWindow(SW_HIDE);
		TextView_class_count->ShowWindow(SW_HIDE);
		TextView_theory_hour->ShowWindow(SW_HIDE);
		TextView_experiment_hour->ShowWindow(SW_HIDE);

		EditText_id->ShowWindow(SW_HIDE);
		EditText_name->ShowWindow(SW_HIDE);
		EditText_gender->ShowWindow(SW_HIDE);
		EditText_title->ShowWindow(SW_HIDE);
		EditText_course->ShowWindow(SW_HIDE);
		EditText_class_name->ShowWindow(SW_HIDE);
		EditText_class_count->ShowWindow(SW_HIDE);
		EditText_theory_hour->ShowWindow(SW_HIDE);
		EditText_experiment_hour->ShowWindow(SW_HIDE);

		Button_add->ShowWindow(SW_HIDE);
		Button_cls->ShowWindow(SW_HIDE);

		TextView_an->ShowWindow(SW_HIDE);
		ComboBox->ShowWindow(SW_HIDE);
		EditText_search->ShowWindow(SW_HIDE);
		Button_search->ShowWindow(SW_HIDE);
		Button_showAll->ShowWindow(SW_HIDE);
		List->ShowWindow(SW_HIDE);

		TextView_id_mod->ShowWindow(SW_HIDE);
		EditText_id_mod->ShowWindow(SW_HIDE);
		Button_id_mod->ShowWindow(SW_HIDE);
		Button_modConfirm->ShowWindow(SW_HIDE);
		Button_modCancel->ShowWindow(SW_HIDE);

		//显示控件
		TextView_id_delete->ShowWindow(SW_SHOW);
		EditText_id_delete->ShowWindow(SW_SHOW);
		Button_id_delete->ShowWindow(SW_SHOW);
		Button_id_cls->ShowWindow(SW_SHOW);
		break;
	case 3://查询或显示全部教师
		//显示控件
		TextView_an->ShowWindow(SW_SHOW);
		ComboBox->ShowWindow(SW_SHOW);
		EditText_search->ShowWindow(SW_SHOW);
		Button_search->ShowWindow(SW_SHOW);
		Button_showAll->ShowWindow(SW_SHOW);
		List->ShowWindow(SW_SHOW);

		//隐藏控件
		TextView_id->ShowWindow(SW_HIDE);
		TextView_name->ShowWindow(SW_HIDE);
		TextView_gender->ShowWindow(SW_HIDE);
		TextView_title->ShowWindow(SW_HIDE);
		TextView_course->ShowWindow(SW_HIDE);
		TextView_class_name->ShowWindow(SW_HIDE);
		TextView_class_count->ShowWindow(SW_HIDE);
		TextView_theory_hour->ShowWindow(SW_HIDE);
		TextView_experiment_hour->ShowWindow(SW_HIDE);

		EditText_id->ShowWindow(SW_HIDE);
		EditText_name->ShowWindow(SW_HIDE);
		EditText_gender->ShowWindow(SW_HIDE);
		EditText_title->ShowWindow(SW_HIDE);
		EditText_course->ShowWindow(SW_HIDE);
		EditText_class_name->ShowWindow(SW_HIDE);
		EditText_class_count->ShowWindow(SW_HIDE);
		EditText_theory_hour->ShowWindow(SW_HIDE);
		EditText_experiment_hour->ShowWindow(SW_HIDE);

		Button_add->ShowWindow(SW_HIDE);
		Button_cls->ShowWindow(SW_HIDE);

		TextView_id_delete->ShowWindow(SW_HIDE);
		EditText_id_delete->ShowWindow(SW_HIDE);
		Button_id_delete->ShowWindow(SW_HIDE);
		Button_id_cls->ShowWindow(SW_HIDE);

		TextView_id_mod->ShowWindow(SW_HIDE);
		EditText_id_mod->ShowWindow(SW_HIDE);
		Button_id_mod->ShowWindow(SW_HIDE);
		Button_modConfirm->ShowWindow(SW_HIDE);
		Button_modCancel->ShowWindow(SW_HIDE);

		List->DeleteAllItems();
		ExecuteSqlSelect("Select * from teacher_info");
		store_sql = "Select * from teacher_info";
		break;
	}
	*pResult = 0;
}


void CMFC7Dlg::OnBnClickedButtonadd()
{
	if (isAddUiEmpty())
	{
		ShowMB("信息不完整");
		return;
	}

	CString str_id;
	CString name;
	CString gender;
	CString title;
	CString course_name;
	CString class_name;
	CString str_class_count;
	CString str_theory_hour;
	CString str_experiment_hour;
	int task_time;

	EditText_id->GetWindowText(str_id);
	EditText_name->GetWindowText(name);
	EditText_gender->GetWindowText(gender);
	EditText_title->GetWindowText(title);
	EditText_course->GetWindowText(course_name);
	EditText_class_name->GetWindowText(class_name);
	EditText_class_count->GetWindowText(str_class_count);
	EditText_theory_hour->GetWindowText(str_theory_hour);
	EditText_experiment_hour->GetWindowText(str_experiment_hour);

	int id = _ttoi(str_id);
	int class_count = _ttoi(str_class_count);
	int theory_hour = _ttoi(str_theory_hour);
	int experiment_hour = _ttoi(str_experiment_hour);

	switch (class_count)
	{
	case 1:
		task_time = theory_hour + experiment_hour;
		break;
	case 2:
		task_time = 1.5 * (theory_hour + experiment_hour);
		break;
	case 3:
		task_time = 2 * (theory_hour + experiment_hour);
		break;
	default:
		task_time = 2.5 * (theory_hour + experiment_hour);
		break;
	}

	char sql[1024] = { 0 };

	MYSQL* mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	if (mysql_query(mysql, "set names gbk"))//设置编码
	{
		goto error;
	}
	sprintf(sql,
		"Insert into teacher_info(教师号,姓名,性别,职称,任教课程,班级,班级数目,理论课时,实验课时,教学工作量) values('%d','%s','%s','%s','%s','%s','%d','%d','%d','%d')",
		id, name, gender, title, course_name, class_name, class_count, theory_hour, experiment_hour, task_time);
	if (mysql_query(mysql, sql))
	{
		printf("插入失败,%s", mysql_error(mysql));
		goto error;
	}
	//cout << "添加教师成功" << endl;
	//::MessageBox(NULL, _T("添加教师成功"), _T("消息"), MB_OK);
	ShowMB("添加教师成功");
	goto exit;
error:
	//::MessageBox(NULL, _T("执行出错"), _T("消息"), MB_OK);
	ShowMB("执行出错");
	//cout << "执行出错:" << mysql_error(mysql);
exit:
	mysql_close(mysql);

}


void CMFC7Dlg::OnBnClickedButtoncls()
{
	// TODO: 在此添加控件通知处理程序代码
	EditText_id->SetWindowText("");
	EditText_name->SetWindowText("");
	EditText_gender->SetWindowText("");
	EditText_title->SetWindowText("");
	EditText_course->SetWindowText("");
	EditText_class_name->SetWindowText("");
	EditText_class_count->SetWindowText("");
	EditText_theory_hour->SetWindowText("");
	EditText_experiment_hour->SetWindowText("");
}

void CMFC7Dlg::SetInputOnlyNumber(CEdit *c)
{
	DWORD dwStyle = c->GetStyle();
	dwStyle |= ES_NUMBER;
	SetWindowLong(c->m_hWnd, GWL_STYLE, dwStyle);
}

void CMFC7Dlg::OnBnClickedButtonidcls()
{
	// TODO: 在此添加控件通知处理程序代码
	EditText_id_delete->SetWindowText("");
}


void CMFC7Dlg::OnBnClickedButtoniddelete()
{
	if (isDeleteEmpty())
	{
		ShowMB("请输入教师号");
		return;
	}
	//判断是否有该教师id
	{
		CString str_id;
		EditText_id_delete->GetWindowText(str_id);
		int id = _ttoi(str_id);
		char sql[1024] = { 0 };
		sprintf(sql, "Select * from teacher_info where 教师号 = %d", id);

		MYSQL *mysql = mysql_init(0);
		if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
		{
			//goto error;
		}
		printf("连接数据库成功！\n");
		if (mysql_query(mysql, "set names gbk"))
		{
			//goto error;
		}
		if (mysql_query(mysql, sql))
		{
			//goto error;
		}
		{
			//离线结果集（数据放到了客户端），对于小结果集比较合适
			MYSQL_RES *result = mysql_store_result(mysql);
			//获取数据行数,为0说明没有数据
			int data = mysql_num_rows(result);
			if (data == 0)
			{
				ShowMB("没有该教师");
				return;
			}
			mysql_free_result(result);//释放本地内存中的查询结果
			mysql_close(mysql);//程序最后必须关闭连接，否则会有mysql服务器连接过多卡死的可能性
		}
	}
	//////////////////////////////////////////
	CString str_id;
	EditText_id_delete->GetWindowText(str_id);
	int id = _ttoi(str_id);

	char sql[1024] = { 0 };
	MYSQL* mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	if (mysql_query(mysql, "set names gbk"))//设置编码
	{
		goto error;
	}
	sprintf(sql,
		"delete from teacher_info where 教师号 = %d", id);
	if (mysql_query(mysql, sql))
	{
		printf("删除失败,%s", mysql_error(mysql));
		goto error;
	}
	ShowMB("删除教师成功");
	goto exit;
error:
	ShowMB("执行出错");
exit:
	mysql_close(mysql);
	EditText_id_delete->SetWindowText("");
}

void CMFC7Dlg::ShowMB(char message[9])
{
	::MessageBox(NULL, _T(message), _T("消息"), MB_OK);
}

void CMFC7Dlg::OnCbnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString select;
	//ComboBox->GetWindowText(select);
	int select = ComboBox->GetCurSel();
	switch (select)
	{
	case 0:
		SearchMode = 0;
		break;
	case 1:
		SearchMode = 1;
		break;
	case 2:
		SearchMode = 2;
		break;
	case 3:
		SearchMode = 3;
		break;
	case 4:
		SearchMode = 4;
		break;
	case 5:
		SearchMode = 5;
		break;
	case 6:
		SearchMode = 6;
		break;
	case 7:
		SearchMode = 7;
		break;
	case 8:
		SearchMode = 8;
		break;
	case 9:
		SearchMode = 9;
		break;
	}
}


void CMFC7Dlg::OnBnClickedButtonsearch()
{
	if (isSearchEmpty())
	{
		ShowMB("请输入查询信息");
		return;
	}

	List->DeleteAllItems();
	CString searchInfo;
	EditText_search->GetWindowText(searchInfo);
	char *c = searchInfo.GetBuffer(searchInfo.GetLength());

	char sql[1024];
	switch (SearchMode)
	{
	case 0:
		sprintf(sql, "Select * from teacher_info where 教师号 = %d", _ttoi(searchInfo));
		break;
	case 1:
		sprintf(sql, "Select * from teacher_info where 姓名 = '%s'", c);
		break;
	case 2:
		sprintf(sql, "Select * from teacher_info where 性别 = '%s'", c);
		break;
	case 3:
		sprintf(sql, "Select * from teacher_info where 职称 = '%s'", c);
		break;
	case 4:
		sprintf(sql, "Select * from teacher_info where 任教课程 = '%s'", c);
		break;
	case 5:
		sprintf(sql, "Select * from teacher_info where 班级 like '%s%s%s'", "%", c, "%");
		break;
	case 6:
		sprintf(sql, "Select * from teacher_info where 班级数目 = %d", _ttoi(searchInfo));
		break;
	case 7:
		sprintf(sql, "Select * from teacher_info where 理论课时 = %d", _ttoi(searchInfo));
		break;
	case 8:
		sprintf(sql, "Select * from teacher_info where 实验课时 = %d", _ttoi(searchInfo));
		break;
	case 9:
		sprintf(sql, "Select * from teacher_info where 教学工作量 = %d", _ttoi(searchInfo));
		break;
	}
	store_sql = (char *)malloc(strlen(sql));
	sprintf(store_sql, "%s", sql);
	ExecuteSqlSelect(sql);
}


void CMFC7Dlg::ExecuteSqlSelect(char *sql)
{
	MYSQL *mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	printf("连接数据库成功！\n");
	if (mysql_query(mysql, "set names gbk"))
	{
		goto error;
	}
	if (mysql_query(mysql, sql))
	{
		goto error;
	}
	{
		//离线结果集（数据放到了客户端），对于小结果集比较合适
		MYSQL_RES *result = mysql_store_result(mysql);
		//执行完了mysql_store_result之后，其实断开数据库连接也没关系
		MYSQL_ROW row;
		//只要还有数据那么while就一直执行
		//mysql_fetch_row是“箭头/游标”向下移动一行，并且获得这一行数据的MSQL_ROW对象
		//如果没有数据则返回0
		int i = 0;
		while (row = mysql_fetch_row(result))
		{
			char *id = row[0];
			char *name = row[1];
			char *gender = row[2];
			char *title = row[3];
			char *course_name = row[4];
			char *class_name = row[5];
			char *class_count = row[6];
			char *theory_hour = row[7];
			char *experiment_hour = row[8];
			char *task_time = row[9];

			List->InsertItem(i, _T(""));                          // 插入行
			List->SetItemText(i, 0, id);                     // 设置第1列(姓名)
			List->SetItemText(i, 1, name);                      // 设置第2列(年龄)  
			List->SetItemText(i, 2, gender);                      // 设置第3列(性别)
			List->SetItemText(i, 3, title);
			List->SetItemText(i, 4, course_name);
			List->SetItemText(i, 5, class_name);
			List->SetItemText(i, 6, class_count);
			List->SetItemText(i, 7, theory_hour);
			List->SetItemText(i, 8, experiment_hour);
			List->SetItemText(i, 9, task_time);

			i++;
		}
		mysql_free_result(result);//释放本地内存中的查询结果
	}
	goto exit;
error:
	printf("执行出错：%s", mysql_error(mysql));
exit:
	mysql_close(mysql);//程序最后必须关闭连接，否则会有mysql服务器连接过多卡死的可能性
}


void CMFC7Dlg::OnBnClickedButtonsearchmod()
{
	if (isSearchIdModEmpty())
	{
		ShowMB("请输入要修改的教师号");
		return;
	}

	CString str_id;
	EditText_id_mod->GetWindowText(str_id);
	int id = _ttoi(str_id);
	char sql[1024] = { 0 };
	sprintf(sql, "Select * from teacher_info where 教师号 = %d", id);

	MYSQL *mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	printf("连接数据库成功！\n");
	if (mysql_query(mysql, "set names gbk"))
	{
		goto error;
	}
	if (mysql_query(mysql, sql))
	{
		goto error;
	}
	{
		//离线结果集（数据放到了客户端），对于小结果集比较合适
		MYSQL_RES *result = mysql_store_result(mysql);
		//获取数据行数,为0说明没有数据
		int data = mysql_num_rows(result);
		if (data == 0)
		{
			ShowMB("没有该教师");
			return;
		}
		//执行完了mysql_store_result之后，其实断开数据库连接也没关系
		MYSQL_ROW row;
		//只要还有数据那么while就一直执行
		//mysql_fetch_row是“箭头/游标”向下移动一行，并且获得这一行数据的MSQL_ROW对象
		//如果没有数据则返回0
		row = mysql_fetch_row(result);
		char *id = row[0];
		char *name = row[1];
		char *gender = row[2];
		char *title = row[3];
		char *course_name = row[4];
		char *class_name = row[5];
		char *class_count = row[6];
		char *theory_hour = row[7];
		char *experiment_hour = row[8];
		//char *task_time = row[9];

		EditText_id->SetWindowText(id);
		EditText_name->SetWindowText(name);
		EditText_gender->SetWindowText(gender);
		EditText_title->SetWindowText(title);
		EditText_course->SetWindowText(course_name);
		EditText_class_name->SetWindowText(class_name);
		EditText_class_count->SetWindowText(class_count);
		EditText_theory_hour->SetWindowText(theory_hour);
		EditText_experiment_hour->SetWindowText(experiment_hour);

		store_id = id;
		store_name = name;
		store_gender = gender;
		store_title = title;
		store_course_name = course_name;
		store_class_name = class_name;
		store_class_count = class_count;
		store_theory_hour = theory_hour;
		store_experiment_hour = experiment_hour;
		//char *store_task_time = task_time;

		mysql_free_result(result);//释放本地内存中的查询结果

		goto exit;
	error:
		printf("执行出错：%s", mysql_error(mysql));
	exit:
		mysql_close(mysql);//程序最后必须关闭连接，否则会有mysql服务器连接过多卡死的可能性
	}
}


void CMFC7Dlg::OnBnClickedButtonmodconfirm()
{
	if (isAddUiEmpty())
	{
		ShowMB("信息不完整");
		return;
	}

	CString str_id;
	CString name;
	CString gender;
	CString title;
	CString course_name;
	CString class_name;
	CString str_class_count;
	CString str_theory_hour;
	CString str_experiment_hour;
	int task_time;

	EditText_id->GetWindowText(str_id);
	EditText_name->GetWindowText(name);
	EditText_gender->GetWindowText(gender);
	EditText_title->GetWindowText(title);
	EditText_course->GetWindowText(course_name);
	EditText_class_name->GetWindowText(class_name);
	EditText_class_count->GetWindowText(str_class_count);
	EditText_theory_hour->GetWindowText(str_theory_hour);
	EditText_experiment_hour->GetWindowText(str_experiment_hour);

	int id = _ttoi(str_id);
	int class_count = _ttoi(str_class_count);
	int theory_hour = _ttoi(str_theory_hour);
	int experiment_hour = _ttoi(str_experiment_hour);

	switch (class_count)
	{
	case 1:
		task_time = theory_hour + experiment_hour;
		break;
	case 2:
		task_time = 1.5 * (theory_hour + experiment_hour);
		break;
	case 3:
		task_time = 2 * (theory_hour + experiment_hour);
		break;
	default:
		task_time = 2.5 * (theory_hour + experiment_hour);
		break;
	}

	char sql[1024] = { 0 };

	MYSQL* mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	if (mysql_query(mysql, "set names gbk"))//设置编码
	{
		goto error;
	}
	sprintf(sql,
		"Update teacher_info set 教师号 = %d,姓名 = '%s',性别 = '%s',职称 = '%s',任教课程 = '%s',班级 = '%s',班级数目 = %d,理论课时 = %d,实验课时 = %d,教学工作量 = %d where 教师号 = %d",
		id, name, gender, title, course_name, class_name, class_count, theory_hour, experiment_hour, task_time, atoi(store_id));
	if (mysql_query(mysql, sql))
	{
		printf("插入失败,%s", mysql_error(mysql));
		goto error;
	}
	//cout << "添加教师成功" << endl;
	//::MessageBox(NULL, _T("添加教师成功"), _T("消息"), MB_OK);
	ShowMB("修改教师信息成功");
	goto exit;
error:
	//::MessageBox(NULL, _T("执行出错"), _T("消息"), MB_OK);
	ShowMB("执行出错");
	//cout << "执行出错:" << mysql_error(mysql);
exit:
	EditText_id_mod->SetWindowText("");
	EditText_id->SetWindowText("");
	EditText_name->SetWindowText("");
	EditText_gender->SetWindowText("");
	EditText_title->SetWindowText("");
	EditText_course->SetWindowText("");
	EditText_class_name->SetWindowText("");
	EditText_class_count->SetWindowText("");
	EditText_theory_hour->SetWindowText("");
	EditText_experiment_hour->SetWindowText("");

	store_id = "";
	store_name = "";
	store_gender = "";
	store_title = "";
	store_course_name = "";
	store_class_name = "";
	store_class_count = "";
	store_theory_hour = "";
	store_experiment_hour = "";

	mysql_close(mysql);
}


void CMFC7Dlg::OnBnClickedButtonmodcancel()
{
	EditText_id->SetWindowText(store_id);
	EditText_name->SetWindowText(store_name);
	EditText_gender->SetWindowText(store_gender);
	EditText_title->SetWindowText(store_title);
	EditText_course->SetWindowText(store_course_name);
	EditText_class_name->SetWindowText(store_class_name);
	EditText_class_count->SetWindowText(store_class_count);
	EditText_theory_hour->SetWindowText(store_theory_hour);
	EditText_experiment_hour->SetWindowText(store_experiment_hour);
}

bool CMFC7Dlg::isAddUiEmpty()
{
	CString str_id;
	CString name;
	CString gender;
	CString title;
	CString course_name;
	CString class_name;
	CString str_class_count;
	CString str_theory_hour;
	CString str_experiment_hour;

	EditText_id->GetWindowText(str_id);
	EditText_name->GetWindowText(name);
	EditText_gender->GetWindowText(gender);
	EditText_title->GetWindowText(title);
	EditText_course->GetWindowText(course_name);
	EditText_class_name->GetWindowText(class_name);
	EditText_class_count->GetWindowText(str_class_count);
	EditText_theory_hour->GetWindowText(str_theory_hour);
	EditText_experiment_hour->GetWindowText(str_experiment_hour);

	if (str_id == "" || name == "" || gender == "" || title == "" || course_name == "" || class_name == "" ||
		str_class_count == "" || str_theory_hour == "" || str_experiment_hour == "")
	{
		return true;
	}
	else
		return false;
}

bool CMFC7Dlg::isSearchIdModEmpty()
{
	CString temp;
	EditText_id_mod->GetWindowText(temp);
	return temp == "" ? true : false;
}

bool CMFC7Dlg::isDeleteEmpty()
{
	CString temp;
	EditText_id_delete->GetWindowText(temp);
	return temp == "" ? true : false;
}

bool CMFC7Dlg::isSearchEmpty()
{
	CString temp;
	EditText_search->GetWindowText(temp);
	return temp == "" ? true : false;
}

void CMFC7Dlg::OnBnClickedButtonshowall()
{
	List->DeleteAllItems();
	ExecuteSqlSelect("Select * from teacher_info");
	store_sql = "Select * from teacher_info";
}


bool sortFlag = false;
void CMFC7Dlg::OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int itemCount = List->GetItemCount();
	if (itemCount == 0)
		return;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	int clicked = pNMLV->iSubItem;
	
	List->DeleteAllItems();
	char sql[1024];

	switch (clicked)
	{
	case 0:
		sprintf(sql, "%s order by 教师号 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 1:
		sprintf(sql, "%s order by 姓名 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 2:
		sprintf(sql, "%s order by 性别 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 3:
		sprintf(sql, "%s order by 职称 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 4:
		sprintf(sql, "%s order by 任教课程 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 5:
		sprintf(sql, "%s order by 班级 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 6:
		sprintf(sql, "%s order by 班级数目 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 7:
		sprintf(sql, "%s order by 理论课时 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 8:
		sprintf(sql, "%s order by 实验课时 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 9:
		sprintf(sql, "%s order by 教学工作量 %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	}
	ExecuteSqlSelect(sql);
	sortFlag = sortFlag ? !sortFlag : !sortFlag;
	*pResult = 0;
}

void CMFC7Dlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFC7Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here


	if (nType != SIZE_MINIMIZED) //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{


		ChangeSize(IDC_List, cx, cy); //对每一个控件依次做调整
	
		GetClientRect(&m_rect); //最后要更新对话框的大小，当做下一次变化的旧坐标


	}
}

void CMFC7Dlg::ChangeSize(UINT nID, int x, int y) //nID为控件ID，x,y分别为对话框的当前长和宽
{


	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{


		CRect rec;
		pWnd->GetWindowRect(&rec); //获取控件变化前的大小
		ScreenToClient(&rec); //将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x / m_rect.Width(); //按照比例调整空间的新位置
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec); //伸缩控件


	}
}