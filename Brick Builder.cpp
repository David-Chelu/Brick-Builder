#include "tgl.h"



int main()
{
    TGL::tglWindow
        window;

    TGL::tglDisplay
        buffer;

    uint16_t
        xStart, xStop, xParse,
        yStart, yStop, yParse;



    window.xPosition() = (TGL::screenWidth  - (window.width()  = TGL::Min(1200, TGL::screenWidth))) / 2;
    window.yPosition() = (TGL::screenHeight - (window.height() = TGL::Min(900, TGL::screenHeight))) / 2;

    window.style() |= WS_POPUP;

    window.Create();
    window.Show();



    buffer = window;
    buffer.AllocateImage();

    xStart =
    yStart = 0;
    xStop = buffer.allocatedWidth();
    yStop = buffer.allocatedHeight();



    for (yParse = yStart; yParse < yStop; ++yParse)
    {
        buffer(yParse);

        for (xParse = xStart; xParse < xStop; ++xParse)
        {
            buffer[xParse];
            buffer = TGL::PixelRGB(255, 0, 0);
        }
    }



    buffer.Display();



    MessageBox(NULL, "Close Message Box to Close the Program", "End Point", MB_OK);



    return 0;
}



































