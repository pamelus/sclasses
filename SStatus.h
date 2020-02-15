#ifndef SSTATUS_H
#define SSTATUS_H

class SStatus : public SWindow
{
    protected:
        int * parts;
        int nParts;
        int iPart;
    public:
        SStatus(SWindow * pWin);
        virtual ~SStatus();
        
        virtual DWORD BeginItem(int iCount);
        virtual DWORD AddItem(int cx);
        virtual DWORD EndItem();
        
        virtual DWORD Autosize();
        
        virtual DWORD SetItemText(int iItem, char * pszText);
        virtual DWORD SetItemImage(int iItem, HICON hIcon);
        virtual DWORD SetItemImage(int iItem, HINSTANCE hInst, char * pszImage);
        virtual DWORD SetItemImage(int iItem, HINSTANCE hInst, UINT uImage);
        
        virtual DWORD GetItemText(int iItem, char * pszText, DWORD dwSize) const;
        virtual HICON GetItemImage(int iItem) const;
};    

#endif
