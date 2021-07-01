/*---------------------------------------
   BEZIER.C -- Bezier Splines Demo
               Pankaj Patil, 2021
  ---------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Bezier") ;
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
     
     hwnd = CreateWindow (szAppName, TEXT ("Bezier Splines"),
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

void DrawBezier (HDC hdc, POINT apt[])
{
     PolyBezier (hdc, apt, 4) ;
     
     MoveToEx (hdc, apt[0].x, apt[0].y, NULL) ;
     LineTo   (hdc, apt[1].x, apt[1].y) ;
     
     MoveToEx (hdc, apt[2].x, apt[2].y, NULL) ;
     LineTo   (hdc, apt[3].x, apt[3].y) ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static POINT apt[4] ;
     HDC          hdc ;
     int          cxClient, cyClient ;
     PAINTSTRUCT  ps ;
     
     switch (message)
     {
     case WM_SIZE:
          cxClient = LOWORD (lParam) ;  // width
          cyClient = HIWORD (lParam) ;  // height
          
          apt[0].x = cxClient / 4 ;     // 6
          apt[0].y = cyClient / 2 ;     // 8
          
          apt[1].x = cxClient / 2 ;     // 12
          apt[1].y = cyClient / 4 ;     // 4
          
          apt[2].x =     cxClient / 2 ; // 12
          apt[2].y = 3 * cyClient / 4 ; // 12
          
          apt[3].x = 3 * cxClient / 4 ; // 18
          apt[3].y =     cyClient / 2 ; // 8
          
          return 0 ;

     case WM_LBUTTONDOWN:
     case WM_RBUTTONDOWN:
     case WM_MOUSEMOVE:
          if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
          {
               hdc = GetDC (hwnd) ;
               
               //SelectObject (hdc, CreatePen(BS_SOLID,0,RGB(0,255,0))) ;  //Uncomment to have fun 
               SelectObject (hdc, GetStockObject(BLACK_BRUSH));
               DrawBezier (hdc, apt) ;
               
               if (wParam & MK_LBUTTON)
               {
                    apt[1].x = LOWORD (lParam) ;
                    apt[1].y = HIWORD (lParam) ;
               }
               
               if (wParam & MK_RBUTTON)
               {
                    apt[2].x = LOWORD (lParam) ;
                    apt[2].y = HIWORD (lParam) ;
               }
               
               SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
               DrawBezier (hdc, apt) ;
               ReleaseDC (hwnd, hdc) ;
          }
          return 0 ;
          
     case WM_PAINT:
          InvalidateRect (hwnd, NULL, TRUE) ;
          
          hdc = BeginPaint (hwnd, &ps) ;
          
          SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
          DrawBezier (hdc, apt) ;
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
