#ifndef SSTATUS_CPP
#define SSTATUS_CPP
#define _WIN32_IE               0x0500

#include <windows.h>
#include <commctrl.h>
#include "SApp.h"
#include "SWindow.h"
#include "SStatus.h"

SStatus::SStatus(SWindow * pWin):
SWindow(pWin->GetSApp(), STATUSCLASSNAME, pWin->GetHwnd(), 0, WS_CHILD | SBARS_SIZEGRIP),
parts(NULL), nParts(0), iPart(0)
{
    pWin->AddChild(this);
}
    
SStatus::~SStatus()
{
    if(parts)
        delete [] parts;
    for(int i = 0; i < nParts; i++)
    {
        HICON hIcon = this->GetItemImage(i);
        if(hIcon)
            DestroyIcon(hIcon);
    }    
}
    
DWORD SStatus::BeginItem(int iCount)
{
    if(parts)
        delete [] parts;
    nParts = iCount; iPart = 0;
    parts = new int[nParts];
    return 0;
}
    
DWORD SStatus::AddItem(int cx)
{
    if(iPart < nParts)
    {
        parts[iPart] = cx;
        iPart++;
    }    
    return 0;
}
    
DWORD SStatus::EndItem()
{
    SendMessage(hwnd, SB_SETPARTS, nParts, (LPARAM)parts);
    return 0;
}

DWORD SStatus::Autosize()
{
    MoveWindow(hwnd, 0, 0, 0, 0, false);
    return 0;
}    

DWORD SStatus::SetItemText(int iItem, char * pszText)
{
    SendMessage(hwnd, SB_SETTEXT, iItem, (LPARAM)pszText);
    return 0;
}
    
DWORD SStatus::SetItemImage(int iItem, HICON hIcon)
{
    HICON hOldIcon = this->GetItemImage(iItem);
    if(hOldIcon) DestroyIcon(hOldIcon);
    SendMessage(hwnd, SB_SETICON, iItem, (LPARAM)hIcon);
    return 0;
}
    
DWORD SStatus::SetItemImage(int iItem, HINSTANCE hInst, char * pszImage)
{
    HICON hIcon = LoadIcon(hInst, pszImage);
    this->SetItemImage(iItem, hIcon);
    DestroyIcon(hIcon);
    return 0;
}
    
DWORD SStatus::SetItemImage(int iItem, HINSTANCE hInst, UINT uImage)
{
    return this->SetItemImage(iItem, hInst, MAKEINTRESOURCE(uImage));
}
    
DWORD SStatus::GetItemText(int iItem, char * pszText, DWORD dwSize) const
{
    DWORD dwResult = SendMessage(hwnd, SB_GETTEXT, iItem, 0);
    char * pszBuffer = new char[LOWORD(dwResult)];
    SendMessage(hwnd, SB_GETTEXT, iItem, (LPARAM)pszBuffer);
    lstrcpyn(pszText, pszBuffer, dwSize);
    delete [] pszBuffer;
    return 0;
}
    
HICON SStatus::GetItemImage(int iItem) const
{
    return (HICON)SendMessage(hwnd, SB_GETICON, iItem, 0);
}    

#endif
