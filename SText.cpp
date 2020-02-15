#ifndef STEXT_CPP
#define STEXT_CPP

#include <windows.h>
#include "SApp.h"
#include "SWindow.h"
#include "SText.h"

SText::SText(SWindow * pWin, UINT uStyle):
SWindow(pWin->GetSApp(), "static", pWin->GetHwnd(), 0, WS_CHILD | uStyle, 0)
{
    pWin->AddChild(this);
}

SText::~SText()
{ }


STextLeft::STextLeft(SWindow * pWin):
SText(pWin, SS_LEFT)
{ }

STextLeft::~STextLeft()
{ }

STextCenter::STextCenter(SWindow * pWin):
SText(pWin, SS_CENTER)
{ }

STextCenter::~STextCenter()
{ }

STextRight::STextRight(SWindow * pWin):
SText(pWin, SS_RIGHT)
{ }

STextRight::~STextRight()
{ }


#endif
