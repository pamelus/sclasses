#ifndef SWINDOW_CPP
#define SWINDOW_CPP
#include <windows.h>
#include "SApp.h"
#include "SWindow.h"

SWindow::SWindow(SApp * sMyApp, const char * pszClass, HWND hParent, UINT id, UINT style, UINT exStyle):
sApp(sMyApp), pChild(NULL), nChild(0)
{
    hwnd = CreateWindowEx(exStyle, pszClass, NULL, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, (HMENU)id, sApp->GetInstance(), NULL);
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);
    wProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)ClassWindowProc);
}

SWindow::~SWindow()
{
    if(pChild) delete [] pChild;
    HFONT hFont = this->GetFont();
    if(hFont) DeleteObject(hFont);
    HICON hIconBig = this->GetIconBig();
    if(hIconBig) DestroyIcon(hIconBig);
    HICON hIconSmall = this->GetIconSmall();
    if(hIconSmall) DestroyIcon(hIconSmall);
    DestroyWindow(hwnd);
}

DWORD SWindow::Show(int nShow) const
{
    ShowWindow(hwnd, nShow);
    for(DWORD i = 0; i < nChild; i++)
        pChild[i]->Show(nShow);
    return 0;
}

DWORD SWindow::AddChild(SWindow * sChild)
{
    SWindow * temp[nChild];
    for(DWORD i = 0; i < nChild; i++)
        temp[i] = pChild[i];
        
    delete [] pChild;
    pChild = new (SWindow *)[nChild+1];
    
    for(DWORD i = 0; i < nChild; i++)
        pChild[i] = temp[i];
    pChild[nChild] = sChild;
    nChild++;
    return 0;
}

DWORD SWindow::SetPosition(int x, int y, int cx, int cy)
{
    MoveWindow(hwnd, x, y, cx, cy, true);    
    return 0;
}

DWORD SWindow::SetPosition(const RECT * pRect)
{
    return this->SetPosition(pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top);
}

DWORD SWindow::SetText(const char * pszText)
{
    SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)pszText);
    return 0;
}

DWORD SWindow::SetCaption(const char * pszText)
{
    SetWindowText(hwnd, pszText);
    return 0;
}

DWORD SWindow::SetIcon(HICON hIcon)
{
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    return 0;
}
    
DWORD SWindow::SetIcon(HINSTANCE hInst, const char * pszIcon)
{
    HICON hIcon = LoadIcon(hInst, pszIcon);
    this->SetIcon(hIcon);
    DestroyIcon(hIcon);
    return 0;
}
    
DWORD SWindow::SetIcon(HINSTANCE hInst, UINT uIcon)
{
    return this->SetIcon(hInst, MAKEINTRESOURCE(uIcon));
}    

DWORD SWindow::SetFont(HFONT hFont)
{
    HFONT hOld = this->GetFont();
    if(hOld) DeleteObject(hFont);
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, MAKELONG(TRUE, 0));
    return 0;
}

DWORD SWindow::SetStyle(UINT uStyle)
{
    SetWindowLong(hwnd, GWL_STYLE, (LONG)uStyle);
    return 0;
}    

DWORD SWindow::GetPosition(int * x, int * y, int * cx, int * cy) const
{
    RECT rect; this->GetPosition(&rect);
    
    if(x) *x = rect.left; if(y) *y = rect.top;
    if(cx) *cx = rect.right - rect.left;
    if(cy) *cy = rect.bottom - rect.top;
    
    return 0;
}

DWORD SWindow::GetPosition(RECT * pRect) const
{
    if(pRect) GetWindowRect(hwnd, pRect);
    return 0;
}

DWORD SWindow::GetClientArea(int * cx, int * cy) const
{
    RECT rect; this->GetClientArea(&rect);
    
    if(cx) *cx = rect.right - rect.left;
    if(cy) *cy = rect.bottom - rect.top;
    
    return 0;
}

DWORD SWindow::GetClientArea(RECT * pRect) const
{
    if(pRect) GetClientRect(hwnd, pRect);
    return 0;
}

DWORD SWindow::GetText(char * pszText, DWORD dwSize) const
{
    SendMessage(hwnd, WM_GETTEXT, dwSize, (LPARAM)pszText);
    return 0;
}

DWORD SWindow::GetCaption(char * pszText, DWORD dwSize) const
{
    GetWindowText(hwnd, pszText, dwSize);
    return 0;
}

HICON SWindow::GetIconBig() const
{
    return (HICON)SendMessage(hwnd, WM_GETICON, ICON_BIG, 0);
}

HICON SWindow::GetIconSmall() const
{
    return (HICON)SendMessage(hwnd, WM_GETICON, ICON_SMALL, 0);
}

HFONT SWindow::GetFont() const
{
    return (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
}

DWORD SWindow::GetStyle() const
{
    return (DWORD)GetWindowLong(hwnd, GWL_STYLE);
}    

BOOL CALLBACK SWindow::OnEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnClose()
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnPaint()
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnResize(int cx, int cy)
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnTooltip()
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnTimer(WORD id)
{
    return FALSE;
}

BOOL CALLBACK SWindow::OnCommand(WORD iCommand, WORD hiword, LPARAM lParam)
{
    return FALSE;
}

LRESULT SWindow::DoCommand(WORD loword, WORD hiword, LPARAM lParam)
{
    return SendMessage(hwnd, WM_COMMAND, MAKELONG(loword, hiword), lParam);
}
    
LRESULT SWindow::DoUpdate()
{
    InvalidateRect(hwnd, NULL, false);
    return 0;
}

LRESULT SWindow::DoEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    return SendMessage(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK SWindow::InclassWindowProc(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam)
{
    SetReturnValue(0);
    
    switch(message)
    {
        case WM_CLOSE:
            if(this->OnClose())
                return this->GetReturnValue();
            break;
        case WM_SIZE:
            if(this->OnResize(LOWORD(lParam), HIWORD(lParam)))
                return this->GetReturnValue();
            break;            
        case WM_PAINT:
            if(this->OnPaint())
                return this->GetReturnValue();
            break;
        case WM_COMMAND:
            if(this->OnCommand(LOWORD(wParam), HIWORD(wParam), lParam))
                return this->GetReturnValue();
            break;
        case WM_TIMER:
            if(this->OnTimer(wParam))
                return this->GetReturnValue();
            break;
    }    
        
    if(this->OnEvent(message, wParam, lParam))
        return this->GetReturnValue();
    return CallWindowProc(wProc, hWin, message, wParam, lParam);
}

LRESULT SWindow::SetReturnValue(LRESULT nValue)
{
    LRESULT rValue = value; value = nValue;
    return rValue;
}

LRESULT SWindow::GetReturnValue() const
{
    return value;
}

HWND SWindow::GetHwnd() const
{
    return hwnd;
}

SApp * SWindow::GetSApp() const
{
    return sApp;
}

#endif
