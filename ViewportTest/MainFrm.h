
// MainFrm.h : CMainFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "ViewportTestView.h"
#include "MainFrm.h"
#include "Dialog2.h"

class CViewportTestView;

class CMainFrame : public CFrameWnd
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	CFrameWnd* m_pFrameWnd;
	CViewportTestView* m_pView;

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // �R���g���[�� �o�[�p�����o�[
	CStatusBar        m_wndStatusBar;

	Dialog2 dlg2_;

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTestShowdlg();
	afx_msg void OnTestShowwnd();
	afx_msg void OnTestShowwnd2();
//	afx_msg void OnUpdateTestShowdlg(CCmdUI *pCmdUI);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnViewDlgOnOff(WPARAM wParam, LPARAM lParam);

	afx_msg void OnTestShowdlg2();
};


