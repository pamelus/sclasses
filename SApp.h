#ifndef SAPP_H
#define SAPP_H

// Klasa g³owna odpowiadaj¹ca programowi oraz pêtla steruj¹ca
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
        
        DWORD SetAccel(HACCEL hNewAccel); // Ustawia tablicê skrótów klawiszowych
        DWORD SetMainWindow(HWND hNewMain); // Ustawia okno g³owne
        DWORD SetMdiWindow(HWND hNewMdi); // Ustawia okno MDI
        
        HINSTANCE GetInstance() const; // Pobiera uchwyt programu
        
        DWORD Loop(); // Pêtla g³owna programu
        DWORD Register(); // Rejestruje klasy okien
};

#endif
