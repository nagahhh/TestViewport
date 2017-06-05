
// ViewportTestView.cpp : CViewportTestView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ViewportTest.h"
#endif

#include "ViewportTestDoc.h"
#include "ViewportTestView.h"

#include "resource.h"

#include <vector>
#include <algorithm>

#include "OudanDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CViewportTestView

IMPLEMENT_DYNCREATE(CViewportTestView, CView)

BEGIN_MESSAGE_MAP(CViewportTestView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(IDTB_BUTTON_0, &CViewportTestView::OnIdtbButton0)
	ON_COMMAND(IDTB_BUTTON_1, &CViewportTestView::OnIdtbButton1)
	ON_COMMAND(IDTB_BUTTON_2, &CViewportTestView::OnIdtbButton2)
	ON_COMMAND(IDTB_BUTTON_3, &CViewportTestView::OnIdtbButton3)
	ON_COMMAND(IDM_COMBO, &CViewportTestView::OnCombo)
	ON_CBN_EDITCHANGE(IDM_COMBO, &CViewportTestView::OnCombo)
	ON_CBN_SELCHANGE(IDM_COMBO, &CViewportTestView::OnCombo)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CViewportTestView コンストラクション/デストラクション

CViewportTestView::CViewportTestView()
{
	// magnification
	m_mag = 1.0;
	m_magOld = 1.0;
	m_magY = 1.0;
	m_magStep = 0.5;

	m_ptOrg.SetPoint(INT_MIN, INT_MIN);
	m_ptOld.SetPoint(INT_MIN, INT_MIN);

	m_vPointData.push_back(CPoint(-100, -100));
	m_vPointData.push_back(CPoint(100, 100));

	m_sizeWindowExt.SetSize(100000, 100000);
	m_sizeViewportExt.SetSize(100, -100);

	m_pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
	m_brushHollow.CreateStockObject(HOLLOW_BRUSH);


	RV1Event[RV1EventID::EVENT0] = &CViewportTestView::onEvent0;
	RV1Event[RV1EventID::EVENT1] = &CViewportTestView::onEvent1;
	RV1Event[RV1EventID::EVENT2] = &CViewportTestView::onEvent2;
	RV1Event[RV1EventID::EVENT3] = &CViewportTestView::onEvent3;
}

CViewportTestView::~CViewportTestView()
{
	OudanDlg::removeObsever(this);
}

//BOOL CViewportTestView::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
//	//  修正してください。
//
//	//return CView::PreCreateWindow(cs);
//}


// CViewportTestView 描画

void CViewportTestView::OnDraw(CDC* pDC)
{
	CViewportTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	initRect();

	beginDrawing(pDC);

	//drawRgn(pDC);
	//drawRgn2(pDC);


	drawGrid(pDC);
	drawFrame(pDC);
	drawSample(pDC);
	
	drawCurvatureFrame(pDC);
	drawCurvatureHeader(pDC);
	drawCurvatureLine(pDC);


	endDrawing(pDC);

	CRect rect = m_rectClient;
	rect.bottom = 40;
	//m_wndToolBar.MoveWindow(rect);

}

void CViewportTestView::initRect()
{
	GetClientRect(&m_rectClient);

	m_rectFrame = m_rectClient;
	m_rectFrame.top += 35;
	m_rectFrame.left += 100;
	m_rectFrame.bottom -= 150;


	m_ptFrameCenter.x = (m_rectFrame.left + m_rectFrame.right) / 2;
	m_ptFrameCenter.y = (m_rectFrame.top + m_rectFrame.bottom) / 2;

	if (m_ptOrg.x == INT_MIN)
	{
		m_ptOrg.x = m_rectFrame.left + 20;
		m_ptOrg.y = m_rectFrame.bottom - 20;

		m_ptOld = m_ptOrg;

		m_ptCenterOld = m_ptFrameCenter;
	}

	m_rectCurvature.left = m_rectFrame.left;
	m_rectCurvature.top = m_rectFrame.bottom + 20;
	m_rectCurvature.right = m_rectFrame.right;
	m_rectCurvature.bottom = m_rectClient.bottom - 5;
	
}

void CViewportTestView::drawGrid(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, RGB(200, 200, 200));
	pDC->SelectObject(pen);

	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetWindowExt(m_sizeWindowExt);

	CSize sizeExt;
	sizeExt.cx = m_sizeViewportExt.cx * m_mag;
	sizeExt.cy = m_sizeViewportExt.cy * m_mag * m_magY;

	pDC->SetViewportExt(sizeExt);

	pDC->SetWindowOrg(0, 0);		// 論理座標系の基準点（ビューポートの基準点と重なる点）
	pDC->SetViewportOrg(m_ptOrg);	// ビューポートの基準点


	CRgn rgn;
	rgn.CreateRectRgnIndirect(m_rectFrame);
	pDC->SelectClipRgn(&rgn);

	CRect rectFrameLP = m_rectFrame;
	pDC->DPtoLP(rectFrameLP);

	CRect rectGrid;
	rectGrid = rectFrameLP;

	rectGrid.top += 10000 * 0.9;
	rectGrid.top /= 10000;
	rectGrid.top *= 10000;

	rectGrid.bottom /= 10000;
	rectGrid.bottom *= 10000;

	rectGrid.left /= 10000;
	rectGrid.left *= 10000;

	rectGrid.right += 10000 * 0.9;
	rectGrid.right /= 10000;
	rectGrid.right *= 10000;


	for (int x = rectGrid.left; x < rectGrid.right; x += 10000)
	{
		pDC->MoveTo(x, rectFrameLP.top);
		pDC->LineTo(x, rectFrameLP.bottom);
	}

	for (int y = rectGrid.bottom; y < rectGrid.top; y += 10000)
	{
		pDC->MoveTo(rectFrameLP.left, y);
		pDC->LineTo(rectFrameLP.right, y);
	}

}


