
// MainView.cpp : CMainView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Main.h"
#endif

#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CView)

BEGIN_MESSAGE_MAP(CMainView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMainView ����/�Ҹ�

CMainView::CMainView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMainView �׸���

void CMainView::OnDraw(CDC* /*pDC*/)
{
	CMainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMainView �μ�

BOOL CMainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMainView ����

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainDoc* CMainView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
	return (CMainDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainView �޽��� ó����
