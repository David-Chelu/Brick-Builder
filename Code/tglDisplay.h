#ifndef TGL_DISPLAY_H
    #define TGL_DISPLAY_H



//{class TGL::tglDisplay

class TGL::tglDisplay
{
public:
    tglDisplay();
    tglDisplay(const TGL::tglDisplay &targetDisplay);
    tglDisplay(TGL::tglWindow &targetWindow);
    tglDisplay(HWND targetWindowHandle);
    ~tglDisplay();



    TGL::tglDisplay
        &operator =(const TGL::tglDisplay &targetDisplay),
        &operator =(TGL::tglWindow &targetWindow),
        &operator =(HWND targetWindowHandle),
        &operator =(const COLORREF &pixel),
        &operator =(const char *pixel),
        &operator ()(size_t line),
        &operator [](size_t column);



    void
        Clear(),
        AllocateImage(),
        DeallocateImage(),
        DisplayValues(FILE *outputStream=stdout);

    bool
        Render(const TGL::tglVector &camera=TGL::defaultCamera), //Not defined yet
        RenderInterface(), //Not defined yet
        Display(),
        Display(TGL::tglTexture &targetTexture);



    const HWND
        &windowHandle() const;

    const HDC
        &windowDC() const;

    const bool
        *marked() const;

    char
        *image(),
        *pixel();

    const char
        *currentLine() const;

    int
        &xPosition(),
        &yPosition();

    const int
        &xPosition() const,
        &yPosition() const;

    size_t
        &width(),
        &height(),
        &bitsPerPixel();

    const size_t
        &width() const,
        &height() const,
        &allocatedWidth() const,
        &allocatedHeight() const,
        &tglObjectID() const,
        &currentColumn() const;

    const BITMAPINFO
        &bitmapInformation() const;

private:
    void
        Monitor(),
        Initialize();

    HWND
        _windowHandle;

    HDC
        _windowDC;

    bool
        *_marked;

    char
        *_image,
        *_currentLine;

    int
        _xPosition,
        _yPosition;

    BITMAPINFO
        _bitmapInformation;

    size_t
        _width,
        _height,
        _allocatedWidth,
        _allocatedHeight,
        _currentColumn,
        _bitsPerPixel,
        _tglObjectID;
};

//}class TGL::tglDisplay



//{TGL::tglDisplay

TGL::tglDisplay::tglDisplay()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglDisplay::tglDisplay(const TGL::tglDisplay &targetDisplay)
{
    this->Initialize();
    (*this=targetDisplay).Monitor();
}

TGL::tglDisplay::tglDisplay(TGL::tglWindow &targetWindow)
{
    this->Initialize();
    (*this=targetWindow).Monitor();
}

TGL::tglDisplay::tglDisplay(HWND targetWindowHandle)
{
    this->Initialize();
    this->_windowDC=GetDC(this->_windowHandle=targetWindowHandle);
    this->Monitor();
}

TGL::tglDisplay::~tglDisplay()
{
    this->Clear();
    TGL::displayActive[this->_tglObjectID]=0;
}

void TGL::tglDisplay::Initialize()
{
    this->_windowHandle=HWND_DESKTOP;

    this->_windowDC=GetDC(this->_windowHandle);

    this->_marked=NULL;

    this->_image=NULL;
    this->_currentLine=NULL;

    this->_xPosition=0;
    this->_yPosition=0;

    this->_bitsPerPixel=TGL::BITS_PER_PIXEL;

    this->_width=TGL::screenWidth;
    this->_height=TGL::screenHeight;
    this->_allocatedWidth=0;
    this->_allocatedHeight=0;
    this->_currentColumn=0;

    ZeroMemory(&this->_bitmapInformation, sizeof(this->_bitmapInformation));
    this->_bitmapInformation.bmiHeader.biSize=sizeof(this->_bitmapInformation.bmiHeader);
    this->_bitmapInformation.bmiHeader.biPlanes=1;
    this->_bitmapInformation.bmiHeader.biBitCount=TGL::BITS_PER_PIXEL;
    this->_bitmapInformation.bmiHeader.biCompression=BI_RGB;
}

