#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <stdio.h>
#include "SApp.h"
#include "SWindow.h"
#include "SMainWindow.h"
#include "SButton.h"
#include "Scheckbox.h"
#include "SRadio.h"
#include "SToolbar.h"
#include "SText.h"
#include "STooltip.h"
#include "SListview.h"

char pszFile1[1024];
char pszFile2[1024];

class MyWindow : public SMainWindow
{
    public:
        MyWindow(SApp * sApp, UINT style): SMainWindow(sApp, style) { }
        ~MyWindow() { }
        
        BOOL CALLBACK OnCommand(WORD loword, WORD hiword, LPARAM lParam) { if(loword == 101) { ShellExecute(HWND_DESKTOP, "open", pszFile1, NULL, NULL, SW_SHOW); return TRUE; } else if(loword == 102) { ShellExecute(HWND_DESKTOP, "open", pszFile2, NULL, NULL, SW_SHOW); return TRUE; } else return FALSE; }
};

void Validate(char * pszBuffer)
{
    for(int i = 0; i < lstrlen(pszBuffer); i++)
        if(pszBuffer[i] == '\n') pszBuffer[i] = 0;
}

int WINAPI WinMain(HINSTANCE hThis, HINSTANCE hPrev, char * pszCmd, int nShow)
{
    SApp sApp(hThis);
    sApp.Register();
    
    // Okno g³ówne
    
    MyWindow main(&sApp, WS_CAPTION | WS_SYSMENU);
    main.SetIcon(hThis, "A");
    main.SetCaption("Starter");
    
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);
    int width = 300;
    int height = 230;
    main.SetPosition(cx / 2 - width / 2, cy / 2 - height / 2, width, height);
    
    SButton button1(&main, 0, 101);
    SButton button2(&main, 0, 102);
    
    RECT rect; main.GetClientArea(&rect);
    
    button1.SetPosition(rect.left+10, rect.top+10, rect.right - rect.left - 20, 40);
    button1.SetText("Prezentacja 1 / Presentation 1");
    
    button2.SetPosition(rect.left+10, rect.top+60, rect.right - rect.left - 20, 40);
    button2.SetText("Prezentacja 2 / Presentation 2");
    
    char pszFolder[1024];
    GetModuleFileName(hThis, pszFolder, 1024);
    
    PathRemoveFileSpec(pszFolder);
    
    char pszBuffer[1024]; lstrcpy(pszBuffer, pszFolder);
    PathAppend(pszBuffer, "autorun.conf");
    
    FILE * stream = fopen(pszBuffer, "r");
    
    fgets(pszBuffer, 1024, stream);
    Validate(pszBuffer);
    lstrcpy(pszFile1, pszFolder);
    PathAppend(pszFile1, pszBuffer);
    
    fgets(pszBuffer, 1024, stream);
    Validate(pszBuffer);
    lstrcpy(pszFile2, pszFolder);
    PathAppend(pszFile2, pszBuffer);
    
    fclose(stream);
    
    main.Show();
    return sApp.Loop();
}    
