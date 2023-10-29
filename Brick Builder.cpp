#include "tgl.h"
#include <iostream>



void Copy(TGL::tglTexture &destination,
          TGL::tglTexture &source,
          uint16_t xStart,
          uint16_t yStart,
          uint16_t width,
          uint16_t height)
{
    for (uint16_t yPixel = 0; yPixel < height; ++yPixel)
    {
        destination(yPixel);
        source(yStart + yPixel);

        for (uint16_t xPixel = 0; xPixel < width; ++xPixel)
        {
            destination[xPixel] = source[xStart + xPixel].pixel();
        }
    }
}



int main()
{
    TGL::tglWindow
        window;

    TGL::tglDisplay
        buffer;

    TGL::tglTexture
        wall,
        ground,
        sky,
        tree,
        grass,
        dirt,
        cutSky,
        brick[4][4],
        skyLoop;

    uint16_t
        xStart, xStop, xParse,
        yStart, yStop, yParse,
        horizon,
        width, height,
        yCutStart,
        cutHeight,
        skyOffset;



    window.xPosition() = (TGL::screenWidth  - (window.width()  = TGL::Min(1600, TGL::screenWidth)))  / 2;
    window.yPosition() = (TGL::screenHeight - (window.height() = TGL::Min(900,  TGL::screenHeight))) / 2;

    window.style() |= WS_POPUP;

    window.Create();
    window.Show();



    buffer = window;
    buffer.AllocateImage();

//    xStart =
//    yStart = 0;
//    xStop = buffer.allocatedWidth();
//    yStop = buffer.allocatedHeight();



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

    wall.Load("Brick.bmp");
    ground.Load("Ground.bmp");
    grass.Load("Ground.bmp");
    dirt.Load("Ground.bmp");
    sky.Load("Sky.bmp");
    tree.Load("Tree.bmp");

//    ZeroMemory(buffer.image(), buffer.bitsPerPixel() * buffer.allocatedWidth() * buffer.allocatedHeight() / 8);

    grass.height() = grass.width(); grass.AllocateImage();
    dirt .height() = dirt .width(); dirt .AllocateImage();

    CopyMemory(grass.image(),
               ground.image(),
               grass.allocatedWidth() * grass.allocatedHeight() * grass.bitsPerPixel() / 8);
    CopyMemory(dirt.image(),
               ground.image() + grass.allocatedWidth() * grass.allocatedHeight() * grass.bitsPerPixel() / 8,
               dirt.allocatedWidth() * dirt.allocatedHeight() * dirt.bitsPerPixel() / 8);

//    dirt.xPosition() = grass.allocatedWidth();

//    buffer.Display(wall);  Sleep(1000);
//    buffer.Display(grass); Sleep(1000);
//    buffer.Display(dirt);  Sleep(1000);
//    buffer.Display(sky);   Sleep(1000);
//    buffer.Display(tree);



    yStart = 0; yStop = sizeof(brick) / sizeof(brick[0]);
    xStart = 0; xStop = sizeof(brick[0]) / sizeof(brick[0][0]);

    width  = wall.allocatedWidth()  / xStop;
    height = wall.allocatedHeight() / yStop;

    for (yParse = yStart; yParse < yStop; ++yParse)
    {
        for (xParse = xStart; xParse < xStop; ++xParse)
        {
            brick[yParse][xParse].width()  = width;
            brick[yParse][xParse].height() = height;
            brick[yParse][xParse].bitsPerPixel() = 32;
            brick[yParse][xParse].AllocateImage();

            Copy(brick[yParse][xParse],
                 wall,
                 xParse * width,
                 yParse * height,
                 width,
                 height);

            brick[yParse][xParse].xPosition() = xParse * width;
            brick[yParse][xParse].yPosition() = yParse * height;
        }
    }



    // Placing Grass

    horizon = buffer.allocatedHeight() / 2;
    xStop = buffer.allocatedWidth() / grass.allocatedWidth();
    grass.yPosition() = horizon;

    for (xParse = xStart; xParse < xStop; ++xParse)
    {
        grass.xPosition() = xParse * grass.allocatedWidth();

        buffer.Display(grass);
    }



    // Placing Dirt

    yStart = 0;
    yStop = buffer.allocatedHeight() / dirt.allocatedHeight() / 2;

    for (yParse = yStart; yParse < yStop; ++yParse)
    {
        dirt.yPosition() = horizon + (yParse + 1) * dirt.allocatedHeight();

        for (xParse = xStart; xParse < xStop; ++xParse)
        {
            dirt.xPosition() = xParse * dirt.allocatedWidth();

            buffer.Display(dirt);
        }
    }



    cutHeight = horizon;
    yCutStart = (sky.allocatedHeight() - horizon) / 2;

    cutSky.width() = sky.allocatedWidth();
    cutSky.height() = cutHeight;
    cutSky.AllocateImage();

    Copy(cutSky,
         sky,
         0,
         yCutStart,
         cutSky.allocatedWidth(),
         cutHeight);



    MSG message;

    skyOffset = 1;
    width  = brick[0][0].allocatedWidth();
    height = brick[0][0].allocatedHeight();

    skyLoop = cutSky;

    while (1)
    {
        // Moving Sky

        cutSky .xPosition() -= skyOffset;
        skyLoop.xPosition() -= skyOffset;

        // Looping Sky

        if (cutSky.xPosition() <= 0)
        {
            skyLoop.xPosition() = cutSky.xPosition() + cutSky.allocatedWidth();
        }

        if (skyLoop.xPosition() <= 0)
        {
            cutSky.xPosition() = skyLoop.xPosition() + skyLoop.allocatedWidth();
        }

        // Placing Sky

        buffer.Display(cutSky);
        buffer.Display(skyLoop);

        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                break;
            }
        }

        Sleep(17);
    }



    MessageBox(NULL, "Close Message Box to Close the Program", "End Point", MB_OK);



    return 0;
}



































