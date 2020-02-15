#ifndef SAPP_H
#define SAPP_H

// Klasa g�owna odpowiadaj�ca programowi oraz p�tla steruj�ca
// wszystkimi oknami w programie

LRESULT CALLBACK ClassWindowProc(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

class SApp
{
    private:
        HINSTANCE hThis;
        HACCEL hAccel;
        
        HWND hMainWindow;
        HWND hMdiWindow;
    public:
        SApp();
        SApp(HINSTANCE hNewThis);
        ~SApp();
        
        DWORD SetAccel(HACCEL hNewAccel); // Ustawia tablic� skr�t�w klawiszowych
        DWORD SetMainWindow(HWND hNewMain); // Ustawia okno g�owne
        DWORD SetMdiWindow(HWND hNewMdi); // Ustawia okno MDI
        
        HINSTANCE GetInstance() const; // Pobiera uchwyt programu
        
        DWORD Loop(); // P�tla g�owna programu
        DWORD Register(); // Rejestruje klasy okien
};

#endif
