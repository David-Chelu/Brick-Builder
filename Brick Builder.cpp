#include "tgl.h"



int main()
{
    TGL::tglWindow
        window;

    TGL::tglDisplay
        buffer;

    TGL::tglTexture
        brick,
        ground,
        sky,
        tree;

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



//    for (yParse = yStart; yParse < yStop; ++yParse)
//    {
//        buffer(yParse);
//
//        for (xParse = xStart; xParse < xStop; ++xParse)
//        {
//            buffer[xParse];
//            buffer = TGL::PixelRGB(255, 0, 0);
//        }
//    }

    brick.Load("Brick.bmp");
    ground.Load("Ground.bmp");
    sky.Load("Sky.bmp");
    tree.Load("Tree.bmp");

//    ZeroMemory(buffer.image(), buffer.bitsPerPixel() * buffer.allocatedWidth() * buffer.allocatedHeight() / 8);

    buffer.Display(brick); Sleep(1000);
    buffer.Display(ground); Sleep(1000);
    buffer.Display(sky); Sleep(1000);
    buffer.Display(tree); Sleep(1000);



    MessageBox(NULL, "Close Message Box to Close the Program", "End Point", MB_OK);



    return 0;
}



































