
// MFC7Dlg.h : ͷ�ļ�
//

#pragma once


// CMFC7Dlg �Ի���
class CMFC7Dlg : public CDialogEx
{
// ����
public:
	CMFC7Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtoncls();
	afx_msg void OnBnClickedButtoniddelete();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnBnClickedButtonidcls();
	afx_msg void OnBnClickedButtonsearchmod();
	afx_msg void OnBnClickedButtonmodconfirm();
	afx_msg void OnBnClickedButtonmodcancel();
	afx_msg void OnBnClickedButtonshowall();

	void SetInputOnlyNumber(CEdit *c);
	void ShowMB(char message[9]);
	void ExecuteSqlSelect(char *sql);

	bool isAddUiEmpty();
	bool isSearchIdModEmpty();
	bool isDeleteEmpty();
	bool isSearchEmpty();

	afx_msg void OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(UINT nID, int x, int y);
//	POINT old;
};