void CViewportTestView::drawCurvatureLine(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, RGB(0, 0, 255));
	pDC->SelectObject(pen);

	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetWindowExt(m_sizeWindowExt);

	int H = (m_rectCurvature.bottom - m_rectCurvature.top) / 2.0;
	int y = (m_rectCurvature.bottom + m_rectCurvature.top) / 2.0;

	CSize sizeExt;
	sizeExt.cx = m_sizeViewportExt.cx * m_mag;
	sizeExt.cy = m_sizeViewportExt.cy * m_mag * m_magY;

	pDC->SetViewportExt(sizeExt.cx, -(H - 10));
	pDC->SetViewportOrg(m_ptOrg.x, y);	// ビューポートの基準点

	pDC->SetWindowExt(m_sizeWindowExt.cx, 150000);
	pDC->SetWindowOrg(0, 0);


	CRgn rgn;
	rgn.CreateRectRgnIndirect(m_rectCurvature);
	pDC->SelectClipRgn(&rgn);


	pDC->MoveTo(0, 0);
	pDC->LineTo(100000, 0);
	pDC->LineTo(200000, 150000);
	pDC->LineTo(300000, 150000);
	pDC->LineTo(400000, 0);
	pDC->LineTo(500000, 0);
	pDC->LineTo(600000, -150000);
	pDC->LineTo(700000, -150000);

}

void CViewportTestView::drawCurvatureHeader(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, RGB(0, 0, 255));
	pDC->SelectObject(pen);

	pDC->SetMapMode(MM_TEXT);

	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportOrg(0, 0);

	pDC->SelectClipRgn(NULL);

	CRect rectHeader;

	rectHeader.left = 5;
	rectHeader.top = m_rectCurvature.top;
	rectHeader.right = m_rectCurvature.left;
	rectHeader.bottom = m_rectCurvature.bottom;

	pDC->MoveTo(rectHeader.right, rectHeader.top);
	pDC->LineTo(rectHeader.left, rectHeader.top);
	pDC->LineTo(rectHeader.left, rectHeader.bottom);
	pDC->LineTo(rectHeader.right, rectHeader.bottom);

	CPoint ptTitle;
	ptTitle.x = (rectHeader.right + rectHeader.left) / 2;
	ptTitle.y = (rectHeader.top + rectHeader.bottom) / 2 - 5;

	pDC->SetTextAlign(TA_CENTER);
	pDC->SetTextColor(RGB(0, 0, 255));

	CString strTitle = _T("曲率");

	pDC->TextOutW(ptTitle.x, ptTitle.y, strTitle);
}

