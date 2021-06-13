/**
 * \file ChildView.h
 *
 * \author 
 *
 * The main child view window.
 */


#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Sandwiches.h"


/**
 * The main child view window.
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	std::shared_ptr<Gdiplus::Bitmap> GetCachedImage(const std::wstring name);

	/// The sandwiches
	CSandwiches mSandwiches;

	/// First draw flag
	bool mFirstDraw = true;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates

	double mDuration = 0;		///< Duration for this sandwich presentation

	/// The Image cache
	std::map<std::wstring, std::shared_ptr<Gdiplus::Bitmap>> mImageCache;

	/// Sandwich names
	std::vector<std::wstring> mNames;

	/// The sandwiches menu (dynamically created)
	CMenu mSandwichMenu;

	/// The current sandwich to display
	int mCurrentSandwich = 0;

public:
	void OnRangeCmds(UINT nID);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

