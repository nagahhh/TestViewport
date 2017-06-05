
// ViewportTestView.h : CViewportTestView �N���X�̃C���^�[�t�F�C�X
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
public: // �V���A��������̂ݍ쐬���܂��B
	CViewportTestView();
	DECLARE_DYNCREATE(CViewportTestView)

	SpinCtrlDlg m_spinCtrlDlg;

	bool isOn_ = false;
	BOOL isChecked_ = FALSE;

// ����
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

	double m_mag;		// ���݂̕\���{���@magnification
	double m_magOld;	// ��O�̕\���{��
	double m_magY;		// Y�������̕\���{��
	double m_magStep;	// �{���̍��݁i��F0.5�{�������j

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

// ����
public:
	/// <summary>
	/// Rubberband�N���X�̐V�����C���X�^���X�����������܂��B
	/// </summary>
	/// <param name="rectSrc">������Ԃ̋�`</param>
	/// <param name="availableHandles">�\������n���h��</param>
	/// <param name="rectLimit">���͈͂�������`</param>
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

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	virtual ~CViewportTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

#ifndef _DEBUG  // ViewportTestView.cpp �̃f�o�b�O �o�[�W����
inline CViewportTestDoc* CViewportTestView::GetDocument() const
   { return reinterpret_cast<CViewportTestDoc*>(m_pDocument); }
#endif

