// Dialog2.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ViewportTest.h"
#include "Dialog2.h"
#include "afxdialogex.h"


// Dialog2 �_�C�A���O

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


// Dialog2 ���b�Z�[�W �n���h���[



void Dialog2::PostNcDestroy()
{
	//// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊��N���X���Ăяo���Ă��������B

	//CDialog::PostNcDestroy();

	delete this;
}


void Dialog2::OnOK()
{
	DestroyWindow();
}
