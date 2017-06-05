// OudanDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ViewportTest.h"
#include "OudanDlg.h"
#include "afxdialogex.h"


// OudanDlg ダイアログ

OudanDlg* OudanDlg::pOudanDlg_ = nullptr;
std::set<CWnd*> OudanDlg::vObsevers_;
CWnd* OudanDlg::pParent_ = nullptr;

void OudanDlg::toggleShowHide()
{
	if (!pOudanDlg_)
	{
		pOudanDlg_ = new OudanDlg();
		pOudanDlg_->Create(OudanDlg::IDD, pParent_);
		pOudanDlg_->ShowWindow(SW_SHOW);

		// メニュー、ツールバーのチェックを切り替える
		for (auto p : vObsevers_)
		{
			p->SendMessage(WM_VIEWDLGONOFF, 0, 0);
		}
	}
	else
	{
		pOudanDlg_->DestroyWindow();
	}

}

void OudanDlg::addObsever(CWnd* pObserver)
{
	vObsevers_.insert(pObserver);
}

void OudanDlg::removeObsever(CWnd* pObserver)
{
	vObsevers_.erase(pObserver);
}

bool OudanDlg::isShown()
{
	return pOudanDlg_ ? true : false;
}

void OudanDlg::setParent(CWnd* pParetn)
{
	pParent_ = pParetn;
}

void OudanDlg::PostNcDestroy()
{
	delete this;
	pOudanDlg_ = nullptr;

	for (auto p : vObsevers_)
	{
		if (p->GetSafeHwnd())
			p->SendMessage(WM_VIEWDLGONOFF, 0, 0);
	}
	
	CDialog::PostNcDestroy();
}


IMPLEMENT_DYNAMIC(OudanDlg, CDialog)

OudanDlg::OudanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(OudanDlg::IDD, pParent)
{

}

OudanDlg::~OudanDlg()
{
}

void OudanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OudanDlg, CDialog)
END_MESSAGE_MAP()


// OudanDlg メッセージ ハンドラー



void OudanDlg::OnCancel()
{
	DestroyWindow();
}
