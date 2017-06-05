#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// SpinCtrlDlg ダイアログ

class SpinCtrlDlg : public CDialog
{
	
//DECLARE_DYNAMIC(SpinCtrlDlg)
//#define DECLARE_DYNAMIC(class_name)
protected:
	static CRuntimeClass* PASCAL _GetBaseClass();

public:
	static const CRuntimeClass classSpinCtrlDlg;
	static CRuntimeClass* PASCAL GetThisClass();
	virtual CRuntimeClass* GetRuntimeClass() const;


public:
	SpinCtrlDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~SpinCtrlDlg();

// ダイアログ データ
	enum { IDD = IDD_SPINCTRLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CSpinButtonCtrl m_spinButtonCtrl;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edSpin;
	int m_nSpin;
	int m_iDelta;
	int m_iPos;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEdit1();
};
