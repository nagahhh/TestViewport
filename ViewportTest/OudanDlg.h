#pragma once

#include <set>

#define WM_VIEWDLGONOFF (WM_USER + 100)

// OudanDlg ダイアログ

class OudanDlg : public CDialog
{
	DECLARE_DYNAMIC(OudanDlg)

	static OudanDlg* pOudanDlg_;
	static std::set<CWnd*> vObsevers_;
	static CWnd* pParent_;

public:
	static void toggleShowHide();
	static void addObsever(CWnd* pObserver);
	static void removeObsever(CWnd* pObserver);
	static bool isShown();
	static void setParent(CWnd* pParent);

public:
	OudanDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~OudanDlg();

// ダイアログ データ
	enum { IDD = IDD_OUDAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	virtual void PostNcDestroy();

	virtual void OnCancel();
};
