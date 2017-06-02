
// PoolView.h : interface of the CPoolView class
//


#pragma once

#include "PoolListCtrl.h"


// CPoolView window

class CPoolView : public CWnd
{
// Construction
public:
	CPoolView();

// Attributes
public:

// Operations
public:
	void Refresh()
	{
		m_List.OnViewRefresh();
	}

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CPoolView();

    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// Generated message map functions
protected:
	CPoolListCtrl m_List;
	bool m_Paused = false;

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditCopy();
	afx_msg void OnFileSave();
	afx_msg void OnViewPause();
	afx_msg void OnUpdateViewPause(CCmdUI *pCmdUI);
};

