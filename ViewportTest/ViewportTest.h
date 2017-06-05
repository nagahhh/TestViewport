
// ViewportTest.h : ViewportTest アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CViewportTestApp:
// このクラスの実装については、ViewportTest.cpp を参照してください。
//

class CViewportTestApp : public CWinAppEx
{
public:
	CViewportTestApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CViewportTestApp theApp;
