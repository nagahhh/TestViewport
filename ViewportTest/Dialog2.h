#pragma once


// Dialog2 �_�C�A���O

class Dialog2 : public CDialog
{
	DECLARE_DYNAMIC(Dialog2)

public:
	Dialog2(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~Dialog2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
};
