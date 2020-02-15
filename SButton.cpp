#ifndef SBUTTON_CPP
#define SBUTTON_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SButton.h"

SButton::SButton(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SWindow(pWin->GetSApp(), "button", pWin->GetHwnd(), uId, WS_CHILD | uStyle, uExStyle)
{
    pWin->AddChild(this);
}

SButton::~SButton()
{
    HICON hIcon = this->GetImage();
    if(hIcon)
        DestroyIcon(hIcon);
}

DWORD SButton::Click()
{
    SendMessage(hwnd, BM_CLICK, 0, 0);
    return 0;
}    

DWORD SButton::SetImage(HICON hIcon)
{
    SendMessage(hwnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
    return 0;
}
    
DWORD SButton::SetImage(HINSTANCE hInst, char * pszImage)
{
    HICON hIcon = LoadIcon(hInst, pszImage);
    this->SetImage(hIcon);
    DestroyIcon(hIcon);
    return 0;
}
    
DWORD SButton::SetImage(HINSTANCE hInst, UINT uImage)
{
    return this->SetImage(hInst, MAKEINTRESOURCE(uImage));
}

HICON SButton::GetImage() const
{
    return (HICON)SendMessage(hwnd, BM_GETIMAGE, IMAGE_ICON, 0);
}    
    
#endif
