#ifndef TGL_TEXTURE_H
    #define TGL_TEXTURE_H



//{class TGL::tglTexture

class TGL::tglTexture
{
public:
    tglTexture();
    tglTexture(const TGL::tglTexture &targetTexture);
    ~tglTexture();



    TGL::tglTexture
        &operator =(const TGL::tglTexture &targetTexture),
        &operator =(const char *pixel),
        &operator =(const COLORREF &pixel),
        &operator ()(size_t line),
        &operator [](size_t column);



    void
        Clear(),
        AllocateImage(),
        DeallocateImage(),
        DisplayValues(FILE *outputStream=stdout);

    bool
        Load(const char *directory),
        Stretch(size_t newWidth=TGL::screenWidth, size_t newHeight=TGL::screenHeight);



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
        &bitsPerPixel(),
        &width(),
        &height();

    const size_t
        &width() const,
        &height() const,
        &allocatedWidth() const,
        &allocatedHeight() const,
        &currentColumn() const,
        &tglObjectID() const;

private:
    void
        Monitor(),
        Initialize();

    char
        *_image,
        *_currentLine;

    int
        _xPosition,
        _yPosition;

    size_t
        _bitsPerPixel,
        _width,
        _height,
        _allocatedWidth,
        _allocatedHeight,
        _currentColumn,
        _tglObjectID;
};

//}class TGL::tglTexture



//{TGL::tglTexture

TGL::tglTexture::tglTexture()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglTexture::tglTexture(const TGL::tglTexture &targetTexture)
{
    this->Initialize();
    (*this=targetTexture).Monitor();
}

TGL::tglTexture::~tglTexture()
{
    this->Clear();
    TGL::textureActive[this->_tglObjectID]=0;
}

void TGL::tglTexture::Initialize()
{
    this->_image=this->_currentLine=NULL;

    this->_xPosition=_yPosition=0;

    this->_width=TGL::screenWidth;
    this->_height=TGL::screenHeight;

    this->_bitsPerPixel=TGL::BITS_PER_PIXEL;

    this->_allocatedWidth=this->_allocatedHeight=0;
    this->_currentColumn=0;
}

