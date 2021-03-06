
// ViewportTest.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ViewportTest.h"
#include "MainFrm.h"

#include "ViewportTestDoc.h"
//#include "ViewportTestView.h"
#include "ViewportTestViewMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CViewportTestApp

BEGIN_MESSAGE_MAP(CViewportTestApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CViewportTestApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CViewportTestApp コンストラクション

CViewportTestApp::CViewportTestApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// アプリケーションが共通言語ランタイム サポート (/clr) を使用して作成されている場合:
	//     1) この追加設定は、再起動マネージャー サポートが正常に機能するために必要です。
	//     2) 作成するには、プロジェクトに System.Windows.Forms への参照を追加する必要があります。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 下のアプリケーション ID 文字列を一意の ID 文字列で置換します。推奨される
	// 文字列の形式は CompanyName.ProductName.SubProduct.VersionInformation です
	SetAppID(_T("ViewportTest.AppID.NoVersion"));

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

// 唯一の CViewportTestApp オブジェクトです。

CViewportTestApp theApp;


// CViewportTestApp 初期化

BOOL CViewportTestApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit コントロールを使用するには AfxInitRichEdit2() が必要です	
	// AfxInitRichEdit2();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(4);  // 標準の INI ファイルのオプションをロードします (MRU を含む)

	
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);



	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;

	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CViewportTestDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		//RUNTIME_CLASS(CViewportTestView));
		RUNTIME_CLASS(CViewportTestViewMain));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CViewportTestApp::ExitInstance()
{
	//TODO: 追加したリソースがある場合にはそれらも処理してください
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CViewportTestApp メッセージ ハンドラー


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnIdtbButton0();
//	afx_msg void OnIdtbButton1();
//	afx_msg void OnCombo();
//	afx_msg void OnIdtbButton2();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
//	virtual BOOL DestroyWindow();
//	virtual void PostNcDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDTB_BUTTON_0, &CAboutDlg::OnIdtbButton0)
//	ON_COMMAND(IDTB_BUTTON_1, &CAboutDlg::OnIdtbButton1)
//	ON_COMMAND(IDM_COMBO, &CAboutDlg::OnCombo)
//ON_COMMAND(IDTB_BUTTON_2, &CAboutDlg::OnIdtbButton2)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CViewportTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CViewportTestApp メッセージ ハンドラー





//void CAboutDlg::OnIdtbButton0()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//}


//void CAboutDlg::OnIdtbButton1()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//}


//void CAboutDlg::OnCombo()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//}


//void CAboutDlg::OnIdtbButton2()
//{
//	PostMessage(WM_COMMAND, 1L, 2L);
//}


BOOL CAboutDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	return CDialogEx::OnCommand(wParam, lParam);
}


//BOOL CAboutDlg::DestroyWindow()
//{
//	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
//
//	return CDialogEx::DestroyWindow();
//}


//void CAboutDlg::PostNcDestroy()
//{
//	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
//
//	//CDialogEx::PostNcDestroy();
//
//	//delete this;
//}