void CViewportTestView::drawCurvatureFrame(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, RGB(0, 0, 255));
	pDC->SelectObject(pen);

	pDC->SetMapMode(MM_TEXT);

	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportOrg(0, 0);

	pDC->SelectClipRgn(NULL);


	pDC->MoveTo(m_rectCurvature.right, m_rectCurvature.top);
	pDC->LineTo(m_rectCurvature.left, m_rectCurvature.top);
	pDC->LineTo(m_rectCurvature.left, m_rectCurvature.bottom);
	pDC->LineTo(m_rectCurvature.right, m_rectCurvature.bottom);

	pDC->MoveTo(m_rectCurvature.right, m_rectCurvature.top);
	pDC->LineTo(m_rectCurvature.left, m_rectCurvature.top);
	pDC->LineTo(m_rectCurvature.left, m_rectCurvature.bottom);
	pDC->LineTo(m_rectCurvature.right, m_rectCurvature.bottom);
}

void CViewportTestView::drawRgn2(CDC* pDC)
{
	CRgn   rgnA, rgnB;
	CRgn   rgnC;

	CPoint ptVertexA[5];

	ptVertexA[0].x = 0;
	ptVertexA[0].y = 0;
	ptVertexA[1].x = 100;
	ptVertexA[1].y = 50;
	ptVertexA[2].x = 0;
	ptVertexA[2].y = 100;

	CPoint ptVertexB[5];

	ptVertexB[0].x = 100;
	ptVertexB[0].y = 0;
	ptVertexB[1].x = 0;
	ptVertexB[1].y = 50;
	ptVertexB[2].x = 100;
	ptVertexB[2].y = 100;

	VERIFY(rgnA.CreatePolygonRgn(ptVertexA, 3, ALTERNATE));
	VERIFY(rgnB.CreatePolygonRgn(ptVertexB, 3, ALTERNATE));
	VERIFY(rgnC.CreateRectRgn(0, 0, 50, 50));


	int nCombineResult = rgnC.CombineRgn(&rgnA, &rgnB, RGN_OR);
	ASSERT(nCombineResult != ERROR && nCombineResult != NULLREGION);

	CBrush br1, br2, br3;
	VERIFY(br1.CreateSolidBrush(RGB(255, 0, 0)));  // rgnA Red
	VERIFY(pDC->FrameRgn(&rgnA, &br1, 2, 2));
	
	VERIFY(br2.CreateSolidBrush(RGB(0, 255, 0)));  // rgnB Green
	VERIFY(pDC->FrameRgn(&rgnB, &br2, 2, 2));
	
	pDC->SetViewportOrg(100, 100);

	VERIFY(br3.CreateSolidBrush(RGB(0, 0, 255)));  // rgnC Blue
	VERIFY(pDC->FrameRgn(&rgnC, &br3, 1, 1));

	RGNDATA data[10];
	rgnC.GetRegionData(data, 10);

	int size = rgnC.GetRegionData(NULL, 0);
	
	if (size)
	{
		LPRGNDATA pRgnData = new RGNDATA[size];

		rgnC.GetRegionData(pRgnData, size);

		RGNDATA data;
		RGNDATAHEADER   rdh;
		for (int i = 0; i < size; i++)
		{
			rdh = pRgnData[i].rdh;
			CRect r = rdh.rcBound;
			int mag = 5;
			r.left *= mag;
			r.top *= mag;
			r.right *= mag;
			r.bottom *= mag;

			pDC->FrameRect(&r, &br3);
		}

		delete[] pRgnData;
	}

}

