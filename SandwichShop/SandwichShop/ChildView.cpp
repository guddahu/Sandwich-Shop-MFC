
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include <sstream>
#include <iomanip>

#include "SandwichShop.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "SandwichesLoader.h"
#include "Sandwich.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Gdiplus;

/// Duration of the frame animation timer in milliseconds
const int FrameDuration = 32;

/// Directory containing the images
const std::wstring DirectoryContainingImages = L"images/";

/// File containing the sandwich data
const std::wstring SandwichesDataFile = L"data/sandwiches.xml";

/// Time to display each sandwich ingredient in seconds
const double TimePerIngredient = 0.3;

/// How much each each ingredient overlaps the previous one.
const float Overlap = 0.85f;

const float GrillOverlap = 0.15f;


// CChildView

CChildView::CChildView()
{
	CSandwichesLoader loader;
	loader.Load(&mSandwiches, SandwichesDataFile);
    mNames = loader.Names();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_COMMAND_RANGE(ID_SANDWICHES, ID_SANDWICHES_END, &CChildView::OnRangeCmds)
END_MESSAGE_MAP()




/**
 * Handle any processing prior to creation of the window
 * \param cs Create structure
 * \return TRUE if successful
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}


/**
 * Handle window creation events
 * \param lpCreateStruct Creation structure
 * \return 0 if successful
 */
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;


    auto menu = GetParentFrame()->GetMenu();

    mSandwichMenu.CreatePopupMenu();
    auto id = ID_SANDWICHES;

    for (auto name : mNames)
    {
        mSandwichMenu.AppendMenu(MF_STRING | MF_ENABLED, id, name.c_str());
        mSandwichMenu.EnableMenuItem(id, MF_ENABLED);
        id++;
    }

    menu->InsertMenu(2, MF_POPUP | MF_BYPOSITION, (UINT_PTR)mSandwichMenu.m_hMenu, L"Sandwiches");

    CMenu* mmenu = AfxGetMainWnd()->GetMenu();
    CMenu* submenu = mmenu->GetSubMenu(2);
    submenu->CheckMenuItem(ID_SANDWICHES + mCurrentSandwich, MF_CHECKED | MF_BYCOMMAND);

    return 0;
}


/**
 * Handle Paint events
 */
void CChildView::OnPaint() 
{
    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);
    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;

    mDuration += elapsed;


	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);

    CRect rect;
    GetClientRect(&rect);
    float width = (float)rect.Width();
    auto centerX = width / 2;

	auto sandwich = mSandwiches.FindSandwich(mNames[mCurrentSandwich]);
    if (sandwich != nullptr)
    {
	    auto images = sandwich->Images();


        auto bottomY = rect.Height() - 10;
        float y = (float)bottomY;

        auto maxLift = (float)rect.Height() * 2;

        int layer = 0;

        // Currently animated layer
        int animLayer = (int)(mDuration / TimePerIngredient);
        double animT = fmod(mDuration / TimePerIngredient, 1);
        size_t index = 0;

        // Draw the grill if necessary
        if (images.size() > 0 && images.front() == L"grill.png")
        {
            index++;

            auto bitmap = GetCachedImage(L"grill.png");

            float wid = (float)bitmap->GetWidth();
            float hit = (float)bitmap->GetHeight();

            graphics.DrawImage(bitmap.get(), (float)centerX - wid / 2, (float)y - hit, wid, hit);

            y -= hit * (1 - GrillOverlap);
        }

        // Draw the layers
        for ( ; index < images.size();  index++)
        {
            auto image = images[index];

            float lift = 0;
            if (layer == animLayer)
            {
                lift += (float)((1 - animT) * maxLift);
            }

            auto bitmap = GetCachedImage(image);

            float wid = (float)bitmap->GetWidth();
            float hit = (float)bitmap->GetHeight();

            graphics.DrawImage(bitmap.get(), (float)centerX - wid / 2, (float)y - hit - lift, wid, hit);

            y -= hit * (1 - Overlap);

            layer++;
            if (layer > animLayer)
            {
                break;
            }
        }


        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 16);
        SolidBrush black(Color::Black);
        StringFormat stringFormat;
        stringFormat.SetAlignment(StringAlignmentCenter);

        int cnt = 27;

        wstringstream str;

        // The line to display the sandwich name and price is commented out until
        // you provide the appropriate getters for those values.

      //  str << L"Please comment line " << __LINE__ << L" and \n uncomment line " << (__LINE__ + 1) << L" in ChildView.cpp \n to display the sandwich name and price.";
        str << sandwich->GetName() << L" $" << fixed << setprecision(2) << sandwich->GetPrice();

        graphics.DrawString(str.str().c_str(),  // String to draw
            -1,         // String length, -1 so it figures it out on its own
            &font,      // The font to use
            PointF(centerX, 10),   // Where to draw (top left corner)
            &stringFormat,
            &black);    // The brush to draw the text with
    }


}


/**
* Get an image from the image cache
*
* Given a base name for an image file, determine if
* we have already loaded it. If we have, return a shared pointer
* to the Bitmap object in the cache. If we have not
* previously loaded it, load it into the cache and then
* return a pointer to the image.
* \param name The base name of the image file. We put images/ onto
* the front of this because that is where the file is located.
* \returns Pointer to cached image object or nullptr if file not found.
*/
std::shared_ptr<Gdiplus::Bitmap> CChildView::GetCachedImage(const std::wstring name)
{
    // See if the name exists in the cache already.
    auto i = mImageCache.find(name);
    if (i != mImageCache.end())
    {
        // If we got here, it does exist and i->second is a
        // reference to the bitmap object shared pointer.
        return i->second;
    }

    // We'll add the path to the name of the file here.
    wstring realname = DirectoryContainingImages + name;

    // Create a bitmap image and load the file into it.
    auto image = shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(realname.c_str()));
    if (image->GetLastStatus() != Ok)
    {
        wstring msg = wstring(L"Unable to open image ") + realname;
        AfxMessageBox(msg.c_str());
        return nullptr;
    }

    // Add it to the cache and return it.
    mImageCache[name] = image;
    return image;
}



/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}


/**
 * Handle timer event
 * \param nIDEvent Timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();

    CWnd::OnTimer(nIDEvent);
}


/**
 * Handler for the sandwich menu options.
 * \param nID ID for the sandwich option selected.
 */
void CChildView::OnRangeCmds(UINT nID)
{
    //
    // Check only the selected sandwich
    //
    CMenu* mmenu = AfxGetMainWnd()->GetMenu();
    CMenu* submenu = mmenu->GetSubMenu(2);
    submenu->EnableMenuItem(nID, MF_GRAYED);
    for (unsigned i = 0; i < mNames.size(); i++)
    {
        auto id = ID_SANDWICHES + i;
        if (id == nID)
        {
            submenu->CheckMenuItem(nID, MF_CHECKED | MF_BYCOMMAND);
        }
        else
        {
            submenu->CheckMenuItem(id, MF_UNCHECKED | MF_BYCOMMAND);
        }

    }

    //
    // Make it the current selection
    //
    mDuration = 0;
    mCurrentSandwich = nID - ID_SANDWICHES;
    Invalidate();
}