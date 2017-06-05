#pragma once

#include "ViewportTestView.h"
#include <set>

#define WM_VIEWDLGONOFF (WM_USER + 100)


// CViewDlg ダイアログ

class CViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewDlg)

public:
	static CViewDlg* pViewDlg_;
	
	CFrameWnd* m_pFrameWnd = nullptr;
	CViewportTestView* m_pView = nullptr;

	CDocument* m_pDoc = nullptr;
	static CDocument* m_pDocS;

	static std::set<CWnd*> vParents_;

	static void toggleShowHide();
	static void addParent(CWnd* pParent);
	static bool isShown();

	//CToolBar m_wndToolBar;
	CMFCToolBar m_wndToolBar;
	CComboBox m_comboBox;
	CRect m_rectToolBar;


public:
	CViewDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CViewDlg();


	void setDocument(CDocument* pDoc)
	{
		m_pDoc = pDoc;
	}


// ダイアログ データ
	enum { IDD = IDD_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuItem1();
	virtual void PostNcDestroy();
	virtual void OnCancel();

	afx_msg LRESULT OnOudanDlgOnOff(WPARAM wParam, LPARAM lParam);

};
