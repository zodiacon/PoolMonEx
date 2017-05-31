
// PoolView.cpp : implementation of the CPoolView class
//

#include "stdafx.h"
#include "resource.h"
#include "PoolMonEx.h"
#include "PoolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPoolView

CPoolView::CPoolView() {
}

CPoolView::~CPoolView() {
}


BEGIN_MESSAGE_MAP(CPoolView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, &CPoolView::OnEditCopy)
	ON_COMMAND(ID_VIEW_PAUSE, &CPoolView::OnViewPause)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE, &CPoolView::OnUpdateViewPause)
END_MESSAGE_MAP()

// CPoolView message handlers

BOOL CPoolView::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE | WS_EX_TRANSPARENT;
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), nullptr, NULL);

	return TRUE;
}

void CPoolView::OnPaint() {
	CPaintDC dc(this); 
}

int CPoolView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_List.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | WS_CLIPSIBLINGS, CRect(), this, 123);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_DOUBLEBUFFER);

    return 0;
}


void CPoolView::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);

	m_List.MoveWindow(0, 0, cx, cy, FALSE);
}


BOOL CPoolView::OnEraseBkgnd(CDC* pDC) {
	return TRUE;
}


void CPoolView::OnEditCopy()
{
	m_List.CopyToClipboard();
}


BOOL CPoolView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_List.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CPoolView::OnViewPause()
{
	m_Paused = !m_Paused;
	m_List.Pause(m_Paused);
}


void CPoolView::OnUpdateViewPause(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_Paused ? L"Resume" : L"Pause");
}
