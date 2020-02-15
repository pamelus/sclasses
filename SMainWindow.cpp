#ifndef SMAINWINDOW_CPP
#define SMAINWINDOW_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SMainWindow.h"

SMainWindow::SMainWindow(SApp * sApp, UINT style, UINT exStyle):
SWindow(sApp, "wcMainWindowClass", HWND_DESKTOP, 0, style, exStyle)
{
    sApp->SetMainWindow(hwnd);
}
    
SMainWindow::~SMainWindow()
{ }

BOOL CALLBACK SMainWindow::OnClose()
{
    DestroyWindow(hwnd);
    return TRUE;
}

#endif
