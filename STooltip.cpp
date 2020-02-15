#ifndef STOOLTIP_CPP
#define STOOLTIP_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "STooltip.h"

STooltip::STooltip(SWindow * pWin):
SWindow(pWin->GetSApp(), "wcTooltipClass", pWin->GetHwnd(), 0, WS_POPUP),
pParent(pWin),
maxWidth(0), maxHeight(0), width(0), height(0),
txtColor(0x000000), bkColor(0xFFFFFF),
pszText(NULL)
{
    SetTimer(hwnd, 100, 2000, NULL);
}

STooltip::~STooltip()
{
    if(pszText)
        delete [] pszText;
}

DWORD STooltip::SetFont(HFONT hFont)
{
    HDC hdc = GetDC(hwnd);
    SelectObject(hdc, hFont);
    ReleaseDC(hwnd, hdc);
    return 0;
}

DWORD STooltip::SetTxtColor(COLORREF color)
{
    txtColor = color;
    HDC hdc = GetDC(hwnd);
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    ReleaseDC(hwnd, hdc);
    return 0;
}

DWORD STooltip::SetBkColor(COLORREF color)
{
    bkColor = color;
    return 0;
}

COLORREF STooltip::GetTxtColor()
{
    return txtColor;
}

COLORREF STooltip::GetBkColor()
{
    return bkColor;
}

DWORD STooltip::SetText(const char * pszBuffer)
{
    if(pszText)
        delete [] pszText;
    pszText = new char[lstrlen(pszBuffer) + 1];
    lstrcpy(pszText, pszBuffer);
    return 0;
}

DWORD STooltip::GetText(char * pszBuffer, DWORD dwSize)
{
    if(pszText)
        lstrcpyn(pszBuffer, pszText, dwSize);
    else
        lstrcpyn(pszBuffer, "", dwSize);
    return 0;
}

DWORD STooltip::SetPosition(int x, int y, int cx, int cy)
{
    return 0;
}

DWORD STooltip::SetMaxWidth(int mWidth)
{
    maxWidth = mWidth;
    return 0;
}

DWORD STooltip::SetMaxHeight(int mHeight)
{
    maxHeight = mHeight;
    return 0;
}

DWORD STooltip::Show()
{
    this->CalculateSize();
    POINT pc; GetCursorPos(&pc);
    MoveWindow(hwnd, pc.x+10, pc.y+10, width, height, false);
    ShowWindow(hwnd, SW_SHOW);
    
    char pszBuffer[256]; wsprintf(pszBuffer, "%dx%d, %d, %d", pc.x+10, pc.y + 10, width, height);
    MessageBox(0, pszBuffer, 0, 0);
    return 0;
}

DWORD STooltip::Hide()
{
    ShowWindow(hwnd, SW_HIDE);
    return 0;
}

BOOL CALLBACK STooltip::OnPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
      
    RECT rcText;
    pParent->GetPosition(&rcText);
    
    rcText.left += 5; rcText.top  += 5;
    rcText.right -= 5; rcText.bottom -= 5;
    
    DrawText(hdc, pszText, lstrlen(pszText), &rcText, DT_LEFT | DT_WORDBREAK);
    
    EndPaint(hwnd, &ps);
    return 0;
}

BOOL CALLBACK STooltip::OnTimer(WORD id)
{
    switch(id)
    {
        case 100:
            pParent->OnTooltip();
            break;
    }
    return TRUE;
}

DWORD STooltip::CalculateSize()
{
    width = height = 0;
    if(maxWidth < 10) maxWidth = 100;
    HDC hdc = GetDC(hwnd);
        SIZE size;
        long nLines, iLineHeight;
        long iLastSpace = 0;
        long iLastBreak = 0;
        
        GetTextExtentPoint32(hdc, pszText, lstrlen(pszText), &size);
        nLines = 1; iLineHeight = size.cy;
        
        for(long i = 0; i < lstrlen(pszText); i++)
        {
            if(pszText[i] == ' ') iLastSpace = i;
            
            GetTextExtentPoint(hdc, &pszText[iLastBreak], i - iLastBreak, &size);
            if(size.cx >= maxWidth)
            {
                if(iLastSpace > iLastBreak)
                {
                    GetTextExtentPoint(hdc, &pszText[iLastBreak], iLastSpace - iLastBreak, &size);
                    if(size.cx > width)
                        width = size.cx;
                    iLastBreak = iLastSpace + 1;
                }
                else
                {
                    if(size.cx > width)
                        width = size.cx;
                    iLastBreak = i;
                }
                nLines++;
            }
        }
    height = nLines * iLineHeight + 10; width += 10;
    ReleaseDC(hwnd, hdc);
    return 0;
}

#endif
