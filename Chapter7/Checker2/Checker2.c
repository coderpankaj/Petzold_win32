/*-------------------------------------------------
   CHECKER2.C -- Mouse Hit-Test Demo Program No. 2
                 Pankaj Patil, 2021
  -------------------------------------------------*/

#include <windows.h>

#define DIVISIONS 7

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Checker2") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("Checker2 Mouse Hit-Test Demo"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL fState[DIVISIONS][DIVISIONS] ;
     static int  cxBlock, cyBlock ;
     HDC         hdc ;
     int         x, y ;
     PAINTSTRUCT ps ;
     POINT       point ;
     RECT        rect ;
     
     switch (message)
     {
     case WM_SIZE :
          cxBlock = LOWORD (lParam) / DIVISIONS ;
          cyBlock = HIWORD (lParam) / DIVISIONS ;
          return 0 ;
          
     case WM_SETFOCUS :
          ShowCursor (TRUE) ;
          return 0 ;
          
     case WM_KILLFOCUS :
          ShowCursor (FALSE) ;
          return 0 ;
          
     case WM_KEYDOWN :
          GetCursorPos (&point) ;
          ScreenToClient (hwnd, &point) ;
          
          x = max (0, min (DIVISIONS - 1, point.x / cxBlock)) ;
          y = max (0, min (DIVISIONS - 1, point.y / cyBlock)) ;
          
          switch (wParam)
          {
          case VK_UP :
               y-- ;
               break ;
               
          case VK_DOWN :
               y++ ;
               break ;
               
          case VK_LEFT :
               x-- ;
               break ;
               
          case VK_RIGHT :
               x++ ;
               break ;
               
          case VK_HOME :
               x = y = 0 ;
               break ;
               
          case VK_END :
               x = y = DIVISIONS - 1 ;
               break ;
               
          case VK_RETURN :
          case VK_SPACE :
               SendMessage (hwnd, WM_LBUTTONDOWN, MK_LBUTTON,
                            MAKELONG (x * cxBlock, y * cyBlock)) ;
               break ;
          }
          x = (x + DIVISIONS) % DIVISIONS ;
          y = (y + DIVISIONS) % DIVISIONS ;
          
          point.x = x * cxBlock + cxBlock / 2 ;
          point.y = y * cyBlock + cyBlock / 2 ;
          
          ClientToScreen (hwnd, &point) ;
          SetCursorPos (point.x, point.y) ;
          return 0 ;
          
     case WM_LBUTTONDOWN :
          x = LOWORD (lParam) / cxBlock ;
          y = HIWORD (lParam) / cyBlock ;
          
          if (x < DIVISIONS && y < DIVISIONS)
          {
               fState[x][y] ^= 1 ;
               
               rect.left   = x * cxBlock ;
               rect.top    = y * cyBlock ;
               rect.right  = (x + 1) * cxBlock ;
               rect.bottom = (y + 1) * cyBlock ;
               
               InvalidateRect (hwnd, &rect, FALSE) ;
          }
          else
               MessageBeep (0) ;
          return 0 ;
          
     case WM_PAINT :
          hdc = BeginPaint (hwnd, &ps) ;
          //SetBkColor(hdc, BLACK_BRUSH);
          HPEN hRedPen = CreatePen(PS_SOLID,0,RGB(255,0,0));
          HPEN hWhitePen = CreatePen(PS_SOLID,0,RGB(255,255,255));
          HBRUSH hBlackBrush = CreateSolidBrush(RGB(0,0,0));
          SelectObject(hdc, hBlackBrush);                        // Color inside of Rectangles

          for (x = 0 ; x < DIVISIONS ; x++)
          for (y = 0 ; y < DIVISIONS ; y++)
          {
               SelectObject(hdc, hWhitePen);                     // Color border of Rectangles
               Rectangle (hdc, x * cxBlock, y * cyBlock,
                          (x + 1) * cxBlock, (y + 1) * cyBlock) ;
                    
               if (fState [x][y])
               {
                    SelectObject(hdc,hRedPen);                   // Color cross in Rectangles
                    MoveToEx (hdc,  x   *cxBlock,  y   *cyBlock, NULL) ;
                    LineTo   (hdc, (x+1)*cxBlock, (y+1)*cyBlock) ;
                    MoveToEx (hdc,  x   *cxBlock, (y+1)*cyBlock, NULL) ;
                    LineTo   (hdc, (x+1)*cxBlock,  y   *cyBlock) ;
               }
          }

          DeleteObject(hRedPen);
          DeleteObject(hWhitePen);
          DeleteObject(hBlackBrush);
          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
