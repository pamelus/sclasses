#ifndef SPROGRESS_CPP
#define SPROGRESS_CPP
#define _WIN32_IE               0x0500

#include <windows.h>
#include <commctrl.h>
#include "SApp.h"
#include "SWindow.h"
#include "SProgress.h"

SProgress::SProgress(SWindow * pWin):
SWindow(pWin->GetSApp(), PROGRESS_CLASS, pWin->GetHwnd(), 0, WS_CHILD)
{
    pWin->AddChild(this);
    SendMessage(hwnd, PBM_SETSTEP, 1, 0);
}
    
SProgress::~SProgress()
{ }

DWORD SProgress::SetRange(DWORD dwRange)
{
    SendMessage(hwnd, PBM_SETRANGE32, 0, dwRange);
    return 0;
}
    
DWORD SProgress::MoveTo(DWORD iPos)
{
    SendMessage(hwnd, PBM_SETPOS, iPos, 0);
    return 0;
}
    
DWORD SProgress::Move(DWORD iMove)
{
    SendMessage(hwnd, PBM_DELTAPOS, iMove, 0);
    return 0;
}
    
DWORD SProgress::StepIt()
{
    SendMessage(hwnd, PBM_STEPIT, 0, 0);
    return 0;
}    

DWORD SProgress::GetRange() const
{
    return (DWORD)SendMessage(hwnd, PBM_GETRANGE, FALSE, (LPARAM)NULL);
}
    
DWORD SProgress::GetCurrentPosition() const
{
    return (DWORD)SendMessage(hwnd, PBM_GETPOS, 0, 0);
}    

#endif
