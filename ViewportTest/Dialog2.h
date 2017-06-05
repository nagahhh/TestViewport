#pragma once


// Dialog2 ダイアログ

class Dialog2 : public CDialog
{
	DECLARE_DYNAMIC(Dialog2)

public:
	Dialog2(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~Dialog2();

// ダイアログ データ
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
};