void TGL::tglDisplay::Monitor()
{
    TGL::displayActive[this->_tglObjectID=TGL::displayCount]=1;
    TGL::displayArray[TGL::displayCount++]=this;
    if (TGL::displayCount==TGL::displayCapacity)
    {
        {
            TGL::tglDisplay
                **arrayHandle=TGL::displayArray;

            TGL::displayArray=new TGL::tglDisplay*[TGL::displayCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::displayArray, arrayHandle, sizeof(*arrayHandle)*TGL::displayCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::displayActive;

            TGL::displayActive=new bool[TGL::displayCount];
            memcpy(TGL::displayActive, arrayHandle, sizeof(*arrayHandle)*TGL::displayCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglDisplay &TGL::tglDisplay::operator =(const TGL::tglDisplay &targetDisplay)
{
    this->_windowHandle=targetDisplay._windowHandle;

    this->_windowDC=targetDisplay._windowDC;

    this->_xPosition=targetDisplay._xPosition;
    this->_yPosition=targetDisplay._yPosition;

    this->_width=targetDisplay._width;
    this->_height=targetDisplay._height;

    memcpy(&this->_bitmapInformation,
           &targetDisplay._bitmapInformation,
           sizeof(this->_bitmapInformation));

    if (this->_allocatedWidth*this->_allocatedHeight!=
        targetDisplay._allocatedWidth*targetDisplay._allocatedHeight)
    {
        this->DeallocateImage();
        this->_allocatedWidth=targetDisplay._allocatedWidth;
        this->_allocatedHeight=targetDisplay._allocatedHeight;
        this->AllocateImage();
    }
    else
    {
        this->_allocatedWidth=targetDisplay._allocatedWidth;
        this->_allocatedHeight=targetDisplay._allocatedHeight;
    }

    memcpy(this->_image,
           targetDisplay._image,
           this->_bitsPerPixel*this->_allocatedWidth*this->_allocatedHeight/8);

    this->_currentLine=targetDisplay._currentLine;
    this->_currentColumn=targetDisplay._currentColumn;

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator =(TGL::tglWindow &targetWindow)
{
    *this=targetWindow.windowHandle();

    this->_width=targetWindow.width();
    this->_height=targetWindow.height();

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator =(HWND targetWindowHandle)
{
    this->_windowDC=GetDC(this->_windowHandle=targetWindowHandle);

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator =(const COLORREF &pixel)
{
    if (!this->_currentLine)
    {
        new TGL::tglError(stdout,
                          TGL::errorMessageNullArray,
                          "TGL::tglDisplay &TGL::tglDisplay::operator =(const COLORREF &pixel)",
                          "TGL::tglDisplay::_image",
                          &this->_image);

        if (HandleError)
        {
            HandleError(TGL::nullArrayAccess);
        }
    }

    memcpy(this->_currentLine+this->_bitsPerPixel*this->_currentColumn/8,
           &pixel,
           TGL::Max<size_t>(this->_bitsPerPixel/8, 1));

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator =(const char *pixel)
{
    if (!this->_currentLine)
    {
        new TGL::tglError(stdout,
                          TGL::errorMessageNullArray,
                          "TGL::tglDisplay &TGL::tglDisplay::operator =(const char *pixel)",
                          "TGL::tglDisplay::_image",
                          &this->_image);

        if (HandleError)
        {
            HandleError(TGL::nullArrayAccess);
        }
    }

    memcpy(this->_currentLine+this->_bitsPerPixel*this->_currentColumn/8,
           pixel,
           TGL::Max<size_t>(this->_bitsPerPixel/8, 1));

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator ()(size_t line)
{
    if (!this->_image)
    {
        this->_currentLine=NULL;
    }
    else
    {
        if (line>=this->_allocatedWidth)
        {
            new TGL::tglError(stdout,
                              TGL::errorMessageOutOfBounds,
                              "TGL::tglDisplay &TGL::tglDisplay::operator ()(size_t line)");

            if (HandleError)
            {
                HandleError(TGL::arrayOutOfBounds);
            }
        }

        this->_currentLine=this->_image+line*this->_allocatedWidth*this->_bitsPerPixel/8;
    }

    return *this;
}

TGL::tglDisplay &TGL::tglDisplay::operator [](size_t column)
{
    if (this->_currentLine)
    {
        if (column>=this->_allocatedWidth)
        {
            new TGL::tglError(stdout,
                              TGL::errorMessageOutOfBounds,
                              "TGL::tglDisplay &TGL::tglDisplay::operator [](size_t column)");
        }

        this->_currentColumn=column;
    }

    return *this;
}



void TGL::tglDisplay::Clear()
{
    this->DeallocateImage();
    ZeroMemory(&this->_bitmapInformation, sizeof(this->_bitmapInformation));
}

void TGL::tglDisplay::AllocateImage()
{
    this->DeallocateImage();

    this->_image =new char[(this->_allocatedWidth =this->_width)*
                           (this->_allocatedHeight=this->_height)*
                           this->_bitsPerPixel/8];

    this->_marked=new bool[this->_allocatedWidth*
                           this->_allocatedHeight*
                           this->_bitsPerPixel/8];
}

void TGL::tglDisplay::DeallocateImage()
{
    if (this->_image)
    {
        delete []this->_image;

        this->_image=NULL;
    }

    if (this->_marked)
    {
        delete []this->_marked;

        this->_marked=NULL;
    }
}

void TGL::tglDisplay::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglDisplay Object #%u:\nwindowHandle: %s\nwindowDC: %s\nimage: %s\ncurrentLine: %s\nxPosition: %d\nyPosition: %d\nwidth: %u\nheight: %u\nallocatedWidth: %u\nallocatedHeight: %u\ncurrentColumn: %u\nbitsPerPixel: %u",
            this->_tglObjectID,
            this->_windowHandle? "Yes":"No",
            this->_windowDC? "Yes":"No",
            this->_image? "Yes":"No",
            this->_currentLine? "Yes":"No",
            this->_xPosition,
            this->_yPosition,
            this->_width,
            this->_height,
            this->_allocatedWidth,
            this->_allocatedHeight,
            this->_currentColumn,
            this->_bitsPerPixel);
}

bool TGL::tglDisplay::Render(const TGL::tglVector &camera)
{
    /*
    if (!this->_image ||
        this->_width!=this->_updateWidth ||
        this->_height!=this->_updateHeight)
    {
        this->functionAllocateImage();
    }
    ::ZeroMemory(this->_marked, this->_updateWidth*this->_updateHeight*sizeof(bool));
    long long
        xPixel, yPixel,
        xStart, yStart,
        xStop,  yStop;
    TGL::tglTexture *target;
    bool *currentMarkLine;
    for (unsigned long long component=0; component<TGL::textureLength; component++)
    {
        if (!TGL::textureActive[component])
        {
            continue;
        }
        target=TGL::textureArray[component];
        xStart=TGL::functionMax(camera.xValue(), (double)target->xPosition());
        yStart=TGL::functionMax(camera.yValue(), (double)target->yPosition());
        xStop=TGL::functionMin(camera.xValue()+this->_width, (double)target->xPosition()+target->updateWidth());
        yStop=TGL::functionMin(camera.yValue()+this->_height, (double)target->yPosition()+target->updateHeight());
        for (yPixel=yStart; yPixel<yStop; yPixel++)
        {
            currentMarkLine=this->_marked+this->_updateWidth*(yPixel-(long long)camera.yValue());
            (*target)(yPixel-target->yPosition());
            (*this)(yPixel-camera.yValue());
            for (xPixel=xStart; xPixel<xStop; xPixel++)
            {
                if (!currentMarkLine[xPixel-(long long)camera.xValue()] &&
                    (*target)[xPixel-target->xPosition()]!=TGL::transparentColor)
                {
                    currentMarkLine[xPixel-(long long)camera.xValue()]=1;
                    (*this)[xPixel-(long long)camera.xValue()]=target->pixel();
                }
            }
        }
    }
    */
    return 1;
}

bool TGL::tglDisplay::RenderInterface()
{
    /*
    ::printf("Entered functionRenderInterface()\n");
    if (!this->_image ||
        this->_width!=this->_updateWidth ||
        this->_height!=this->_updateHeight)
    {
        this->functionAllocateImage();
    }
    ::ZeroMemory(this->_marked, this->_updateWidth*this->_updateHeight*sizeof(bool));
    ::ZeroMemory(this->_image, this->_updateWidth*this->_updateHeight*TGL::BITS_PER_PIXEL/8);
    long long
        xPixel, yPixel,
        xStart, yStart,
        xStop,  yStop;
    TGL::tglInterface *targetInterface;
    TGL::tglButton *targetButton;
    TGL::tglTexture *targetTexture;
    bool *currentMarkLine;
    for (unsigned long long component=0; component<TGL::interfaceLength; component++)
    {
        if (!(targetInterface=TGL::interfaceArray[component])->focus()) //if (TGL::interfaceArray[component]->ignore())
        {
            continue;
        }
        for (unsigned long long buttonID=0; buttonID<targetInterface->buttonLength(); buttonID++)
        {
            if (targetTexture=(targetButton=(*targetInterface)[buttonID])->currentTexture())
            {
                xStart=TGL::functionMax((int)0, int(targetButton->xPosition()+targetTexture->xPosition()));
                yStart=TGL::functionMax((int)0, int(targetButton->yPosition()+targetTexture->yPosition()));
                xStop=TGL::functionMin((int)this->_width, int(targetButton->xPosition()+targetTexture->xPosition()+targetTexture->updateWidth()));
                yStop=TGL::functionMin((int)this->_height, int(targetButton->yPosition()+targetTexture->yPosition()+targetTexture->updateHeight()));
                for (yPixel=yStart; yPixel<yStop; yPixel++)
                {
                    currentMarkLine=this->_marked+this->_updateWidth*yPixel;
                    (*targetTexture)(yPixel-targetButton->yPosition()-targetTexture->yPosition());
                    (*this)(yPixel);
                    for (xPixel=xStart; xPixel<xStop; xPixel++)
                    {
                        if (!currentMarkLine[xPixel] &&
                            (*targetTexture)[xPixel-targetButton->xPosition()-targetTexture->xPosition()]!=TGL::transparentColor)
                        {
                            currentMarkLine[xPixel]=1;
                            (*this)[xPixel]=targetTexture->pixel();
                        }
                    }
                }
            }
        }
        targetTexture=targetInterface->background();
        xStart=max(0, targetTexture->xPosition());
        yStart=max(0, targetTexture->yPosition());
        xStop=min(this->_updateWidth, targetTexture->xPosition()+targetTexture->updateWidth());
        yStop=min(this->_updateHeight, targetTexture->yPosition()+targetTexture->updateHeight());
        for (yPixel=yStart; yPixel<yStop; yPixel++)
        {
            currentMarkLine=this->_marked+this->_updateWidth*yPixel;
            (*targetTexture)(yPixel-targetTexture->yPosition());
            (*this)(yPixel);
            for (xPixel=xStart; xPixel<xStop; xPixel++)
            {
                if (!currentMarkLine[xPixel] &&
                    (*targetTexture)[xPixel-targetTexture->xPosition()]!=TGL::transparentColor)
                {
                    currentMarkLine[xPixel]=1;
                    (*this)[xPixel]=targetTexture->pixel();
                }
            }
        }
    }
    */
    return true;
}

bool TGL::tglDisplay::Display()
{
    this->_bitmapInformation.bmiHeader.biWidth=this->_allocatedWidth;
    this->_bitmapInformation.bmiHeader.biHeight=-this->_allocatedHeight;
    this->_bitmapInformation.bmiHeader.biBitCount=this->_bitsPerPixel;

    if (!SetDIBitsToDevice(this->_windowDC,
                           this->_xPosition,
                           this->_yPosition,
                           this->_allocatedWidth,
                           this->_allocatedHeight,
                           0,
                           0,
                           0,
                           this->_allocatedHeight,
                           this->_image,
                           &this->_bitmapInformation,
                           DIB_RGB_COLORS))
    {
        return 0;
    }

    return 1;
}

bool TGL::tglDisplay::Display(TGL::tglTexture &targetTexture)
{
    this->_bitmapInformation.bmiHeader.biWidth=targetTexture.allocatedWidth();
    this->_bitmapInformation.bmiHeader.biHeight=-targetTexture.allocatedHeight();
    this->_bitmapInformation.bmiHeader.biBitCount=targetTexture.bitsPerPixel();

    if (!SetDIBitsToDevice(this->_windowDC,
                           targetTexture.xPosition(),
                           targetTexture.yPosition(),
                           targetTexture.allocatedWidth(),
                           targetTexture.allocatedHeight(),
                           0,
                           0,
                           0,
                           targetTexture.allocatedHeight(),
                           targetTexture.image(),
                           &this->_bitmapInformation,
                           DIB_RGB_COLORS))
    {
        return 0;
    }

    return 1;
}



const HWND &TGL::tglDisplay::windowHandle() const
{
	return this->_windowHandle;
}

const HDC &TGL::tglDisplay::windowDC() const
{
	return this->_windowDC;
}

const bool *TGL::tglDisplay::marked() const
{
	return this->_marked;
}

char *TGL::tglDisplay::image()
{
	return this->_image;
}

char *TGL::tglDisplay::pixel()
{
    if (!this->_currentLine)
    {
        new TGL::tglError(stdout,
                          "Attempted to access pixel in a NULL image(array).",
                          "TGL::tglDisplay::pixel()",
                          "TGL::tglDisplay::_image",
                          &this->_currentLine);
    }

	return this->_currentLine+this->_bitsPerPixel*this->_currentColumn/8;
}

const char *TGL::tglDisplay::currentLine() const
{
	return this->_currentLine;
}

int &TGL::tglDisplay::xPosition()
{
	return this->_xPosition;
}

const int &TGL::tglDisplay::xPosition() const
{
	return this->_xPosition;
}

int &TGL::tglDisplay::yPosition()
{
	return this->_yPosition;
}

const int &TGL::tglDisplay::yPosition() const
{
	return this->_yPosition;
}

size_t &TGL::tglDisplay::width()
{
	return this->_width;
}

const size_t &TGL::tglDisplay::width() const
{
	return this->_width;
}

size_t &TGL::tglDisplay::height()
{
	return this->_height;
}

const size_t &TGL::tglDisplay::height() const
{
	return this->_height;
}

size_t &TGL::tglDisplay::bitsPerPixel()
{
    return this->_bitsPerPixel;
}

const size_t &TGL::tglDisplay::allocatedWidth() const
{
	return this->_allocatedWidth;
}

const size_t &TGL::tglDisplay::allocatedHeight() const
{
	return this->_allocatedHeight;
}

const size_t &TGL::tglDisplay::tglObjectID() const
{
	return this->_tglObjectID;
}

const size_t &TGL::tglDisplay::currentColumn() const
{
	return this->_currentColumn;
}

const BITMAPINFO &TGL::tglDisplay::bitmapInformation() const
{
	return this->_bitmapInformation;
}

//}TGL::tglDisplay



#include"tglDisplay Functions.h"



#endif // TGL_DISPLAY_H






































