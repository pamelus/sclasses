#ifndef SLISTVIEW_H
#define SLISTVIEW_H

#define ALIGN_LEFT      LVCFMT_LEFT
#define ALIGN_CENTER    LVCFMT_CENTER
#define ALIGN_RIGHT     LVCFMT_RIGHT

class SListview : public SWindow
{
    protected:
        HIMAGELIST hImageListBig;
        HIMAGELIST hImageListSmall;
        int nColumns;
    public:
        SListview(SWindow * sWin, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0);
        virtual ~SListview();
        
        virtual DWORD SetStyle(DWORD dwStyle);
        
        virtual DWORD AddColumn(char * pszText, int cx);
        virtual DWORD DeleteColumn(int iColumn);
        virtual DWORD SetColumnText(int iColumn, char * pszText);
        virtual DWORD SetColumnWidth(int iColumn, int cx);
        virtual DWORD SetColumnAligment(int iColumn, int nAlign);
        virtual DWORD SetColumnImage(int iColumn, int iImage);
        virtual DWORD GetColumnText(int iColumn, char * pszText, DWORD dwSize) const;
        virtual DWORD GetColumnWidth(int iColumn) const;
        virtual DWORD GetColumnAligment(int iColumn) const;
        virtual DWORD GetColumnImage(int iColumn) const;
        
        virtual DWORD BeginImage();
        virtual DWORD AddImage(HICON hIcon);
        virtual DWORD AddImage(HINSTANCE hInst, UINT uImage);
        virtual DWORD AddImage(HINSTANCE hInst, char * pszImage);
        virtual DWORD EndImage();
        
        virtual DWORD AddItem(int iImage, LPARAM lParam = 0);
        virtual DWORD DeleteAllItems();
        virtual DWORD DeleteItem(DWORD iItem);
        virtual DWORD SetItemText(DWORD iItem, int iColumn, char * pszText);
        virtual DWORD SetItemImage(DWORD iItem, int iImage);
        virtual DWORD GetItemText(DWORD iItem, int iColumn, char * pszText, DWORD dwSize) const;
        virtual DWORD GetItemImage(DWORD iItem) const;
        
        virtual DWORD SetSelection(DWORD iItem);
        virtual DWORD GetSelection() const;
        virtual DWORD GetItemCount() const;
        
        virtual DWORD SetTextColor(COLORREF cColor);
        virtual DWORD SetBkColor(COLORREF cColor);
        
        virtual COLORREF GetTextColor() const;
        virtual COLORREF GetBkColor() const;
        
        virtual DWORD GetItemRect(DWORD iItem, RECT * pRect) const;
};    

#endif
