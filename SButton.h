// Klasa prostego przycisku

#ifndef SBUTTON_H
#define SBUTTON_H

class SButton : public SWindow
{
    public:
        SButton(SWindow * pWin, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0); // Konstruktor - wska¿nik na okno - rodzica
        virtual ~SButton();
        
        virtual DWORD Click();
        virtual DWORD SetImage(HICON hIcon);
        virtual DWORD SetImage(HINSTANCE hInst, char * pszImage);
        virtual DWORD SetImage(HINSTANCE hInst, UINT uImage);
        virtual HICON GetImage() const;
        
};

#endif
