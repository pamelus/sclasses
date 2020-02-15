#ifndef SEDIT_H
#define SEDIT_H

class SEdit : public SWindow
{
    public:
        SEdit(SWindow * pWin, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0);
        virtual ~SEdit();
        
        virtual DWORD AddText(char * pszText);
        virtual DWORD ReplaceSelection(char * pszText);
        
        virtual DWORD Undo();
        virtual DWORD Cut();
        virtual DWORD Paste();
        virtual DWORD Copy();
        
        virtual DWORD SelectAll();
        virtual DWORD UnselectAll();
        virtual DWORD ToBegin();
        virtual DWORD ToEnd();
        
        virtual DWORD SetTextLimit(DWORD dwLimit);
        virtual DWORD SetLeftMargin(int cx);
        virtual DWORD SetRightMargin(int cx);
        virtual DWORD SetSelection(int iStart, int iEnd);
        virtual DWORD SetPasswordChar(char ch);
        virtual DWORD SetCarret(int iCarret);
        virtual DWORD SetModify(BOOL isModyfied);
        
        virtual DWORD GetLength() const;
        virtual DWORD GetTextLimit() const;
        virtual DWORD GetLeftMargin() const;
        virtual DWORD GetRightMargin() const;
        virtual DWORD GetSelection(int & iStart, int & iEnd) const;
        virtual DWORD GetCarret() const;
        virtual BOOL GetModify() const;
};
    
#endif
