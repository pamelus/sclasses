#ifndef SGROUPBOX_CPP
#define SGROUPBOX_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SButton.h"
#include "SGroupbox.h"

SGroupbox::SGroupbox(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SButton(pWin, uStyle | BS_GROUPBOX, uId, uExStyle)
{ }

SGroupbox::~SGroupbox()
{ }

#endif
