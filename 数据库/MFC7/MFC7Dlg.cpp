
// MFC7Dlg.cpp : ʵ���ļ�
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

//����Ϣ�����޸Ľ�ʦ���棬���л�ԭ�����޸�
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

//�洢��ѯ������,���б�����
char *store_sql;

//CRect  m_rect; //���ڱ���ԭ�Ի����С
CRect m_rect;

CTabCtrl *Tab;
//��ӽ�ʦ�ؼ�
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

//ɾ����ʦ�ؼ�
CStatic *TextView_id_delete;
CEdit *EditText_id_delete;
CButton *Button_id_delete;
CButton *Button_id_cls;

//��ѯ��ʦ�ؼ�
CStatic *TextView_an;
CComboBox *ComboBox;
CEdit *EditText_search;
CButton *Button_search;
CButton *Button_showAll;
CListCtrl *List;

//�޸Ľ�ʦ�ؼ�
CStatic *TextView_id_mod;
CEdit *EditText_id_mod;
CButton *Button_id_mod;
CButton *Button_modConfirm;
CButton *Button_modCancel;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFC7Dlg �Ի���



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



// CMFC7Dlg ��Ϣ�������

BOOL CMFC7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetClientRect(&m_rect); //��ȡ�Ի���Ĵ�С


	Tab = (CTabCtrl *)GetDlgItem(IDC_Tab);
	Tab->InsertItem(0, _T("���"));
	Tab->InsertItem(1, _T("�޸�"));
	Tab->InsertItem(2, _T("ɾ��"));
	Tab->InsertItem(3, _T("��ѯ"));

	//��ӽ�ʦ�ؼ�
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

	//ɾ����ʦ�ؼ�
	TextView_id_delete = (CStatic *)GetDlgItem(IDC_TextView_id_delete);
	EditText_id_delete = (CEdit *)GetDlgItem(IDC_EditText_id_delete);
	Button_id_delete = (CButton *)GetDlgItem(IDC_Button_id_delete);
	Button_id_cls = (CButton *)GetDlgItem(IDC_Button_id_cls);

	//��ѯ��ʦ�ؼ�
	ComboBox = (CComboBox *)GetDlgItem(IDC_ComboBox);
	SetDlgItemText(IDC_ComboBox, "��ʦ��");
	ComboBox->InsertString(0, "��ʦ��");
	ComboBox->InsertString(1, "����");
	ComboBox->InsertString(2, "�Ա�");
	ComboBox->InsertString(3, "ְ��");
	ComboBox->InsertString(4, "�ν̿γ�");
	ComboBox->InsertString(5, "�༶��");
	ComboBox->InsertString(6, "�༶��Ŀ");
	ComboBox->InsertString(7, "���ۿ�ʱ");
	ComboBox->InsertString(8, "ʵ���ʱ");
	ComboBox->InsertString(9, "��ѧ������");
	TextView_an = (CStatic *)GetDlgItem(IDC_TextView_an);
	ComboBox = (CComboBox *)GetDlgItem(IDC_ComboBox);
	EditText_search = (CEdit *)GetDlgItem(IDC_EditText_search);
	Button_search = (CButton *)GetDlgItem(IDC_Button_search);
	Button_showAll = (CButton *)GetDlgItem(IDC_Button_showAll);
	List = (CListCtrl *)GetDlgItem(IDC_List);

	//�޸Ľ�ʦ�ؼ�
	TextView_id_mod = (CStatic *)GetDlgItem(IDC_TextView_id_mod);
	EditText_id_mod = (CEdit *)GetDlgItem(IDC_EditText_id_mod);
	Button_id_mod = (CButton *)GetDlgItem(IDC_Button_id_mod);
	Button_modConfirm = (CButton *)GetDlgItem(IDC_Button_modConfirm);
	Button_modCancel = (CButton *)GetDlgItem(IDC_Button_modCancel);


	//�����ı��༭��ֻ����������
	SetInputOnlyNumber(EditText_id);
	SetInputOnlyNumber(EditText_class_count);
	SetInputOnlyNumber(EditText_theory_hour);
	SetInputOnlyNumber(EditText_experiment_hour);
	SetInputOnlyNumber(EditText_id_mod);
	SetInputOnlyNumber(EditText_id_delete);


	List->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	//List->InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	List->InsertColumn(0, _T("��ʦ��"), LVCFMT_LEFT, 100);        // �����1�е�����  
	List->InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);        // �����2�е�����  
	List->InsertColumn(2, _T("�Ա�"), LVCFMT_LEFT, 50);        // �����3�е�����  
	List->InsertColumn(3, _T("ְ��"), LVCFMT_LEFT, 75);
	List->InsertColumn(4, _T("�ν̿γ�"), LVCFMT_LEFT, 100);
	List->InsertColumn(5, _T("�༶"), LVCFMT_LEFT, 140);
	List->InsertColumn(6, _T("�༶��Ŀ"), LVCFMT_LEFT, 80);
	List->InsertColumn(7, _T("���ۿ�ʱ"), LVCFMT_LEFT, 80);
	List->InsertColumn(8, _T("ʵ���ʱ"), LVCFMT_LEFT, 80);
	List->InsertColumn(9, _T("��ѧ������"), LVCFMT_LEFT, 90);




	//���ؿؼ�
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC7Dlg::OnPaint()
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
HCURSOR CMFC7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC7Dlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int select = Tab->GetCurSel();
	switch (select)
	{
	case 0://��ӽ�ʦ
		//��ʾ�ؼ�
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

		//���ؿؼ�
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
	case 1://�޸Ľ�ʦ
		//��ʾ�ؼ�
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

		//���ؿؼ�
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
	case 2://ɾ����ʦ
		//���ؿؼ�
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

		//��ʾ�ؼ�
		TextView_id_delete->ShowWindow(SW_SHOW);
		EditText_id_delete->ShowWindow(SW_SHOW);
		Button_id_delete->ShowWindow(SW_SHOW);
		Button_id_cls->ShowWindow(SW_SHOW);
		break;
	case 3://��ѯ����ʾȫ����ʦ
		//��ʾ�ؼ�
		TextView_an->ShowWindow(SW_SHOW);
		ComboBox->ShowWindow(SW_SHOW);
		EditText_search->ShowWindow(SW_SHOW);
		Button_search->ShowWindow(SW_SHOW);
		Button_showAll->ShowWindow(SW_SHOW);
		List->ShowWindow(SW_SHOW);

		//���ؿؼ�
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
		ShowMB("��Ϣ������");
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
	if (mysql_query(mysql, "set names gbk"))//���ñ���
	{
		goto error;
	}
	sprintf(sql,
		"Insert into teacher_info(��ʦ��,����,�Ա�,ְ��,�ν̿γ�,�༶,�༶��Ŀ,���ۿ�ʱ,ʵ���ʱ,��ѧ������) values('%d','%s','%s','%s','%s','%s','%d','%d','%d','%d')",
		id, name, gender, title, course_name, class_name, class_count, theory_hour, experiment_hour, task_time);
	if (mysql_query(mysql, sql))
	{
		printf("����ʧ��,%s", mysql_error(mysql));
		goto error;
	}
	//cout << "��ӽ�ʦ�ɹ�" << endl;
	//::MessageBox(NULL, _T("��ӽ�ʦ�ɹ�"), _T("��Ϣ"), MB_OK);
	ShowMB("��ӽ�ʦ�ɹ�");
	goto exit;
error:
	//::MessageBox(NULL, _T("ִ�г���"), _T("��Ϣ"), MB_OK);
	ShowMB("ִ�г���");
	//cout << "ִ�г���:" << mysql_error(mysql);
exit:
	mysql_close(mysql);

}


