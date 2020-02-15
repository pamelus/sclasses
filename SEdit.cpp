#ifndef SEDIT_CPP
#define SEDIT_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SEdit.h"

SEdit::SEdit(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SWindow(pWin->GetSApp(), "edit", pWin->GetHwnd(), uId, WS_CHILD | uStyle, WS_EX_CLIENTEDGE | uExStyle)
{
    pWin->AddChild(this);
}

SEdit::~SEdit()
{ }

DWORD SEdit::AddText(char * pszText)
{
    this->ToEnd();
    this->ReplaceSelection(pszText);
    return 0;
}

DWORD SEdit::ReplaceSelection(char * pszText)
{
    SendMessage(hwnd, EM_REPLACESEL, TRUE, (LPARAM)pszText);
    return 0;
}    
    
DWORD SEdit::Undo()
{
    SendMessage(hwnd, WM_UNDO, 0, 0);
    return 0;
}
    
DWORD SEdit::Cut()
{
    SendMessage(hwnd, WM_CUT, 0, 0);
    return 0;
}
    
DWORD SEdit::Paste()
{
    SendMessage(hwnd, WM_PASTE, 0, 0);
    return 0;
}
    
DWORD SEdit::Copy()
{
    SendMessage(hwnd, WM_COPY, 0, 0);
    return 0;
}
    
DWORD SEdit::SelectAll()
{
    this->SetSelection(0, -1);
    return 0;
}
    
DWORD SEdit::UnselectAll()
{
    this->SetSelection(-1, 0);
    return 0;
}
    
DWORD SEdit::ToBegin()
{
    this->SetSelection(0, 0);
    return 0;
}    

DWORD SEdit::ToEnd()
{
    this->SetSelection(-1, -1);
    return 0;
}

    
DWORD SEdit::SetTextLimit(DWORD dwLimit)
{
    SendMessage(hwnd, EM_SETLIMITTEXT, dwLimit, 0);
    return 0;
}
    
DWORD SEdit::SetLeftMargin(int cx)
{
    SendMessage(hwnd, EM_SETMARGINS, EC_LEFTMARGIN, MAKELONG(cx, 0));
    return 0;
}
    
DWORD SEdit::SetRightMargin(int cx)

{
    SendMessage(hwnd, EM_SETMARGINS, EC_RIGHTMARGIN, MAKELONG(0, cx));
    return 0;
}

DWORD SEdit::SetSelection(int iStart, int iEnd)
{
    SendMessage(hwnd, EM_SETSEL, iStart, iEnd);
    return 0;
}
    
DWORD SEdit::SetPasswordChar(char ch)
{
    SendMessage(hwnd, EM_SETPASSWORDCHAR, (UINT)ch, 0);
    return 0;
}
    
DWORD SEdit::SetCarret(int iCarret)
{
    this->SetSelection(iCarret, iCarret);
    return 0;
}
    
DWORD SEdit::SetModify(BOOL isModyfied)
{
    SendMessage(hwnd, EM_SETMODIFY, isModyfied, 0);
    return 0;
}

DWORD SEdit::GetLength() const
{
    return (SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0) + 1);
}    

DWORD SEdit::GetTextLimit() const
{
    return SendMessage(hwnd, EM_GETLIMITTEXT, 0, 0);
}
    
DWORD SEdit::GetLeftMargin() const
{
    DWORD dwMargins = SendMessage(hwnd, EM_GETMARGINS, 0, 0);
    return LOWORD(dwMargins);
}
    
DWORD SEdit::GetRightMargin() const
{
    DWORD dwMargins = SendMessage(hwnd, EM_GETMARGINS, 0, 0);
    return HIWORD(dwMargins);
}

DWORD SEdit::GetSelection(int & iStart, int & iEnd) const
{
    SendMessage(hwnd, EM_GETSEL, (WPARAM)&iStart, (LPARAM)iEnd);
    return 0;
}
    
DWORD SEdit::GetCarret() const
{
    int iStart, iEnd;
    this->GetSelection(iStart, iEnd);
    return iEnd;
}
    
BOOL SEdit::GetModify() const
{
    return (BOOL)SendMessage(hwnd, EM_GETMODIFY, 0, 0);
}    

#endif
