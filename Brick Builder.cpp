#include "tgl.h"
#include <iostream>
#include <vector>
#include "Virtual Keys.h"



#define GlueSkies(left, right)\
{\
    skyOffset = TGL::Min(int32_t(left.allocatedWidth()) + left.xPosition(), \
                         int32_t(render.allocatedWidth()));                 \
                                                                            \
    Copy(render, left,                                                      \
         0, 0,                                                              \
         -left.xPosition(), 0,                                              \
         skyOffset, left.allocatedHeight());                                \
                                                                            \
    Copy(render, right,                                                     \
         skyOffset, 0,                                                      \
         0, 0,                                                              \
         render.allocatedWidth() - skyOffset, right.allocatedHeight());     \
}



enum Mode
{
    Pyramid,
    Wall
};



void Copy(TGL::tglTexture &destination,
          TGL::tglTexture &source,
          uint16_t xDestination,
          uint16_t yDestination,
          uint16_t xSource,
          uint16_t ySource,
          uint16_t width,
          uint16_t height)
{
    for (uint16_t yPixel = 0; yPixel < height; ++yPixel)
    {
        destination(yDestination + yPixel);
        source(ySource + yPixel);

        for (uint16_t xPixel = 0; xPixel < width; ++xPixel)
        {
            destination[xDestination + xPixel] = source[xSource + xPixel].pixel();
        }
    }
}

void Fill(TGL::tglTexture &destination,
          COLORREF color)
{
    for (uint16_t yPixel = 0; yPixel < destination.allocatedHeight(); ++yPixel)
    {
        destination(yPixel);

        for (uint16_t xPixel = 0; xPixel < destination.allocatedWidth(); ++xPixel)
        {
            destination[xPixel] = color;
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
        skyLoop,
        render,
        placeZone,
        eraseZone;

    uint16_t
        xStart, xStop, xParse,
        yStart, yStop, yParse,
        horizon,
        width, height,
        yCutStart,
        cutHeight,
        skySpeed,
        skyOffset,
        xLayer, yLayer,
        wallOffset,
        layerOffset,
        layerStart,
        brickLocation;

    std::vector<std::vector<TGL::tglTexture*>>
        layer;

    Mode
        mode = Mode::Pyramid;

    POINT
        mouse;



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
                 0,
                 0,
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



    // Cutting Sky.bmp

    cutHeight = horizon;
    yCutStart = (sky.allocatedHeight() - horizon) / 2;

    cutSky.width() = sky.allocatedWidth();
    cutSky.height() = cutHeight;
    cutSky.AllocateImage();

    Copy(cutSky, sky,
         0, 0,
         0, yCutStart,
         cutSky.allocatedWidth(), cutHeight);



    MSG message;

    wallOffset = render.allocatedWidth() % brick[0][0].allocatedWidth() / 2;
    skySpeed = 1;

    width  = brick[0][0].allocatedWidth();
    height = brick[0][0].allocatedHeight();

    skyLoop = cutSky;

    render.width()  = buffer.allocatedWidth();
    render.height() = buffer.allocatedHeight() / 2;
    render.AllocateImage();

    layer.resize(horizon / brick[0][0].allocatedHeight());

    for (yLayer = 0; yLayer < layer.size(); ++yLayer)
    {
        layer[yLayer].resize(buffer.allocatedWidth() / brick[0][0].allocatedWidth() - yLayer % 2);

        for (xLayer = 0; xLayer < layer[yLayer].size(); ++xLayer)
        {
            layer[yLayer][xLayer] = &brick[yLayer % (sizeof(brick) / sizeof(brick[0]))][xLayer % (sizeof(brick[0]) / sizeof(brick[0][0]))];
        }
    }

    layer[layer.size() / 2][layer[layer.size() / 2].size() / 2] = NULL;

    placeZone = eraseZone = brick[0][0];

    Fill(placeZone, TGL::PixelRGB(0, 255, 0));
    Fill(eraseZone, TGL::PixelRGB(255, 0, 0));

    while (1)
    {
        Sleep(17);

        // Moving Sky

        cutSky .xPosition() -= skySpeed;
        skyLoop.xPosition() -= skySpeed;



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

        int32_t
            skyOffset;

        if (cutSky.xPosition() < skyLoop.xPosition())
        {
            GlueSkies(cutSky, skyLoop);
        }
        else
        {
            GlueSkies(skyLoop, cutSky);
        }



        // Placing Bricks

        for (yLayer = 0; yLayer < layer.size(); ++yLayer)
        {
            static uint16_t
                layerSize,
                xRegion, yRegion;

            layerSize = (Mode::Wall == mode ? layer[yLayer].size() : layer[0].size() - yLayer);
            layerStart = render.allocatedHeight() - (yLayer + 1) * brick[0][0].allocatedHeight();

            for (xLayer = 0; xLayer < layerSize; ++xLayer)
            {
                layerOffset = (Mode::Wall == mode ? yLayer % 2 : yLayer) * brick[0][0].allocatedWidth() / 2;
                brickLocation = xLayer * brick[0][0].allocatedWidth();

                xRegion = wallOffset + layerOffset + brickLocation;
                yRegion = layerStart;

                static TGL::tglTexture
                    *target;

                target = layer[yLayer][xLayer];

                GetCursorPos(&mouse);

                mouse.x -= window.xPosition();
                mouse.y -= window.yPosition();

                if (xRegion <= mouse.x && mouse.x < xRegion + brick[0][0].allocatedWidth() &&
                    yRegion <= mouse.y && mouse.y < yRegion + brick[0][0].allocatedHeight())
                {
                    if (target)
                    {
                        Copy(render, eraseZone,
                             xRegion, yRegion,
                             0, 0,
                             eraseZone.allocatedWidth(), eraseZone.allocatedHeight());
                    }
                    else
                    {
                        Copy(render, placeZone,
                             xRegion, yRegion,
                             0, 0,
                             placeZone.allocatedWidth(), placeZone.allocatedHeight());
                    }
                }
                else
                {
                    if (target)
                    {
                        Copy(render, *target,
                             xRegion, yRegion,
                             0, 0,
                             target->allocatedWidth(), target->allocatedHeight());
                    }
                }
            }
        }



        // Displaying Result

        buffer.Display(render);



        GetAllKeyStatus();

        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            if (GetAsyncKeyState('M'))
            {
                if (Mode::Pyramid == mode)
                {
                    mode = Mode::Wall;
                }
                else
                {
                    mode = Mode::Pyramid;
                }
            }

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                break;
            }
        }
    }



    MessageBox(NULL, "Close Message Box to Close the Program", "End Point", MB_OK);



    return 0;
}



