void CMFC7Dlg::OnBnClickedButtoncls()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EditText_id_delete->SetWindowText("");
}


void CMFC7Dlg::OnBnClickedButtoniddelete()
{
	if (isDeleteEmpty())
	{
		ShowMB("�������ʦ��");
		return;
	}
	//�ж��Ƿ��иý�ʦid
	{
		CString str_id;
		EditText_id_delete->GetWindowText(str_id);
		int id = _ttoi(str_id);
		char sql[1024] = { 0 };
		sprintf(sql, "Select * from teacher_info where ��ʦ�� = %d", id);

		MYSQL *mysql = mysql_init(0);
		if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
		{
			//goto error;
		}
		printf("�������ݿ�ɹ���\n");
		if (mysql_query(mysql, "set names gbk"))
		{
			//goto error;
		}
		if (mysql_query(mysql, sql))
		{
			//goto error;
		}
		{
			//���߽���������ݷŵ��˿ͻ��ˣ�������С������ȽϺ���
			MYSQL_RES *result = mysql_store_result(mysql);
			//��ȡ��������,Ϊ0˵��û������
			int data = mysql_num_rows(result);
			if (data == 0)
			{
				ShowMB("û�иý�ʦ");
				return;
			}
			mysql_free_result(result);//�ͷű����ڴ��еĲ�ѯ���
			mysql_close(mysql);//����������ر����ӣ��������mysql���������ӹ��࿨���Ŀ�����
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
	if (mysql_query(mysql, "set names gbk"))//���ñ���
	{
		goto error;
	}
	sprintf(sql,
		"delete from teacher_info where ��ʦ�� = %d", id);
	if (mysql_query(mysql, sql))
	{
		printf("ɾ��ʧ��,%s", mysql_error(mysql));
		goto error;
	}
	ShowMB("ɾ����ʦ�ɹ�");
	goto exit;
error:
	ShowMB("ִ�г���");
exit:
	mysql_close(mysql);
	EditText_id_delete->SetWindowText("");
}

void CMFC7Dlg::ShowMB(char message[9])
{
	::MessageBox(NULL, _T(message), _T("��Ϣ"), MB_OK);
}

void CMFC7Dlg::OnCbnSelchangeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		ShowMB("�������ѯ��Ϣ");
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
		sprintf(sql, "Select * from teacher_info where ��ʦ�� = %d", _ttoi(searchInfo));
		break;
	case 1:
		sprintf(sql, "Select * from teacher_info where ���� = '%s'", c);
		break;
	case 2:
		sprintf(sql, "Select * from teacher_info where �Ա� = '%s'", c);
		break;
	case 3:
		sprintf(sql, "Select * from teacher_info where ְ�� = '%s'", c);
		break;
	case 4:
		sprintf(sql, "Select * from teacher_info where �ν̿γ� = '%s'", c);
		break;
	case 5:
		sprintf(sql, "Select * from teacher_info where �༶ like '%s%s%s'", "%", c, "%");
		break;
	case 6:
		sprintf(sql, "Select * from teacher_info where �༶��Ŀ = %d", _ttoi(searchInfo));
		break;
	case 7:
		sprintf(sql, "Select * from teacher_info where ���ۿ�ʱ = %d", _ttoi(searchInfo));
		break;
	case 8:
		sprintf(sql, "Select * from teacher_info where ʵ���ʱ = %d", _ttoi(searchInfo));
		break;
	case 9:
		sprintf(sql, "Select * from teacher_info where ��ѧ������ = %d", _ttoi(searchInfo));
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
	printf("�������ݿ�ɹ���\n");
	if (mysql_query(mysql, "set names gbk"))
	{
		goto error;
	}
	if (mysql_query(mysql, sql))
	{
		goto error;
	}
	{
		//���߽���������ݷŵ��˿ͻ��ˣ�������С������ȽϺ���
		MYSQL_RES *result = mysql_store_result(mysql);
		//ִ������mysql_store_result֮����ʵ�Ͽ����ݿ�����Ҳû��ϵ
		MYSQL_ROW row;
		//ֻҪ����������ôwhile��һֱִ��
		//mysql_fetch_row�ǡ���ͷ/�αꡱ�����ƶ�һ�У����һ����һ�����ݵ�MSQL_ROW����
		//���û�������򷵻�0
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

			List->InsertItem(i, _T(""));                          // ������
			List->SetItemText(i, 0, id);                     // ���õ�1��(����)
			List->SetItemText(i, 1, name);                      // ���õ�2��(����)  
			List->SetItemText(i, 2, gender);                      // ���õ�3��(�Ա�)
			List->SetItemText(i, 3, title);
			List->SetItemText(i, 4, course_name);
			List->SetItemText(i, 5, class_name);
			List->SetItemText(i, 6, class_count);
			List->SetItemText(i, 7, theory_hour);
			List->SetItemText(i, 8, experiment_hour);
			List->SetItemText(i, 9, task_time);

			i++;
		}
		mysql_free_result(result);//�ͷű����ڴ��еĲ�ѯ���
	}
	goto exit;
error:
	printf("ִ�г���%s", mysql_error(mysql));
exit:
	mysql_close(mysql);//����������ر����ӣ��������mysql���������ӹ��࿨���Ŀ�����
}


