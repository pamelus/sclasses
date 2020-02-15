#ifndef SAPP_CPP
#define SAPP_CPP

#include <windows.h>
#include <commctrl.h>
#include "SApp.h"
#include "SWindow.h"

SApp::SApp():
hThis(NULL), hAccel(NULL), hMainWindow(NULL), hMdiWindow(NULL)
{ }

SApp::SApp(HINSTANCE hInstance):
hThis(hInstance), hAccel(NULL), hMainWindow(NULL), hMdiWindow(NULL)
{ }

SApp::~SApp()
{
    if(hAccel) { DestroyAcceleratorTable(hAccel); }
}
 
DWORD SApp::SetAccel(HACCEL hNewAccel)
{
    hAccel = hNewAccel;
    return 0;
}
    
DWORD SApp::SetMainWindow(HWND hNewMain)
{
    hMainWindow = hNewMain;
    return 0;
}
    
DWORD SApp::SetMdiWindow(HWND hNewMdi)
{
    hMdiWindow = hNewMdi;
    return 0;
}
    
HINSTANCE SApp::GetInstance() const
{
    return hThis;
}
    
DWORD SApp::Loop()
{
    MSG msg;
    while(IsWindow(hMainWindow))
    {
        if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(hMdiWindow)
                if(TranslateMDISysAccel(hMdiWindow, &msg)) continue;
            if(hAccel)
                if(TranslateAccelerator(hMainWindow, hAccel, &msg)) continue;
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }    
    }
    return msg.wParam;
}

DWORD SApp::Register()
{
    WNDCLASSEX wincl;
    wincl.hInstance = hThis;
    wincl.lpszClassName = "wcMainWindowClass";
    wincl.lpfnWndProc = DefWindowProc;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = NULL;
    wincl.hIconSm = NULL;
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BTNSHADOW;
    RegisterClassEx(&wincl);
    
    wincl.lpszClassName = "wcTooltipClass";
    wincl.hbrBackground = (HBRUSH)COLOR_BTNSHADOW;
    RegisterClassEx(&wincl);
 
    InitCommonControls();
    
    return 0;
}    

LRESULT CALLBACK ClassWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SWindow * sWin = (SWindow *)GetWindowLong(hwnd, GWL_USERDATA);
    if(sWin)
        return sWin->InclassWindowProc(hwnd, message, wParam, lParam);
    else
        return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif
