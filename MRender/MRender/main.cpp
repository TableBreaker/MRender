// MRender.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MRender.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

MRender *mRender;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance, int &x, int &y, int &screenWidth, int &screenHeight);
BOOL                InitInstance(HINSTANCE, int nCmdShow, int x, int y, int screenWidth, int screenHeight);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	int x, y, screenWidth, screenHeight;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MRENDER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, x, y, screenWidth, screenHeight);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow, x, y, screenWidth, screenHeight))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MRENDER));

    MSG msg;


	// MRender
	mRender = new MRender;
	auto rtCode = 0;

	if (!mRender)
	{
		return rtCode;
	}

	bool done, result;

	if (mRender->Initialize(screenWidth, screenHeight))
	{
		// Loop until there is a quit message from the window or the user.
		done = false;
		while (!done)
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			// If windows signals to end the application then exit out.
			if (msg.message == WM_QUIT)
			{
				rtCode = (int)msg.wParam;
				done = true;
			}
			else
			{
				// Otherwise do the frame processing
				result = mRender->Paint(msg.hwnd);
				if (!result)
				{
					rtCode = (int)msg.wParam;
					done = true;
				}
			}
		}
	}

	mRender->Shutdown();
	delete mRender;
	mRender = nullptr;

	GdiplusShutdown(gdiplusToken);

	return rtCode;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance, int &x, int &y, int &screenWidth, int &screenHeight)
{
    WNDCLASSEXW wcex;
	DEVMODE dmScreenSettings;

    wcex.cbSize = sizeof(WNDCLASSEXW);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MRENDER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_MRENDER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ATOM a = RegisterClassExW(&wcex);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to the full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		x = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		y = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	return a;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, int x, int y, int screenWidth, int screenHeight)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowExW(
	   WS_EX_APPWINDOW,
	   szWindowClass, 
	   szTitle,
	   WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
	   x,
	   y,
	   screenWidth,
	   screenHeight, 
	   nullptr,
	   nullptr, 
	   hInstance, 
	   nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_PAINT:
			mRender->Paint(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return mRender->MessageHandler(hWnd, message, wParam, lParam);
	}
    return 0;
}

//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
