#ifndef TGL_WINDOW_FUNCTIONS_H
    #define TGL_WINDOW_FUNCTIONS_H



//{TGL::tglWindow functions

LRESULT CALLBACK TGL::tglWindowProcedure(HWND windowHandle,
                                         UINT windowMessage,
                                         WPARAM wordParameter,
                                         LPARAM longParameter)
{
    switch (windowMessage)
    {
        case WM_CREATE:
        {
            return 0;
        }
        case WM_PAINT:
        {
            TGL::disposableDCForWindowProcedure=BeginPaint(windowHandle, &TGL::disposablePaintStructureForWindowProcedure);
            EndPaint(windowHandle, &TGL::disposablePaintStructureForWindowProcedure);

            return 0;
        }
        case WM_DESTROY:
        {
            return 0;
        }
    }
    return DefWindowProc(windowHandle, windowMessage, wordParameter, longParameter);
}

//}TGL::tglWindow functions



#endif // TGL_WINDOW_FUNCTIONS_H






































