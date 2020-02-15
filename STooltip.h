#ifndef STOOLTIP_H
#define STOOLTIP_H

class STooltip : public SWindow
{
    private:
        SWindow * pParent;
        char * pszText;
        
        int maxWidth, maxHeight;
        int width, height;
        
        HFONT hFont;
        COLORREF txtColor, bkColor;
        HBRUSH hBkBrush, hTxtBrush;
        
        virtual DWORD CalculateSize();
    public:
        STooltip(SWindow * pWin);
        virtual ~STooltip();
        
        virtual DWORD SetFont(HFONT hFont);
        virtual DWORD SetTxtColor(COLORREF color);
        virtual DWORD SetBkColor(COLORREF color);
        
        virtual COLORREF GetTxtColor();
        virtual COLORREF GetBkColor();
        
        virtual DWORD SetText(const char * pszBuffer);
        virtual DWORD GetText(char * pszBuffer, DWORD dwSize);
        
        virtual DWORD SetPosition(int x, int y, int cx, int cy);
        virtual DWORD SetMaxWidth(int mWidth);
        virtual DWORD SetMaxHeight(int mHeight);
        
        virtual DWORD Show();
        virtual DWORD Hide();
        
        virtual BOOL CALLBACK OnPaint();
        virtual BOOL CALLBACK OnTimer(WORD id);
};

#endif