void TGL::tglTexture::Monitor()
{
    TGL::textureActive[this->_tglObjectID=TGL::textureCount]=1;
    TGL::textureArray[TGL::textureCount++]=this;
    if (TGL::textureCount==TGL::textureCapacity)
    {
        {
            TGL::tglTexture
                **arrayHandle=TGL::textureArray;

            TGL::textureArray=new TGL::tglTexture*[TGL::textureCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::textureArray, arrayHandle, sizeof(*arrayHandle)*TGL::textureCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::textureActive;

            TGL::textureActive=new bool[TGL::textureCount];
            memcpy(TGL::textureActive, arrayHandle, sizeof(*arrayHandle)*TGL::textureCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglTexture &TGL::tglTexture::operator =(const TGL::tglTexture &targetTexture)
{
    this->_bitsPerPixel=targetTexture._bitsPerPixel;

    this->_xPosition=targetTexture._xPosition;
    this->_yPosition=targetTexture._yPosition;

    this->_width=targetTexture._width;
    this->_height=targetTexture._height;

    if (this->_allocatedWidth*this->_allocatedHeight!=targetTexture._allocatedWidth*targetTexture._allocatedHeight)
    {
        this->DeallocateImage();

        this->_allocatedWidth=targetTexture._allocatedWidth;
        this->_allocatedHeight=targetTexture._allocatedHeight;

        this->AllocateImage();
    }
    else
    {
        this->_allocatedWidth=targetTexture._allocatedWidth;
        this->_allocatedHeight=targetTexture._allocatedHeight;
    }

    memcpy(this->_image,
           targetTexture._image,
           this->_bitsPerPixel*this->_allocatedWidth*this->_allocatedHeight/8);

    this->_currentLine=targetTexture._currentLine;
    this->_currentColumn=targetTexture._currentColumn;

    return *this;
}

TGL::tglTexture &TGL::tglTexture::operator =(const char *pixel)
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

TGL::tglTexture &TGL::tglTexture::operator =(const COLORREF &pixel)
{
    if (!this->_currentLine)
    {
        new TGL::tglError(stdout,
                          TGL::errorMessageNullArray,
                          "TGL::tglTexture &TGL::tglTexture::operator =(const COLORREF &pixel)",
                          "TGL::tglTexture::_image",
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

TGL::tglTexture &TGL::tglTexture::operator ()(size_t line)
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

TGL::tglTexture &TGL::tglTexture::operator [](size_t column)
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



void TGL::tglTexture::Clear()
{
    this->_image? delete []this->_image:void(0);
}

void TGL::tglTexture::AllocateImage()
{
    this->DeallocateImage();

    this->_image =new char[(this->_allocatedWidth =this->_width)*
                           (this->_allocatedHeight=this->_height)*
                           this->_bitsPerPixel/8];
}

void TGL::tglTexture::DeallocateImage()
{
    if (this->_image)
    {
        delete []this->_image;

        this->_image=NULL;
    }
}

void TGL::tglTexture::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglTexture Object #%u:\nimage: %s\ncurrentLine: %s\nxPosition: %d\nyPosition: %d\nbitsPerPixel: %u\nwidth: %u\nheight: %u\nallocatedWidth: %u\nallocatedHeight: %u\ncurrentColumn: %u",
            this->_tglObjectID,
            this->_image? "Yes":"No",
            this->_currentLine? "Yes":"No",
            this->_xPosition,
            this->_yPosition,
            this->_bitsPerPixel,
            this->_width,
            this->_height,
            this->_allocatedWidth,
            this->_allocatedHeight,
            this->_currentColumn);
}

bool TGL::tglTexture::Load(const char *directory)
{
    FILE
        *fileHandle=fopen(directory, "rb");

    if (!fileHandle)
    {
        new TGL::tglError(stdout,
                          TGL::errorLoadingFile,
                          "bool TGL::tglTexture::Load(const char *directory)",
                          "directory",
                          NULL);

        return 0;
    }

    char
        *fileContents=new char[54];


    BITMAPFILEHEADER
        *bitmapFileHeader;

    BITMAPINFOHEADER
        *bitmapInfoHeader;

    fread(fileContents, 1, 54, fileHandle);

    bitmapFileHeader=(BITMAPFILEHEADER*)fileContents;
    bitmapInfoHeader=(BITMAPINFOHEADER*)(fileContents+sizeof(BITMAPFILEHEADER));

    this->_width=bitmapInfoHeader->biWidth;
    this->_height=bitmapInfoHeader->biHeight;
    this->AllocateImage();

    for (size_t line=0; line<this->_allocatedHeight; line++)
    {
        fread(this->_image+(this->_allocatedHeight-line-1)*this->_allocatedWidth*this->_bitsPerPixel/8,
              1,
              this->_allocatedWidth*this->_bitsPerPixel/8,
              fileHandle);
    }

    delete []fileContents;

    fclose(fileHandle);

    return 1;
}

bool TGL::tglTexture::Stretch(size_t newWidth, size_t newHeight)
{
    TGL::tglTexture
        originalImage=*this;

    if (this->_allocatedWidth*this->_allocatedHeight!=
        newWidth*newHeight)
    {
        this->_width=newWidth;
        this->_height=newHeight;

        this->AllocateImage();
    }
    else
    {
        if (this->_allocatedWidth==newWidth &&
            this->_allocatedHeight==newHeight)
        {
            return 0;
        }

        this->_width=newWidth;
        this->_height=newHeight;

        this->_allocatedWidth=newWidth;
        this->_allocatedHeight=newHeight;
    }

    int
        xPixel,
        yPixel,
        xStart=0,
        yStart=0,
        xStop=TGL::Max<size_t>(this->_allocatedWidth, originalImage.width()),
        yStop=TGL::Max<size_t>(this->_allocatedHeight, originalImage.height());

    for (yPixel=yStart; yPixel<yStop; yPixel++)
    {
        (*this)(yPixel*this->_height/yStop);
        originalImage(yPixel*originalImage.height()/yStop);
        for (xPixel=xStart; xPixel<xStop; xPixel++)
        {
            (*this)[xPixel*this->_width/xStop]=
            originalImage[xPixel*originalImage.width()/xStop].pixel();
        }
    }

    return 1;
}



char *TGL::tglTexture::image()
{
	return this->_image;
}

char *TGL::tglTexture::pixel()
{
    if (!this->_currentLine)
    {
        new TGL::tglError(stdout,
                          "Attempted to access pixel in a NULL image(array).",
                          "char *TGL::tglTexture::pixel()",
                          "TGL::tglDisplay::_image",
                          &this->_currentLine);
    }

	return this->_currentLine+this->_bitsPerPixel*this->_currentColumn/8;
}

const char *TGL::tglTexture::currentLine() const
{
	return this->_currentLine;
}

int &TGL::tglTexture::xPosition()
{
	return this->_xPosition;
}

const int &TGL::tglTexture::xPosition() const
{
	return this->_xPosition;
}

int &TGL::tglTexture::yPosition()
{
	return this->_yPosition;
}

const int &TGL::tglTexture::yPosition() const
{
	return this->_yPosition;
}

size_t &TGL::tglTexture::bitsPerPixel()
{
    return this->_bitsPerPixel;
}

size_t &TGL::tglTexture::width()
{
	return this->_width;
}

const size_t &TGL::tglTexture::width() const
{
	return this->_width;
}

size_t &TGL::tglTexture::height()
{
	return this->_height;
}

const size_t &TGL::tglTexture::height() const
{
	return this->_height;
}

const size_t &TGL::tglTexture::allocatedWidth() const
{
	return this->_allocatedWidth;
}

const size_t &TGL::tglTexture::allocatedHeight() const
{
	return this->_allocatedHeight;
}

const size_t &TGL::tglTexture::currentColumn() const
{
	return this->_currentColumn;
}

const size_t &TGL::tglTexture::tglObjectID() const
{
	return this->_tglObjectID;
}

//}TGL::tglTexture



#include"tglTexture Functions.h"



#endif // TGL_TEXTURE_H






































