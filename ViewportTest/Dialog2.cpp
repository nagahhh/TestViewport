// Dialog2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ViewportTest.h"
#include "Dialog2.h"
#include "afxdialogex.h"


// Dialog2 ダイアログ

IMPLEMENT_DYNAMIC(Dialog2, CDialog)

Dialog2::Dialog2(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog2::IDD, pParent)
{

}

Dialog2::~Dialog2()
{
}

void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog2, CDialog)
END_MESSAGE_MAP()


// Dialog2 メッセージ ハンドラー



void Dialog2::PostNcDestroy()
{
	//// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	//CDialog::PostNcDestroy();

	delete this;
}


void Dialog2::OnOK()
{
	DestroyWindow();
}