void CMFC7Dlg::OnBnClickedButtonsearchmod()
{
	if (isSearchIdModEmpty())
	{
		ShowMB("������Ҫ�޸ĵĽ�ʦ��");
		return;
	}

	CString str_id;
	EditText_id_mod->GetWindowText(str_id);
	int id = _ttoi(str_id);
	char sql[1024] = { 0 };
	sprintf(sql, "Select * from teacher_info where ��ʦ�� = %d", id);

	MYSQL *mysql = mysql_init(0);
	if (!mysql_real_connect(mysql, "localhost", "root", "root", "teacher_database", 0, 0, 0))//localhost
	{
		goto error;
	}
	printf("�������ݿ�ɹ���\n");
	if (mysql_query(mysql, "set names gbk"))
	{
		goto error;
	}
	if (mysql_query(mysql, sql))
	{
		goto error;
	}
	{
		//���߽���������ݷŵ��˿ͻ��ˣ�������С������ȽϺ���
		MYSQL_RES *result = mysql_store_result(mysql);
		//��ȡ��������,Ϊ0˵��û������
		int data = mysql_num_rows(result);
		if (data == 0)
		{
			ShowMB("û�иý�ʦ");
			return;
		}
		//ִ������mysql_store_result֮����ʵ�Ͽ����ݿ�����Ҳû��ϵ
		MYSQL_ROW row;
		//ֻҪ����������ôwhile��һֱִ��
		//mysql_fetch_row�ǡ���ͷ/�αꡱ�����ƶ�һ�У����һ����һ�����ݵ�MSQL_ROW����
		//���û�������򷵻�0
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

		mysql_free_result(result);//�ͷű����ڴ��еĲ�ѯ���

		goto exit;
	error:
		printf("ִ�г���%s", mysql_error(mysql));
	exit:
		mysql_close(mysql);//����������ر����ӣ��������mysql���������ӹ��࿨���Ŀ�����
	}
}