void CViewportTestView::drawRgn(CDC* pDC)
{
	CRgn   rgnA, rgnB;

	CPoint ptVertex[5];

	ptVertex[0].x = 180;
	ptVertex[0].y = 80;
	ptVertex[1].x = 100;
	ptVertex[1].y = 160;
	ptVertex[2].x = 120;
	ptVertex[2].y = 260;
	ptVertex[3].x = 240;
	ptVertex[3].y = 260;
	ptVertex[4].x = 260;
	ptVertex[4].y = 160;

	VERIFY(rgnA.CreatePolygonRgn(ptVertex, 5, ALTERNATE));

	CRect rectRgnBox;
	int nRgnBoxResult = rgnA.GetRgnBox(&rectRgnBox);
	ASSERT(nRgnBoxResult != ERROR && nRgnBoxResult != NULLREGION);

	CBrush brA, brB;
	VERIFY(brA.CreateSolidBrush(RGB(255, 0, 0)));  // rgnA Red
	VERIFY(pDC->FrameRgn(&rgnA, &brA, 2, 2));
	VERIFY(brB.CreateSolidBrush(RGB(0, 0, 255)));  // Blue
	rectRgnBox.InflateRect(3, 3);
	pDC->FrameRect(&rectRgnBox, &brB);
}

void CViewportTestView::beginDrawing(CDC* pDC)
{
	m_penOld = pDC->SelectObject(&m_pen1);
	m_brushOld = pDC->SelectObject(&m_brushHollow);
}

void CViewportTestView::endDrawing(CDC* pDC)
{
	pDC->SelectObject(m_penOld);
	pDC->SelectObject(m_brushOld);
}

void CViewportTestView::drawFrame(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, RGB(0, 0, 0));
	pDC->SelectObject(pen);

	pDC->SetMapMode(MM_TEXT);

	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportOrg(0, 0);

	pDC->SetWindowExt(0, 0);
	pDC->SetViewportExt(0, 0);

	pDC->SelectClipRgn(NULL);

	pDC->MoveTo(m_rectFrame.left, m_rectFrame.top);
	pDC->LineTo(m_rectFrame.left, m_rectFrame.bottom);
	pDC->LineTo(m_rectFrame.right, m_rectFrame.bottom);
}

void CViewportTestView::drawSample(CDC* pDC)
{
	CPoint p1;
	CPoint p2;

	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetWindowExt(m_sizeWindowExt);

	CSize sizeExt;
	sizeExt.cx = m_sizeViewportExt.cx * m_mag;
	sizeExt.cy = m_sizeViewportExt.cy * m_mag * m_magY;

	pDC->SetViewportExt(sizeExt);

	pDC->SetWindowOrg(0, 0);		// 論理座標系の基準点（ビューポートの基準点と重なる点）
	pDC->SetViewportOrg(m_ptOrg);	// ビューポートの基準点

	CPoint ptOrgLP = m_ptOrg;
	pDC->DPtoLP(&ptOrgLP);


	CRgn rgn;
	rgn.CreateRectRgnIndirect(m_rectFrame);
	pDC->SelectClipRgn(&rgn);

	//pDC->Rectangle(0, 0, 100 * m_mag, 100 * m_mag * m_magY);
	pDC->Rectangle(0, 0, 100000, 100000);
	pDC->MoveTo(100000, 0);
	pDC->LineTo(0, 100000);
	//pDC->TextOutW(0, 0, CString(_T("曲率")));

	pDC->SelectObject(m_pen1);

	pDC->SetMapMode(MM_TEXT);

	pDC->SetWindowExt(m_sizeWindowExt);
	pDC->SetViewportExt(m_sizeViewportExt);

	pDC->Rectangle(0, 0, 100, -100);
	pDC->MoveTo(0, 0);
	pDC->LineTo(100, -100);


	p1.x = m_vPointData[0].x + m_vectZoom.x;
	p1.y = m_vPointData[0].y + m_vectZoom.y;

	p2.x = m_vPointData[1].x + m_vectZoom.x;
	p2.y = m_vPointData[1].y + m_vectZoom.y;


	p1.x *= m_mag;
	p1.y *= m_mag;

	p2.x *= m_mag;
	p2.y *= m_mag;


	CString str;
	str.Format(_T("(%d, %d)"), m_ptOrg.x, m_ptOrg.y);
	pDC->TextOutW(0, 0, str);

	CString str2;
	str2.Format(_T("(%d, %d)"), ptOrgLP.x, ptOrgLP.y);
	pDC->TextOutW(0, 20, str2);
}

