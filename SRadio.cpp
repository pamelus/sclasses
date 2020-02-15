#ifndef SRADIO_CPP
#define SRADIO_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SButton.h"
#include "SRadio.h"

SRadio::SRadio(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SButton(pWin, uStyle | BS_RADIOBUTTON, uId, uExStyle)
{ }

SRadio::~SRadio()
{ }

BOOL SRadio::IsChecked()
{
    return (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;
}

DWORD SRadio::SetChecked(BOOL isCheck)
{
    WPARAM bState = (isCheck) ? BST_CHECKED : BST_UNCHECKED;
    SendMessage(hwnd, BM_SETCHECK, bState, 0);
    return 0;
}

#endif
