#ifndef SICON_CPP
#define SICON_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SText.h"
#include "SIcon.h"

SIcon::SIcon(SWindow * pWin):
SText(pWin, SS_ICON)
{ }
    
SIcon::~SIcon()
{
    HICON hIcon = this->GetIcon();
    DestroyIcon(hIcon);
}   
 
DWORD SIcon::SetIcon(HICON hIcon)
{
    SendMessage(hwnd, STM_SETICON, (WPARAM)hIcon, 0);
    return 0;
}
    
DWORD SIcon::SetIcon(HINSTANCE hInst, const char * pszIcon)
{
    HICON hIcon = LoadIcon(hInst, pszIcon);
    this->SetIcon(hIcon);
    DestroyIcon(hIcon);
}
    
DWORD SIcon::SetIcon(HINSTANCE hInst, UINT uIcon)
{
    return this->SetIcon(hInst, MAKEINTRESOURCE(uIcon));
}
    
HICON SIcon::GetIcon() const
{
    return (HICON)SendMessage(hwnd, STM_GETICON, 0, 0);
}    

#endif
