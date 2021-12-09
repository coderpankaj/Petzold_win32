#include<windows.h>

int main()
{
    #define GCL_HBRBACKGROUND   (-10)
    HINSTANCE hInstance;HMENU hMenu;UINT  uIDEnableItem; UINT  uEnable; static LOGFONT logfont ;
    HWND hwnd; HDC hdc; RECT rect; BOOL bul; int int1; MSG msg; void func();
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

    /* Creates a modeless dialog box from a dialog box template resource. The CreateDialog macro uses the 
       CreateDialogParam function. */
    CreateDialog (hInstance, TEXT ("ColorScrDlg"), hwnd, func) ;

    /* Determines whether a message is intended for the specified dialog box and, if it is, processes the message. */
    IsDialogMessage (hwnd, &msg);

    /* The SetScrollRange function sets the minimum and maximum scroll box positions for the specified scroll bar. */
    SetScrollRange (hwnd, SB_CTL, 0, 255, FALSE) ;

    /* The SetScrollPos function sets the position of the scroll box (thumb) in the specified scroll bar and, 
       if requested, redraws the scroll bar to reflect the new position of the scroll box. */
    SetScrollPos   (hwnd, SB_CTL, 0, FALSE) ;

    /* Sets the text of a control in a dialog box to the string representation of a specified integer value. */
    SetDlgItemInt (hwnd,  int1 + 3, int1, FALSE) ;

    /* Retrieves a handle to the specified window's parent or owner.
        To retrieve a handle to a specified ancestor, use the GetAncestor function. */
    GetParent (hwnd) ;

    /* Replaces the specified 32-bit (long) value at the specified offset into the extra class memory or 
        the WNDCLASSEX structure for the class to which the specified window belongs. */
    SetClassLong (hwnd, GCL_HBRBACKGROUND, (LONG) CreateSolidBrush ( RGB (int1,int1,int1)));

    /* SetDlgItemText : Sets the title or text of a control in a dialog box. */
    SetDlgItemText (hwnd, VK_ESCAPE, szText) ;

    /* CharUpper : Converts a character string or a single character to uppercase. 
        If the operand is a character string, the function converts the characters in place. */
    CharUpper ((TCHAR *) szText);

    /* isxdigit : Check if character is hexadecimal digit */
    isxdigit (LOWORD (szText));

    /* isdigit : Check if character is decimal digit */
    isdigit (szText);

    /* MessageBeep : Plays a waveform sound. The waveform sound for each sound type is identified by 
        an entry in the registry. */
    MessageBeep (0) ;

    /* TranslateAccelerator : Processes accelerator keys for menu commands. */
    TranslateAccelerator (hwnd, hwnd, &msg);

    /* Loads the specified accelerator table. */
    LoadAccelerators (hInstance, szText) ;

    /* wsprintf : Writes formatted data to the specified buffer. */
    wsprintf (szText, TEXT ("%s - %s"), szText, szText) ;
    
    /* SetWindowText : Changes the text of the specified window's title bar (if it has one). */
    SetWindowText (hwnd, szText) ;

    /* SendMessage : Sends the specified message to a window or windows. */
    SendMessage (hwnd, WM_COMMAND, NULL, 0);

    /* MessageBox : Displays a modal dialog box that contains a system icon, a set of buttons, and a brief 
        application-specific message, */
    MessageBox (hwnd, szText, szText, MB_YESNOCANCEL | MB_ICONQUESTION) ;

    /* The GetObject function retrieves information for the specified graphics object. */
    GetObject (GetStockObject (SYSTEM_FONT), sizeof (LOGFONT), (PTSTR) &logfont) ;

    /* The CreateFontIndirect function creates a logical font that has the specified characteristics. 
        The font can subsequently be selected as the current font for any device context. */
    CreateFontIndirect (&logfont) ;

    /* SetFocus : Sets the keyboard focus to the specified window. The window must be attached to 
        the calling thread's message queue. */
    SetFocus (hwnd) ;

    /* MoveWindow : Changes the position and dimensions of the specified window.  */
    MoveWindow (hwnd, 0, 0, LOWORD (NULL), HIWORD (NULL), TRUE) ;

    /* IsClipboardFormatAvailable : Determines whether the clipboard contains data in the specified format. */
    IsClipboardFormatAvailable (CF_TEXT);

    /* GetOpenFileName : Creates an Open dialog box that lets the user specify the drive, directory, and 
        the name of a file or set of files to be opened. */
    static OPENFILENAME ofn ;
    GetOpenFileName (&ofn);

    /* GetSaveFileName : Creates a Save dialog box that lets the user specify the drive, directory, and 
        name of a file to save. */
    GetSaveFileName (&ofn) ;

    /* IsTextUnicode : Determines if a buffer is likely to contain a form of Unicode text. */
    IsTextUnicode (szText, int1, &szText);

    /* WideCharToMultiByte : Maps a UTF-16 (wide character) string to a new character string. */
    WideCharToMultiByte (CP_ACP, 0, (PWSTR) szText, -1, szText, int1 + 2, NULL, NULL) ;

    /* lstrcpy : Copies a string to a buffer. */
    lstrcpy ((PTSTR) szText, (PTSTR) szText) ;

    /* MultiByteToWideChar : Maps a character string to a UTF-16 (wide character) string. 
        The character string is not necessarily from a multibyte character set. */
    MultiByteToWideChar (CP_ACP, 0, szText, -1, (PTSTR) szText, int1 + 1) ;

    /* WriteFile : Writes data to the specified file or input/output (I/O) device. */
    WriteFile (hwnd, szText, int1 * sizeof (TCHAR), &szText, NULL) ;

    /* GetWindowTextLength : Retrieves the length, in characters, of the specified window's title bar text 
        (if the window has a title bar). */
    GetWindowTextLength (hwnd) ;

    /* ChooseFont : Creates a Font dialog box that enables the user to choose attributes for a logical font. 
        These attributes include a font family and associated font style, a point size, effects (underline, strikeout, 
        and text color), and a script (or character set). */
    CHOOSEFONT cf ;
    ChooseFont (&cf) ;

    /* Creates a Color dialog box that enables the user to select a color. */
    static CHOOSECOLOR cc ;
    ChooseColor (&cc) ;

    return TRUE;
}