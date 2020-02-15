#ifndef SCHECKBOX_CPP
#define SCHECKBOX_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SButton.h"
#include "SCheckbox.h"

SCheckbox::SCheckbox(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SButton(pWin, uStyle | BS_AUTOCHECKBOX, uId, uExStyle)
{ }

SCheckbox::~SCheckbox()
{ }

BOOL SCheckbox::IsChecked()
{
    return (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;
}

DWORD SCheckbox::SetChecked(BOOL isCheck)
{
    WPARAM bState = (isCheck) ? BST_CHECKED : BST_UNCHECKED;
    SendMessage(hwnd, BM_SETCHECK, bState, 0);
    return 0;
}

#endif
