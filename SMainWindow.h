// Klasa okna g��wnego aplikacji. Zazwyczaj b�dzie nadpisywana

#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

class SMainWindow : public SWindow
{
    public:
        SMainWindow(SApp * sApp, UINT style = WS_OVERLAPPEDWINDOW, UINT exStyle = 0);
        virtual ~SMainWindow();
        
        virtual BOOL CALLBACK OnClose();
};

#endif
