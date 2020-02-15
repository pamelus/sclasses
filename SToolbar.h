#ifndef STOOLBAR_H
#define STOOLBAR_H

class SToolbar : public SWindow
{
    protected:
        HIMAGELIST hImageList;
        TBBUTTON * buttons;
        int nButtons; int iButton;
    public:
        SToolbar(SWindow * pWin);
        virtual ~SToolbar();
        
        virtual DWORD BeginImage();
        virtual DWORD AddImage(HICON hIcon);
        virtual DWORD AddImage(HINSTANCE hInst, UINT uImage);
        virtual DWORD AddImage(HINSTANCE hInst, char * pszImage);
        virtual DWORD EndImage();
        
        virtual DWORD BeginButton(int iCount);
        virtual DWORD AddButton(BYTE fsType, int iImage = -1, int iCommand = 0);
        virtual DWORD EndButton();
        
        virtual DWORD Autosize();
        
        virtual DWORD EnableButton(DWORD iCommand, BOOL isEnabled);
};    

#endif
