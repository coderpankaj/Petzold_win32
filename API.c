#include<windows.h>

int main()
{
    HINSTANCE hInstance;
    HWND hwnd;
    WNDPROC AboutDlgProc;

    /* DialogBox : Creates a modal dialog box from a dialog box template resource */
    DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc) ;
    return TRUE;
}