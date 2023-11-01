#include "tgl.h"
#include <iostream>
#include <vector>
#include <time.h>
#include "Virtual Keys.h"



//#define DEBUG_MODE

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

#define PlaceBrick()\
Copy(render, *target,                                      \
     xRegion, yRegion,                                     \
     0, 0,                                                 \
     target->allocatedWidth(), target->allocatedHeight());



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

    uint8_t
        placeKey = VK_LBUTTON,
        eraseKey = VK_RBUTTON,
        modeKey = 'M',
        eraseAllKey = 'E',
        placeAllKey = 'F',
        exitKey = VK_ESCAPE;

    std::vector<std::vector<TGL::tglTexture*>>
        layer;

    Mode
        mode = Mode::Pyramid;

    POINT
        mouse;

    clock_t
        frameTime,
        previousTime,
        currentTime;



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

    wall.Load("Resources\\Brick.bmp");
    ground.Load("Resources\\Ground.bmp");
    grass.Load("Resources\\Ground.bmp");
    dirt.Load("Resources\\Ground.bmp");
    sky.Load("Resources\\Sky.bmp");
    tree.Load("Resources\\Tree.bmp");

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
            layer[yLayer][xLayer] = NULL; // &brick[yLayer % (sizeof(brick) / sizeof(brick[0]))][xLayer % (sizeof(brick[0]) / sizeof(brick[0][0]))];
        }
    }

    layer[layer.size() / 2][layer[layer.size() / 2].size() / 2] = NULL;

    placeZone = eraseZone = brick[0][0];

    Fill(placeZone, TGL::PixelRGB(0, 255, 0));
    Fill(eraseZone, TGL::PixelRGB(255, 0, 0));

    frameTime = 17;
    previousTime = clock();

    wallOffset = render.allocatedWidth() % brick[0][0].allocatedWidth() / 2;
    skySpeed = 1;

#ifdef DEBUG_MODE
    SetWindowPos(GetConsoleWindow()
                ,0
                ,GetSystemMetrics(SM_CXSCREEN) / 2 - 320
                ,GetSystemMetrics(SM_CYSCREEN) / 2 - 240
                ,0
                ,0
                ,SWP_NOSIZE
                );
#endif // DEBUG_MODE

    while (1)
    {
//        Sleep(1);

        currentTime = clock();

        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            if (currentTime - previousTime >= frameTime)
            {
                previousTime += frameTime;
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
                        aboveLayerSize,
                        belowLayerSize,
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
                                if (layer.size() - 1 != yLayer)
                                {
                                    aboveLayerSize = (Mode::Wall == mode ? layer[yLayer + 1].size() : layer[0].size() - yLayer - 1);
                                }

                                if (layer.size() - 1 == yLayer ||
                                    (Mode::Pyramid == mode && !layer[yLayer + 1][TGL::Max(0, int(xLayer) - 1)]              && !layer[yLayer + 1][TGL::Min(int(xLayer), int(aboveLayerSize) - 1)]) ||
                                    (Mode::Wall    == mode && !layer[yLayer + 1][TGL::Max(0, int(xLayer) - 1 + yLayer % 2)] && !layer[yLayer + 1][TGL::Min(int(xLayer) + yLayer % 2, int(aboveLayerSize) - 1)]))
                                {
                                    Copy(render, eraseZone,
                                         xRegion, yRegion,
                                         0, 0,
                                         eraseZone.allocatedWidth(), eraseZone.allocatedHeight());

                                    if (Holding(eraseKey))
                                    {
                                        layer[yLayer][xLayer] = NULL;
                                    }
                                }
                                else
                                {
                                    PlaceBrick();
                                }
                            }
                            else
                            {
                                if (0 != yLayer)
                                {
                                    belowLayerSize = (Mode::Wall == mode ? layer[yLayer - 1].size() : layer[0].size() - yLayer + 1);
                                }

                                if (0 == yLayer ||
                                    (Mode::Pyramid == mode &&  layer[yLayer - 1][TGL::Max(0, int(xLayer))]                  && layer[yLayer - 1][TGL::Min(int(xLayer) + 1, int(belowLayerSize) - 1)]) ||
                                    (Mode::Wall    == mode && (layer[yLayer - 1][TGL::Max(0, int(xLayer) - 1 + yLayer % 2)] || layer[yLayer - 1][TGL::Min(int(xLayer) + yLayer % 2, int(belowLayerSize) - 1)])))
                                {
                                    Copy(render, placeZone,
                                         xRegion, yRegion,
                                         0, 0,
                                         placeZone.allocatedWidth(), placeZone.allocatedHeight());

                                    if (Holding(placeKey))
                                    {
                                            layer[yLayer][xLayer] = &brick[yLayer % (sizeof(brick) / sizeof(brick[0]))][xLayer % (sizeof(brick[0]) / sizeof(brick[0][0]))];
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (target)
                            {
                                PlaceBrick();
                            }
                        }
                    }
                }



                // Displaying Result

                buffer.Display(render);



                GetAllKeyStatus();

                if (Tapped(eraseAllKey))
                {
                    for (auto &line : layer)
                    {
                        for (auto &column : line)
                        {
                            column = NULL;
                        }
                    }
                }

                if (Tapped(placeAllKey))
                {
                    for (auto &line : layer)
                    {
                        for (auto &column : line)
                        {
                            column = &brick[yLayer % (sizeof(brick) / sizeof(brick[0]))][xLayer % (sizeof(brick[0]) / sizeof(brick[0][0]))];
                        }
                    }
                }

                if (Tapped(modeKey))
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

                if (Tapped(exitKey))
                {
                    break;
                }
            }
        }
    }



//    MessageBox(NULL, "Close Message Box to Close the Program", "End Point", MB_OK);



    return 0;
}



