// CViewportTestView 印刷

BOOL CViewportTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CViewportTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CViewportTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CViewportTestView 診断

#ifdef _DEBUG
void CViewportTestView::AssertValid() const
{
	CView::AssertValid();
}

void CViewportTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewportTestDoc* CViewportTestView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewportTestDoc)));
	return (CViewportTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CViewportTestView メッセージ ハンドラー


BOOL CViewportTestView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	//return CView::OnMouseWheel(nFlags, zDelta, pt);

	CRect rect;
	GetClientRect(&rect);

	if (zDelta > 0)
	{
		if (nFlags == MK_CONTROL)
		{
			m_magY += m_magStep;
		}
		else
		{ 
			m_magOld = m_mag;
			//if (m_mag >= 1.0)
			//	m_mag += m_magStep;
			//else
			//	m_mag /= m_magStep;
			m_mag *= 1.25;

			//CPoint ptClient = pt;
			//ScreenToClient(&ptClient);
			
			//CPoint p = m_ptOrg - ptClient;
			//Vector v(p);
			//v /= m_magOld;
			//v *= m_mag;
			//m_ptOrg = ptClient + v.toCPoint();

			m_ptOrg = getNewOrgOnMouseWheel(pt);
		}
	}
	else
	{
		if (nFlags == MK_CONTROL)
		{
			m_magY -= m_magStep;
			if (m_magY < 1.0)
				m_magY = 1.0;
		}
		else
		{
			m_magOld = m_mag;
			//if (m_mag >= 1.0)
			//	m_mag -= m_magStep;
			//else
			//{
			//	m_mag *= m_magStep;
			//	if (m_mag < pow(m_magStep, 4))
			//	{
			//		m_mag = pow(m_magStep, 4);
			//		return TRUE;
			//	}
			//}
			m_mag *= 0.8;

			//CPoint ptClient = pt;
			//ScreenToClient(&ptClient);

			//CPoint p = m_ptOrg - ptClient;
			//Vector v(p);
			//v /= m_magOld;
			//v *= m_mag;
			//m_ptOrg = ptClient + v.toCPoint();

			m_ptOrg = getNewOrgOnMouseWheel(pt);

		}
	}
	
	invalidateRect();

	return TRUE;
}


void CViewportTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	//CView::OnMouseMove(nFlags, point);


	if (nFlags & (MK_MBUTTON | MK_LBUTTON))
	{
		int id = point.x % 10;

		RV1EventHnadler eh = this->RV1Event[(RV1EventID)id];
		if (eh)
		{
			(this->*eh)();
		}

		if (point != m_ptOld)
		{
			CPoint vect = point - m_ptOld;
			m_ptOrg += vect;
			
			invalidateRect();

			m_ptOld = point;
		}
	}

	//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
	//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);

}

void CViewportTestView::invalidateRect()
{
	CRect rect = m_rectClient;
	rect.top += m_rectToolBar.bottom;
	InvalidateRect(rect);
}

void CViewportTestView::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_ptOld = point;
}


