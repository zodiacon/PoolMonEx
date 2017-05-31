#pragma once

#include <map>

// CPoolListCtrl

class CPoolListCtrl : public CMFCListCtrl {
	DECLARE_DYNAMIC(CPoolListCtrl)

public:
	CPoolListCtrl();
	virtual ~CPoolListCtrl();

	COLORREF OnGetCellBkColor(int row, int col);

	void Pause(bool pause);
	void CopyToClipboard();

	static const unsigned NonPagedBit = 0x80000000;

private:
    struct PoolTagInfo {
        SYSTEM_POOLTAG Tag;
        PCWSTR SourceName;
        PCWSTR SourceDesc;
    };

	CImageList m_Images;
	std::map<ULONG_PTR, PoolTagInfo> m_Tags;
	std::map<std::pair<int, int>, COLORREF> m_CellColors;

	int m_SortColumn = -1;
	bool m_Ascending = true;

	int AddItem(int index, const SYSTEM_POOLTAG&, PCSTR tag, bool nonpaged);
	void UpdateItem(int index, PoolTagInfo& tag, bool nonpaged);
	bool ProcessChanges(int row, const SYSTEM_POOLTAG& newTag, const SYSTEM_POOLTAG& oldTag, bool nonpaged);
	void AddColor(int row, int col, COLORREF color);

	void BuildPoolData();
	void RefreshPoolData();
	int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

	static ULONG ReverseTag(ULONG tagUlong);

	SYSTEM_POOLTAG_INFORMATION* m_pPoolInfo;
	const DWORD m_PoolInfoSize = 1 << 21;

	static const COLORREF Green = RGB(0, 255, 0);
	static const COLORREF Red = RGB(255, 0, 0);

	enum ColumnType : int
	{
		TagName,
		PoolType,
		Allocs,
		Frees,
		Diff,
		Usage,
		UsageKB,
		PerAlloc,
        SourceName,
        SourceDescription
	};

	bool m_Update = false;
	bool m_Paused = false;
	int m_Interval = 10000;
	bool m_DynamicSort = true;
	int m_IntervalIndex = 1;

    std::map<std::string, std::pair<std::wstring, std::wstring>> m_PoolTagMap;

private:
    void LoadPoolTags();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnViewRefresh();
	void OnIntervalChange(UINT id);
	void OnIntervalChangeUpdateUI(CCmdUI* pCmdUI);
	afx_msg void OnViewDynamicsort();
	afx_msg void OnUpdateViewDynamicsort(CCmdUI *pCmdUI);
};


