// SpinCtrlDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ViewportTest.h"
#include "SpinCtrlDlg.h"
#include "afxdialogex.h"


// SpinCtrlDlg ダイアログ

//IMPLEMENT_DYNAMIC(SpinCtrlDlg, CDialog)
// IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL, NULL)
// #define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, class_init)
CRuntimeClass* PASCAL SpinCtrlDlg::_GetBaseClass()
{
	//return RUNTIME_CLASS(CDialog);
	return CDialog::GetThisClass();
}
AFX_COMDAT const CRuntimeClass SpinCtrlDlg::classSpinCtrlDlg = 
{
	"class_name", 
	sizeof(class SpinCtrlDlg), 
	0xFFFF, 
	NULL,
	&SpinCtrlDlg::_GetBaseClass, 
	NULL, 
	NULL
};

CRuntimeClass* PASCAL SpinCtrlDlg::GetThisClass()
{
	//return _RUNTIME_CLASS(SpinCtrlDlg);
	return (CRuntimeClass*)(&SpinCtrlDlg::classSpinCtrlDlg);
}

CRuntimeClass* SpinCtrlDlg::GetRuntimeClass() const
{
	//return _RUNTIME_CLASS(SpinCtrlDlg);
	return (CRuntimeClass*)(&SpinCtrlDlg::classSpinCtrlDlg);
}


SpinCtrlDlg::SpinCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SpinCtrlDlg::IDD, pParent)
{

}

SpinCtrlDlg::~SpinCtrlDlg()
{
}

void SpinCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_spinButtonCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_edSpin);
	DDX_Text(pDX, IDC_EDIT1, m_nSpin);
	DDV_MinMaxInt(pDX, m_nSpin, 0, 6);
}


BEGIN_MESSAGE_MAP(SpinCtrlDlg, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &SpinCtrlDlg::OnDeltaposSpin1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &SpinCtrlDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// SpinCtrlDlg メッセージ ハンドラー




void SpinCtrlDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	pNMUpDown->iDelta = -pNMUpDown->iDelta;

	*pResult = 0;
}


BOOL SpinCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_spinButtonCtrl.SetRange32(6, 0);
	m_spinButtonCtrl.SetPos32(4);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}





void SpinCtrlDlg::OnEnKillfocusEdit1()
{
	int iPos = m_spinButtonCtrl.GetPos32();
	m_spinButtonCtrl.SetPos32(iPos);
}
