
// ViewportTestView.h : CViewportTestView クラスのインターフェイス
//

#pragma once

#include <vector>
#include <map>
#include "SpinCtrlDlg.h"
#include "MainFrm.h"
#include "ViewportTestDoc.h"

using namespace std;

class CViewportTestView : public CView
{
public: // シリアル化からのみ作成します。
	CViewportTestView();
	DECLARE_DYNCREATE(CViewportTestView)

	SpinCtrlDlg m_spinCtrlDlg;

	bool isOn_ = false;
	BOOL isChecked_ = FALSE;

// 属性
public:
	enum RV1EventID {
		EVENT0 = 0,
		EVENT1,
		EVENT2,
		EVENT3,
	};

	typedef void (CViewportTestView::*RV1EventHnadler)();
	map<RV1EventID, RV1EventHnadler> RV1Event;

	void onEvent0()
	{ 
		//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(_T("onEvent0"));
		return;
	}
	void onEvent1()
	{
		//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(_T("onEvent1"));
		return;
	}

	void onEvent2()
	{
		//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(_T("onEvent2"));
		return;
	}
	void onEvent3()
	{
		//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(_T("onEvent3"));
		return;
	}

	void setDocument(CDocument* pDocument)
	{
		m_pDocument = pDocument;
	}

	CToolBar m_wndToolBar;
	//CMFCToolBar m_wndToolBar;
	CComboBox m_comboBox;

	CRect m_rectClient;
	CRect m_rectFrame;
	CRect m_rectCurvature;
	CRect m_rectToolBar;

	double m_mag;		// 現在の表示倍率　magnification
	double m_magOld;	// 一つ前の表示倍率
	double m_magY;		// Y軸方向の表示倍率
	double m_magStep;	// 倍率の刻み（例：0.5倍ずつ増加）

	CPoint m_ptOld;
	CPoint m_ptOrg;

	CPoint m_ptFrameCenter;

	CPoint m_ptCenterOld;

	CSize m_sizeWindowExt;
	CSize m_sizeViewportExt;


	CPen m_pen1;
	CBrush m_brushHollow;

	CPen* m_penOld;
	CBrush* m_brushOld;

	class Vector
	{
	public:
		double x;
		double y;

	public:
		Vector()
		{
			x = 0.0;
			y = 0.0;
		}
		Vector(Vector& v)
		{
			x = v.x;
			y = v.y;
		}
		Vector(CPoint& p)
		{
			x = p.x;
			y = p.y;
		}
		Vector(CPoint& p1, CPoint& p2)
		{
			x = p2.x - p1.x;
			y = p2.y - p1.y;
		}
		Vector(double x, double y)
		{
			x = x;
			y = y;
		}
		Vector(int x, int y)
		{
			x = x;
			y = y;
		}

		Vector operator + (Vector& v)
		{
			double x1 = x + v.x;
			double y1 = y + v.y;
			return Vector(x1, y1);
		}
		Vector operator - (Vector& v)
		{
			double x1 = x - v.x;
			double y1 = y - v.y;
			return Vector(x1, y1);
		}
		Vector operator * (double mag)
		{
			double x1 = x * mag;
			double y1 = y * mag;
			return Vector(x1, y1);
		}
		Vector operator / (double mag)
		{
			double x1 = x / mag;
			double y1 = y / mag;
			return Vector(x1, y1);
		}
		Vector operator += (Vector& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		Vector operator -= (Vector& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		Vector& operator *= (double mag)
		{
			x *= mag;
			y *= mag;
			return *this;
		}
		Vector& operator /= (double mag)
		{
			x /= mag;
			y /= mag;
			return *this;
		}
		CPoint toCPoint()
		{
			int x1 = (int)(x + 0.5);
			int y1 = (int)(y + 0.5);
			return CPoint(x1, y1);
		}
		double getLength()
		{
			return sqrt(x * x + y * y);
		}
		
		void Unit()
		{
			x /= getLength();
			y /= getLength();
		}
	};

	Vector m_vectZoom;

	vector<CPoint> m_vPointData;
	

	CViewportTestDoc* GetDocument() const;

// 操作
public:
	/// <summary>
	/// Rubberbandクラスの新しいインスタンスを初期化します。
	/// </summary>
	/// <param name="rectSrc">初期状態の矩形</param>
	/// <param name="availableHandles">表示するハンドル</param>
	/// <param name="rectLimit">可動範囲を示す矩形</param>
	void invalidateRect();
	void initRect();

	void beginDrawing(CDC* pDC);
	void endDrawing(CDC* pDC);

	void drawSample(CDC* pDC);
	void drawFrame(CDC* pDC);
	void drawGrid(CDC* pDC);
	void drawCurvature(CDC* pDC);
	void drawCurvatureFrame(CDC* pDC);
	void drawCurvatureHeader(CDC* pDC);
	void drawCurvatureLine(CDC* pDC);

	void drawRgn(CDC* pDC);
	void drawRgn2(CDC* pDC);

	CPoint getNewOrgOnMouseWheel(CPoint& pt)
	{
		CPoint ptClient = pt;
		ScreenToClient(&ptClient);
		CPoint v = m_ptOrg - ptClient;

		v.x *= 1000;
		v.y *= 1000;

		v.x = (int)(v.x / m_magOld);
		v.y = (int)(v.y / m_magOld);

		v.x = (int)(v.x * m_mag);
		v.y = (int)(v.y * m_mag);


		v.x /= 1000;
		v.y /= 1000;

		CPoint ptNewOrg = ptClient + v;

		return ptNewOrg;
	}

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CViewportTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnIdtbButton0();
	afx_msg void OnIdtbButton1();
	afx_msg void OnIdtbButton2();
	afx_msg void OnIdtbButton3();

	afx_msg void OnCombo();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // ViewportTestView.cpp のデバッグ バージョン
inline CViewportTestDoc* CViewportTestView::GetDocument() const
   { return reinterpret_cast<CViewportTestDoc*>(m_pDocument); }
#endif

