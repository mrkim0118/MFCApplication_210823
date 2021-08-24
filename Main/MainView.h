
// MainView.h : CMainView Ŭ������ �������̽�
//

#pragma once


class CMainView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMainView();
	DECLARE_DYNCREATE(CMainView)

// Ư���Դϴ�.
public:
	CMainDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MainView.cpp�� ����� ����
inline CMainDoc* CMainView::GetDocument() const
   { return reinterpret_cast<CMainDoc*>(m_pDocument); }
#endif

