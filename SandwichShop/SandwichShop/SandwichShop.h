/**
 * \file SandwichShop.h
 *
 * \author 
 *
 * SandwichShop.h : main header file for the SandwichShop application
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols



/**
 * Sandwich Shop application class
 */
class CSandwichShopApp : public CWinApp
{
public:
	CSandwichShopApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
};

/// Man application object
extern CSandwichShopApp theApp;