void CViewportTestView::OnSize(UINT nType, int cx, int cy)
{
	if (m_ptOrg.x == INT_MIN)
		return;

	initRect();

	CPoint v = m_ptOrg - m_ptCenterOld;	
	CPoint ptCenterNew(
		(m_rectFrame.left + m_rectFrame.right) / 2,
		(m_rectFrame.top + m_rectFrame.bottom) / 2);
	m_ptOrg = ptCenterNew + v;
	m_ptCenterOld = ptCenterNew;


	invalidateRect();
}


void CViewportTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);

	if (nChar == VK_SHIFT)
	{
		CPoint p;
		GetCursorPos(&p);
		ScreenToClient(&p);
		m_ptOld = p;
	}
}


void CViewportTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CView::OnLButtonDown(nFlags, point);
	m_ptOld = point;

	CString str;
	str.Format(_T("(%d, %d)"), point.x, point.y);
	CClientDC dc(this);
	dc.TextOut(point.x, point.y, str);
	
	SetFocus();
}


int CViewportTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
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

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

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


	m_wndToolBar.SetButtonStyle(4, TBBS_CHECKBOX);

	return 0;
}


void CViewportTestView::OnIdtbButton0()
{
	m_spinCtrlDlg.DoModal();
}


void CViewportTestView::OnIdtbButton1()
{
	int nFrameW = m_rectFrame.Width() - 40;
	int nFrameH = m_rectFrame.Height() - 40;
	
	double dFrameW = nFrameW * 1000;
	double dFrameH = nFrameH * 1000;

	
	vector<int> vX;
	vector<int> vY;

	for (int i = 0; i <= 10; i++)
	{
		vX.push_back(i * 10000);
		vY.push_back(i * 10000);
	}

	int nMaxX = *max_element(vX.begin(), vX.end());
	int nMaxY = *max_element(vY.begin(), vY.end());
	int nMinX = *min_element(vX.begin(), vX.end());
	int nMinY = *min_element(vY.begin(), vY.end());

	CPoint ptMax(nMaxX, nMaxY);
	CPoint ptMin(nMinX, nMinY);

	CRect rectArea(ptMax, ptMin);
	rectArea.NormalizeRect();

	int nAreaW = rectArea.Width();
	int nAreaH = rectArea.Height() * m_magY;

	double dAreaW = nAreaW;
	double dAreaH = nAreaH;
	
	if (dAreaH / dAreaW > dFrameH / dFrameW)
	{
		m_mag = dFrameH / dAreaH;
	}
	else
	{
		m_mag = dFrameW / dAreaW;
	}
	
	int nAreaWd = (int)(dAreaW / 1000.0 * m_mag);
	int nAreaHd = (int)(dAreaH / 1000.0 * m_mag);

	if (dAreaH / dAreaW > dFrameH / dFrameW)
	{
		m_ptOrg.x = m_rectFrame.left + 20 + (nFrameW - nAreaWd) / 2;
		m_ptOrg.y = m_rectFrame.bottom - 20;
	}
	else
	{
		m_ptOrg.x = m_rectFrame.left + 20;
		m_ptOrg.y = m_rectFrame.bottom - 20 - (nFrameH - nAreaHd) / 2;
	}

	invalidateRect();
}

void CViewportTestView::OnIdtbButton2()
{
	//GetParentFrame()->PostMessage(WM_COMMAND, 1L, 2L);
	
	isOn_ = !isOn_;
	m_wndToolBar.GetToolBarCtrl().CheckButton(IDTB_BUTTON_3, isOn_);
	//m_wndToolBar.GetToolBarCtrl().PressButton(IDTB_BUTTON_3, FALSE);

}

void CViewportTestView::OnIdtbButton3()
{
	OudanDlg::toggleShowHide();
}

void CViewportTestView::OnCombo()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	SetFocus();
}


void CViewportTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(_T(""));

	CView::OnLButtonUp(nFlags, point);
}


BOOL CViewportTestView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1L)
	{
		MessageBox(_T("TEST"));
		return TRUE;
	}

	return CView::OnCommand(wParam, lParam);
}
