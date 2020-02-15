// Klasa bazowa dla WSZYSTKICH okien (buttonów, editów, listboxów itp

#ifndef SWINDOW_H
#define SWINDOW_H

class SWindow
{
    private:
        LRESULT value;
    protected:
        SApp * sApp;
        
        SWindow ** pChild;
        DWORD nChild;
        
        WNDPROC wProc;
        HWND hwnd;
    public:
        // Konstruktor i destruktor
        SWindow(SApp * sMyApp, const char * pszClass, HWND hParent = NULL, UINT id = 0, UINT style = 0, UINT exStyle = 0);
        virtual ~SWindow();
        
        // Metody wirtualne
        
        virtual DWORD Show(int nShow = SW_SHOW) const; // Wyœwietla okno
        
        virtual DWORD SetPosition(int x, int y, int cx, int cy);
        virtual DWORD SetPosition(const RECT * rect);
        virtual DWORD SetText(const char * pszText);
        virtual DWORD SetCaption(const char * pszText);
        virtual DWORD SetFont(HFONT hFont);
        virtual DWORD SetIcon(HICON hIcon);
        virtual DWORD SetIcon(HINSTANCE hInst, const char * pszIcon);
        virtual DWORD SetIcon(HINSTANCE hInst, UINT uIcon);
        virtual DWORD SetStyle(UINT uStyle);
        
        virtual DWORD GetPosition(int * x, int * y, int * cx, int * cy) const;
        virtual DWORD GetPosition(RECT * rect) const;
        virtual DWORD GetClientArea(int * cx, int * cy) const;
        virtual DWORD GetClientArea(RECT * rect) const;
        virtual DWORD GetText(char * pszText, DWORD dwSize) const;
        virtual DWORD GetCaption(char * pszText, DWORD dwSize) const;
        virtual DWORD GetStyle() const;
        virtual HICON GetIconBig() const;
        virtual HICON GetIconSmall() const;
        virtual HFONT GetFont() const;
        
        virtual BOOL CALLBACK OnEvent(UINT message, WPARAM wParam, LPARAM lParam);
        virtual BOOL CALLBACK OnClose();
        virtual BOOL CALLBACK OnPaint();
        virtual BOOL CALLBACK OnResize(int cx, int cy);
        virtual BOOL CALLBACK OnTooltip();
        virtual BOOL CALLBACK OnTimer(WORD id);
        virtual BOOL CALLBACK OnCommand(WORD loword, WORD hiword, LPARAM lParam);
        
        virtual LRESULT DoCommand(WORD loword, WORD hiword, LPARAM lParam);
        virtual LRESULT DoUpdate();
        virtual LRESULT DoEvent(UINT message, WPARAM wParam, LPARAM lParam);
        
        // Metody w³aœciwe WY£¥CZNIE dla klasy SWindow
        
        LRESULT CALLBACK InclassWindowProc(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);
        
        LRESULT SetReturnValue(LRESULT nValue);
        LRESULT GetReturnValue() const;
        
        HWND GetHwnd() const;
        SApp * GetSApp() const;
        
        DWORD AddChild(SWindow * sChild);
};

#endif
