#ifndef SICON_H
#define SICON_H

class SIcon : public SText
{
    public:
        SIcon(SWindow * pWin);
        virtual ~SIcon();
        
        virtual DWORD SetIcon(HICON hIcon);
        virtual DWORD SetIcon(HINSTANCE hInst, const char * pszIcon);
        virtual DWORD SetIcon(HINSTANCE hInst, UINT uIcon);
        virtual HICON GetIcon() const;
};   

#endif