void CMFC7Dlg::OnBnClickedButtonmodconfirm()
{
	if (isAddUiEmpty())
	{
		ShowMB("��Ϣ������");
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
	if (mysql_query(mysql, "set names gbk"))//���ñ���
	{
		goto error;
	}
	sprintf(sql,
		"Update teacher_info set ��ʦ�� = %d,���� = '%s',�Ա� = '%s',ְ�� = '%s',�ν̿γ� = '%s',�༶ = '%s',�༶��Ŀ = %d,���ۿ�ʱ = %d,ʵ���ʱ = %d,��ѧ������ = %d where ��ʦ�� = %d",
		id, name, gender, title, course_name, class_name, class_count, theory_hour, experiment_hour, task_time, atoi(store_id));
	if (mysql_query(mysql, sql))
	{
		printf("����ʧ��,%s", mysql_error(mysql));
		goto error;
	}
	//cout << "��ӽ�ʦ�ɹ�" << endl;
	//::MessageBox(NULL, _T("��ӽ�ʦ�ɹ�"), _T("��Ϣ"), MB_OK);
	ShowMB("�޸Ľ�ʦ��Ϣ�ɹ�");
	goto exit;
error:
	//::MessageBox(NULL, _T("ִ�г���"), _T("��Ϣ"), MB_OK);
	ShowMB("ִ�г���");
	//cout << "ִ�г���:" << mysql_error(mysql);
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
		sprintf(sql, "%s order by ��ʦ�� %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 1:
		sprintf(sql, "%s order by ���� %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 2:
		sprintf(sql, "%s order by �Ա� %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 3:
		sprintf(sql, "%s order by ְ�� %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 4:
		sprintf(sql, "%s order by �ν̿γ� %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 5:
		sprintf(sql, "%s order by �༶ %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 6:
		sprintf(sql, "%s order by �༶��Ŀ %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 7:
		sprintf(sql, "%s order by ���ۿ�ʱ %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 8:
		sprintf(sql, "%s order by ʵ���ʱ %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	case 9:
		sprintf(sql, "%s order by ��ѧ������ %s", store_sql, sortFlag ? "ASC" : "DESC");
		break;
	}
	ExecuteSqlSelect(sql);
	sortFlag = sortFlag ? !sortFlag : !sortFlag;
	*pResult = 0;
}

void CMFC7Dlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMFC7Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here


	if (nType != SIZE_MINIMIZED) //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{


		ChangeSize(IDC_List, cx, cy); //��ÿһ���ؼ�����������
	
		GetClientRect(&m_rect); //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ�����


	}
}

void CMFC7Dlg::ChangeSize(UINT nID, int x, int y) //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{


	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{


		CRect rec;
		pWnd->GetWindowRect(&rec); //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec); //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x / m_rect.Width(); //���ձ��������ռ����λ��
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec); //�����ؼ�


	}
}