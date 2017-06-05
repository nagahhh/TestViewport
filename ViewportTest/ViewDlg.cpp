// ViewDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ViewportTest.h"
#include "ViewDlg.h"
#include "afxdialogex.h"

#include "ViewportTestView.h"

#include "OudanDlg.h"

// CViewDlg ダイアログ

IMPLEMENT_DYNAMIC(CViewDlg, CDialog)

CViewDlg* CViewDlg::pViewDlg_ = nullptr;
std::set<CWnd*> CViewDlg::vParents_;
CDocument* CViewDlg::m_pDocS = nullptr;


void CViewDlg::toggleShowHide()
{
	if (!pViewDlg_)
	{
		pViewDlg_ = new CViewDlg();
		pViewDlg_->Create(CViewDlg::IDD);
		pViewDlg_->ShowWindow(SW_SHOW);

		for (auto p : vParents_)
		{
			p->SendMessage(WM_VIEWDLGONOFF, 0, 0);
		}
		
		//CRect rect;
		//pViewDlg_->m_pView->GetClientRect(rect);
		//
		//pViewDlg_->m_pView->ClientToScreen(rect);

		//CPoint pt = rect.CenterPoint();

		//pViewDlg_->m_pView->PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
		////pViewDlg_->m_pView->m_wndToolBar.Invalidate();
		//pViewDlg_->m_pView->m_wndToolBar.EnableWindow();
		
	}
	else
	{
		pViewDlg_->DestroyWindow();
	}

}

void CViewDlg::addParent(CWnd* pParent)
{
	vParents_.insert(pParent);
}

bool CViewDlg::isShown()
{
	return pViewDlg_ ? true : false;
}

void CViewDlg::PostNcDestroy()
{
	delete this;
	pViewDlg_ = nullptr;

	for (auto p : vParents_)
	{
		p->SendMessage(WM_VIEWDLGONOFF, 0, 0);
	}

	CDialog::PostNcDestroy();
}

void CViewDlg::OnCancel()
{
	DestroyWindow();
}

CViewDlg::CViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewDlg::IDD, pParent)
{
	OudanDlg::addObsever(this);
	OudanDlg::setParent(this);
}

CViewDlg::~CViewDlg()
{
	OudanDlg::removeObsever(this);
	OudanDlg::setParent(nullptr);
}

void CViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CViewDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_ITEM_1, &CViewDlg::OnMenuItem1)

	ON_MESSAGE(WM_VIEWDLGONOFF, OnOudanDlgOnOff)
END_MESSAGE_MAP()


// CViewDlg メッセージ ハンドラー

LRESULT CViewDlg::OnOudanDlgOnOff(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	// メニュー
	CMenu* menu = GetMenu();

	if (OudanDlg::isShown())
	{
		menu->CheckMenuItem(ID_MENU_ITEM_1, MF_CHECKED | MF_BYCOMMAND);
	}
	else
	{
		menu->CheckMenuItem(ID_MENU_ITEM_1, MF_UNCHECKED | MF_BYCOMMAND);
	}

	// ツールバー
	CToolBarCtrl& toolBarCtrl = m_pView->m_wndToolBar.GetToolBarCtrl();
	toolBarCtrl.CheckButton(IDTB_BUTTON_3, OudanDlg::isShown());

	return 0;
}


BOOL CViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//CViewportTestView* m_pView = new CViewportTestView();
	
	CRect rect; 
	GetClientRect(&rect); 
	rect.top += 35;

	// フレームウィンドウの作成情報（ビューだけを指定） 
	CCreateContext context; 
	context.m_pNewViewClass = RUNTIME_CLASS(CViewportTestView);
	//context.m_pCurrentDoc = m_pDoc;
	context.m_pCurrentDoc = m_pDocS;


	// フレームウィンドウ～ビュー作成  
	m_pFrameWnd = static_cast< CFrameWnd* >(RUNTIME_CLASS(CFrameWnd)->CreateObject());
	m_pFrameWnd->Create(NULL, NULL, WS_VISIBLE | WS_CHILD, rect, this, NULL, 0, &context);
	
	//m_pView = (CViewportTestView*)m_pFrameWnd->GetActiveView();

	POSITION pos = m_pDocS->GetFirstViewPosition();
	CViewportTestView* pView1 = (CViewportTestView*)m_pDocS->GetNextView(pos);
	CViewportTestView* pView2 = (CViewportTestView*)m_pDocS->GetNextView(pos);

	m_pView = pView2;

	OnOudanDlgOnOff(0, 0);



	m_wndToolBar.Create(this);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR1);

	HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FONT);
	LOGFONT lf;
	::GetObject(hFont, sizeof(LOGFONT), &lf);

	//lstrcpy(lf.lfFaceName, _T("MS ゴシック"));
	lf.lfHeight = 5;
	lf.lfWidth = 0;

	CFont font;
	font.CreateFontIndirectW(&lf);

	m_wndToolBar.SetFont(&font);

	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);


	m_wndToolBar.ShowWindow(SW_SHOW);

	m_wndToolBar.SetButtonInfo(1, IDM_COMBO, TBBS_SEPARATOR, 150);

	CRect rectCombo;

	//３番目のITEMの領域で、Comboを作成
	m_wndToolBar.GetItemRect(1, &rectCombo);
	rectCombo.left += 3;
	rectCombo.right -= 3;
	rectCombo.bottom -= 3;
	//rectCombo.bottom = rectCombo.top + 100;

	if (!m_comboBox.Create(
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		rectCombo, &m_wndToolBar, IDM_COMBO))
	{
		TRACE0("Failed to create combobox ...\n");
		return FALSE;
	}

	int x = ::GetSystemMetrics(SM_CXMAXIMIZED);
	//	CSize size;
	//	m_wndToolBar.GetToolBarCtrl().GetMaxSize(&size);
	int y = m_comboBox.GetItemHeight(-1);

	m_rectToolBar.right = x;
	m_rectToolBar.bottom = 35;
	m_wndToolBar.MoveWindow(m_rectToolBar);


	//	m_comboBox.SetFont(m_wndToolBar.GetFont());
	//	m_comboBox.SetFont(&font);


	//COMBOにデータを設定。
	m_comboBox.AddString(_T("This"));
	m_comboBox.AddString(_T("is"));
	m_comboBox.AddString(_T("a"));
	m_comboBox.AddString(_T("test"));
	m_comboBox.AddString(_T("program"));
	m_comboBox.SetCurSel(0);


	m_wndToolBar.SetButtonStyle(4, TBBS_CHECKBOX);	return TRUE;
}


void CViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pFrameWnd)
	{
		CRect rect;
		GetClientRect(&rect);
		rect.top += 35;
		m_pFrameWnd->MoveWindow(rect);
	}
}


void CViewDlg::OnMenuItem1()
{
	OudanDlg::toggleShowHide();
}


