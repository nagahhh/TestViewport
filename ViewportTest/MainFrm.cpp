
// MainFrm.cpp : CMainFrame �N���X�̎���
//

#include "stdafx.h"
#include "ViewportTest.h"

#include "MainFrm.h"
#include "ViewportTestView.h"
#include "ViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_SHOWDLG, &CMainFrame::OnTestShowdlg)
	ON_COMMAND(ID_TEST_SHOWWND, &CMainFrame::OnTestShowwnd)
	ON_COMMAND(ID_TEST_SHOWWND2, &CMainFrame::OnTestShowwnd2)
	//ON_UPDATE_COMMAND_UI(ID_TEST_SHOWDLG, &CMainFrame::OnUpdateTestShowdlg)

	ON_MESSAGE(WM_VIEWDLGONOFF, OnViewDlgOnOff)
	ON_COMMAND(ID_TEST_SHOWDLG2, &CMainFrame::OnTestShowdlg2)
END_MESSAGE_MAP()

LRESULT CMainFrame::OnViewDlgOnOff(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	// Handle message here.

	CMenu* menu = GetMenu();
	CMenu* subMenu = menu->GetSubMenu(4);

	if (CViewDlg::isShown())
	{
		subMenu->CheckMenuItem(ID_TEST_SHOWDLG, MF_CHECKED | MF_BYCOMMAND);
	}
	else
	{
		subMenu->CheckMenuItem(ID_TEST_SHOWDLG, MF_UNCHECKED | MF_BYCOMMAND);
	}


	return 0;
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // �X�e�[�^�X ���C�� �C���W�P�[�^�[
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame �R���X�g���N�V����/�f�X�g���N�V����

CMainFrame::CMainFrame()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
	CViewDlg::addParent(this);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("�X�e�[�^�X �o�[�̍쐬�Ɏ��s���܂����B\n");
		return -1;      // �쐬�ł��Ȃ��ꍇ
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return TRUE;
}

// CMainFrame �f�f

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ���b�Z�[�W �n���h���[



void CMainFrame::OnTestShowdlg()
{
	CViewDlg::m_pDocS = GetActiveDocument();
	CViewDlg::toggleShowHide();
}


void CMainFrame::OnTestShowwnd()
{
	UINT nID = 1234;
	m_pFrameWnd = new CFrameWnd;
	LPCTSTR ClassName = (LPCTSTR)AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)COLOR_BACKGROUND + 1, NULL);

	DWORD dwStyle = WS_CAPTION | WS_VISIBLE;
	dwStyle |= WS_THICKFRAME;
	dwStyle |= WS_SYSMENU;

	m_pFrameWnd->CreateEx(0, ClassName, _T("Win"), dwStyle,
		0, 0, 580, 600, m_hWnd, (HMENU)NULL);

	RECT rect;
	m_pFrameWnd->GetClientRect(&rect);

	m_pView = new CViewportTestView;

	dwStyle = WS_CHILD;

	m_pView->Create(ClassName, _T("Win"), dwStyle,
		rect, m_pFrameWnd, nID);

	// �t���[���E�B���h�E�̍쐬���i�r���[�������w��j 
	CCreateContext context; 
	context.m_pNewViewClass = RUNTIME_CLASS(CViewportTestView);


	// �t���[���E�B���h�E�`�r���[�쐬  
	dwStyle = WS_CAPTION | WS_VISIBLE;
	dwStyle |= WS_THICKFRAME;
	dwStyle |= WS_SYSMENU;
	CFrameWnd* viewFrame_ = static_cast< CFrameWnd* >(RUNTIME_CLASS(CFrameWnd)->CreateObject());
	viewFrame_->Create(NULL, NULL, dwStyle, rect, this, NULL, 0, &context);
}


void CMainFrame::OnTestShowwnd2()
{
	CCreateContext contextT;
	contextT.m_pCurrentDoc = GetActiveDocument();
	contextT.m_pNewDocTemplate = contextT.m_pCurrentDoc->GetDocTemplate();
	contextT.m_pNewViewClass = RUNTIME_CLASS(CViewportTestView);
	CWnd* wndRT = dynamic_cast<CWnd*>(contextT.m_pNewViewClass->CreateObject());

	//CViewportTestView* wndRT = new CViewportTestView();

	DWORD dwStyle = WS_CAPTION | WS_VISIBLE;
	dwStyle |= WS_THICKFRAME;
	dwStyle |= WS_SYSMENU;

	LPCTSTR ClassName = (LPCTSTR)AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)COLOR_BACKGROUND + 1, NULL);
	wndRT->CreateEx(WS_EX_WINDOWEDGE, ClassName, _T("Win"), dwStyle,
		0, 0, 580, 100, m_hWnd, (HMENU)NULL);
}


//void CMainFrame::OnUpdateTestShowdlg(CCmdUI *pCmdUI)
//{
//	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
//	CViewDlg* pViewDlg = CViewDlg::getInstance();
//	pViewDlg->ShowWindow(SW_SHOW);
//}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1L)
	{
		AfxMessageBox(_T("TEST2"));
		return TRUE;
	}

	return CFrameWnd::OnCommand(wParam, lParam);
}


void CMainFrame::OnTestShowdlg2()
{
	dlg2_.Create(Dialog2::IDD, this);
	dlg2_.ShowWindow(SW_SHOW);
}
