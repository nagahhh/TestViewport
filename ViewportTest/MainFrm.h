
// MainFrm.h : CMainFrame クラスのインターフェイス
//

#pragma once

#include "ViewportTestView.h"
#include "MainFrm.h"
#include "Dialog2.h"

class CViewportTestView;

class CMainFrame : public CFrameWnd
{
protected: // シリアル化からのみ作成します。
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	CFrameWnd* m_pFrameWnd;
	CViewportTestView* m_pView;

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // コントロール バー用メンバー
	CStatusBar        m_wndStatusBar;

	Dialog2 dlg2_;

// 生成された、メッセージ割り当て関数
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


