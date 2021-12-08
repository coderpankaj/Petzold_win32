#include<windows.h>

int main()
{
    HINSTANCE hInstance;HMENU hMenu;UINT  uIDEnableItem; UINT  uEnable;
    HWND hwnd; HDC hdc; RECT rect; BOOL bul; int int1;
    WNDPROC AboutDlgProc; HBRUSH hBrush; COLORREF crColor; TCHAR szText[20];

    /* EnableMenuItem: Enables, disables, or grays the specified menu item. */
    EnableMenuItem(hMenu, uIDEnableItem, uEnable);

    /* DialogBox : Creates a modal dialog box from a dialog box template resource */
    DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc) ;

    /* The GetDC function retrieves a handle to a device context (DC) for the client area of a 
        specified window or for the entire screen. */
    hdc = GetDC (hwnd) ;

    /* GetClientRect : Retrieves the coordinates of a window's client area */
    bul = GetClientRect (hwnd, &rect) ;

    /* The CreateSolidBrush function creates a logical brush that has the specified solid color. */
    hBrush = CreateSolidBrush (crColor[&int1]) ;

    /* The SelectObject function selects an object into the specified device context (DC). 
        The new object replaces the previous object of the same type.*/
    hBrush = (HBRUSH) SelectObject (hdc, hBrush) ;

    /* The Rectangle function draws a rectangle. The rectangle is outlined by using the current pen 
        and filled by using the current brush. */
    Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom) ;

    /* The Ellipse function draws an ellipse. The center of the ellipse is the center of the specified bounding rectangle.
       The ellipse is outlined by using the current pen and is filled by using the current brush.*/
    Ellipse   (hdc, rect.left, rect.top, rect.right, rect.bottom) ;
     
    /* The DeleteObject function deletes a logical pen, brush, font, bitmap, region, or palette, freeing all 
        system resources associated with the object. After the object is deleted, the specified handle is no longer valid. */
    DeleteObject (SelectObject (hdc, hBrush)) ;

    /* The ReleaseDC function releases a device context (DC), freeing it for use by other applications.
        The effect of the ReleaseDC function depends on the type of DC. It frees only common and window DCs.
        It has no effect on class or private DCs.*/
    ReleaseDC (hwnd, hdc) ;

    /* The InvalidateRect function adds a rectangle to the specified window's update region. 
        The update region represents the portion of the window's client area that must be redrawn.*/
    InvalidateRect (hwnd, NULL, TRUE) ;

    /* The UpdateWindow function updates the client area of the specified window by sending a WM_PAINT message to 
        the window if the window's update region is not empty.*/
    UpdateWindow (hwnd) ;

    /* CheckRadioButton : Adds a check mark to (checks) a specified radio button in a group and removes a check mark 
        from (clears) all other radio buttons in the group.*/
    CheckRadioButton (hwnd, int1, int1, int1) ;

    /* GetDlgItem : Retrieves a handle to a control in the specified dialog box.*/
    hwnd = GetDlgItem (hwnd, int1) ;

    /* EndDialog : Destroys a modal dialog box, causing the system to end any processing for the dialog box.*/
    EndDialog (hwnd, TRUE) ;

    /* GetWindowText : Copies the text of the specified window's title bar (if it has one) into a buffer.*/
    GetWindowText (hwnd, szText, sizeof (szText)) ;

    /* The SetBkColor function sets the current background color to the specified color value */
    SetBkColor (hdc, GetSysColor (COLOR_WINDOW)) ;

    /* The SetTextColor function sets the text color for the specified device context to the specified color. */
    SetTextColor (hdc, GetSysColor (COLOR_WINDOWTEXT)) ;

    /* The DrawText function draws formatted text in the specified rectangle. It formats the text according to 
       the specified method (expanding tabs, justifying characters, breaking lines, and so forth). */
    DrawText (hdc, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

    /* Retrieves information about the specified window. The function also retrieves the 32-bit (DWORD) value 
       at the specified offset into the extra window memory. */
    GetWindowLong (hwnd, GWL_ID);

    
    return TRUE;
}