#ifndef STOOLBAR_CPP
#define STOOLBAR_CPP
#define _WIN32_IE               0x0500
#define TB_SETIMAGELIST         (WM_USER + 48)

#include <windows.h>
#include <commctrl.h>
#include "SApp.h"
#include "SWindow.h"
#include "SToolbar.h"

SToolbar::SToolbar(SWindow * pWin):
SWindow(pWin->GetSApp(), TOOLBARCLASSNAME, pWin->GetHwnd(), 0, WS_CHILD | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS),
buttons(NULL), nButtons(0), iButton(0), hImageList(NULL)
{
    pWin->AddChild(this);
}
    
SToolbar::~SToolbar()
{
    if(hImageList)
        ImageList_Destroy(hImageList);
    if(buttons)
        delete [] buttons;
}

DWORD SToolbar::BeginImage()
{
    if(hImageList) ImageList_Destroy(hImageList);
    hImageList = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR16, 1, 1);
    return 0;
}

DWORD SToolbar::AddImage(HICON hIcon)
{
    ImageList_AddIcon(hImageList, hIcon);
    return 0;
}

DWORD SToolbar::AddImage(HINSTANCE hInst, UINT uImage)
{
    return this->AddImage(hInst, MAKEINTRESOURCE(uImage));
}
    
DWORD SToolbar::AddImage(HINSTANCE hInst, char * pszImage)
{
    HICON hIcon = LoadIcon(hInst, pszImage);
    this->AddImage(hIcon);
    DestroyIcon(hIcon);
    return 0;
}    

DWORD SToolbar::EndImage()
{
    SendMessage(hwnd, TB_SETIMAGELIST, 0, (LPARAM)hImageList);
    return 0;
}
    
DWORD SToolbar::BeginButton(int iCount)
{
    if(buttons) delete [] buttons;
    nButtons = iCount; iButton = 0;
    buttons = new TBBUTTON[nButtons];
    ZeroMemory(buttons, nButtons * sizeof(TBBUTTON));
    return 0;
}
    
DWORD SToolbar::AddButton(BYTE fsType, int iImage, int iCommand)
{
    if(iButton < nButtons)
    {
        buttons[iButton].iBitmap = iImage;
        buttons[iButton].idCommand = iCommand;
        buttons[iButton].fsStyle = fsType;
        buttons[iButton].fsState = TBSTATE_ENABLED;
        iButton++;
    }
    return 0;
}
    
DWORD SToolbar::EndButton()
{
    SendMessage(hwnd, TB_ADDBUTTONS, nButtons, (LPARAM)buttons);
    return 0;
}
    
DWORD SToolbar::Autosize()
{
    SendMessage(hwnd, TB_AUTOSIZE, 0, 0);
    return 0;
}
    
DWORD SToolbar::EnableButton(DWORD iCommand, BOOL isEnabled)
{
    SendMessage(hwnd, TB_ENABLEBUTTON, iCommand, MAKELONG(isEnabled, 0));
    return 0;
}    

#endif
