#ifndef TGL_WINDOW_H
    #define TGL_WINDOW_H



//{class TGL::tglWindow

class TGL::tglWindow
{
public:
    tglWindow();
    tglWindow(const TGL::tglWindow &targetWindow);
    tglWindow(const WNDPROC &targetWindowProcedure);
    ~tglWindow();



    TGL::tglWindow
        &operator =(const TGL::tglWindow &targetWindow),
        &operator =(const WNDPROC &targetWindowProcedure);



    void
        Clear(),
        DisplayValues(FILE *outputStream=stdout);

    bool
        Show(),
        Hide(),
        Update(HWND insertAfterWindow=NULL, UINT windowFlags=SWP_SHOWWINDOW);

    HWND
        Create(),
        Create(DWORD newExtendedStyle,
               const char *newClassName,
               const char *newWindowName,
               DWORD newStyle,
               int newXPosition,
               int newYPosition,
               size_t newWidth,
               size_t newHeight,
               HWND newParentWindow,
               HMENU newMenuHandle,
               HINSTANCE newWindowInstance);



    HMENU
        &menuHandle(),
        menuHandle() const;

    DWORD
        &style(),
        &extendedStyle();

    const DWORD
        &style() const,
        &extendedStyle() const;

    const char
        *&windowName(),
        *&className();

    const char
        *windowName() const,
        *className() const;

    HWND
        &parentWindow(),
        parentWindow() const,
        windowHandle() const;

    WNDPROC
        &windowProcedure();

    const WNDPROC
        windowProcedure() const;

    HINSTANCE
        &windowInstance();

    const HINSTANCE
        windowInstance() const;

    int
        &backgroundColor(),
        &xPosition(),
        &yPosition();

    const int
        &backgroundColor() const,
        &xPosition() const,
        &yPosition() const;

    size_t
        &width(),
        &height();

    const size_t
        &width() const,
        &height() const,
        &tglObjectID() const;

private:
    void
        Monitor(),
        Initialize();

    HMENU
        _menuHandle;

    DWORD
        _style,
        _extendedStyle;

    const char
        *_windowName,
        *_className;

    WNDPROC
        _windowProcedure;

    HWND
        _parentWindow,
        _windowHandle;

    WNDCLASS
        _windowClass;

    HINSTANCE
        _windowInstance;

    int
        _backgroundColor,
        _xPosition,
        _yPosition;

    size_t
        _width,
        _height,
        _tglObjectID;
};

//}class TGL::tglWindow



//{TGL::tglWindow

TGL::tglWindow::tglWindow()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglWindow::tglWindow(const TGL::tglWindow &targetWindow)
{
    this->Initialize();
    (*this=targetWindow).Monitor();
}

TGL::tglWindow::tglWindow(const WNDPROC &targetWindowProcedure)
{
    this->Initialize();
    this->_windowProcedure=targetWindowProcedure;
    this->Monitor();
}

TGL::tglWindow::~tglWindow()
{
    this->Clear();
    TGL::windowActive[this->_tglObjectID]=0;
}

void TGL::tglWindow::Initialize()
{
    this->_menuHandle=NULL;

    this->_style=WS_VISIBLE;
    this->_extendedStyle=0;

    this->_windowName="TGL Program";
    this->_className="Generated Using TGL::tglWindow";

    this->_backgroundColor=BLACK_BRUSH;

    this->_windowProcedure=TGL::tglWindowProcedure;

    this->_parentWindow=
    this->_windowHandle=NULL;

    ZeroMemory(&this->_windowClass, sizeof(this->_windowClass));

    this->_windowInstance=TGL::windowCreationInstance;

    this->_xPosition=
    this->_yPosition=0;

    this->_width=TGL::screenWidth;
    this->_height=TGL::screenHeight;
}

void TGL::tglWindow::Monitor()
{
    TGL::windowActive[this->_tglObjectID=TGL::windowCount]=1;
    TGL::windowArray[TGL::windowCount++]=this;
    if (TGL::windowCount==TGL::windowCapacity)
    {
        {
            TGL::tglWindow
                **arrayHandle=TGL::windowArray;

            TGL::windowArray=new TGL::tglWindow*[TGL::windowCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::windowArray, arrayHandle, sizeof(*arrayHandle)*TGL::windowCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::windowActive;

            TGL::windowActive=new bool[TGL::windowCount];
            memcpy(TGL::windowActive, arrayHandle, sizeof(*arrayHandle)*TGL::windowCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglWindow &TGL::tglWindow::operator =(const TGL::tglWindow &targetWindow)
{
    memcpy(&this->_windowClass,
           &targetWindow._windowClass,
           sizeof(this->_windowClass));

    this->_menuHandle=targetWindow._menuHandle;

    this->_style=targetWindow._style;
    this->_extendedStyle=targetWindow._extendedStyle;

    this->_windowName=targetWindow._windowName;
    this->_className=targetWindow._className;

    this->_windowProcedure=targetWindow._windowProcedure;
    this->_windowInstance=targetWindow._windowInstance;

    this->_backgroundColor=targetWindow._backgroundColor;

    this->_xPosition=targetWindow._xPosition;
    this->_yPosition=targetWindow._yPosition;

    this->_width=targetWindow._width;
    this->_height=targetWindow._height;

    return *this;
}

TGL::tglWindow &TGL::tglWindow::operator =(const WNDPROC &targetWindowProcedure)
{
    this->_windowProcedure=targetWindowProcedure;
    return *this;
}



void TGL::tglWindow::Clear()
{
    if (this->_windowHandle)
    {
        DestroyWindow(this->_windowHandle);
    }
}

void TGL::tglWindow::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglWindow Object #%u:\nxPosition: %u\nyPosition: %u\nwidth: %u\nheight: %u\nbackgroundColor: %s\nmenuHandle: %s\nstyle: %u\nextendedStyle: %u\nwindowName: %s\nclassName: %s\nwindowProcedure: %s\nparentWindow: %s\nwindowHandle: %s\nwindowInstance: %s",
            this->_tglObjectID,
            this->_xPosition,
            this->_yPosition,
            this->_width,
            this->_height,
            this->_backgroundColor==0? "White":this->_backgroundColor==1? "Light Gray":this->_backgroundColor==2? "Gray":this->_backgroundColor==3? "Dark Gray":this->_backgroundColor==4? "Black":"Hollow/Null",
            this->_menuHandle? "Yes":"No",
            this->_style,
            this->_extendedStyle,
            this->_windowName,
            this->_className,
            this->_windowProcedure? "Yes":"No",
            this->_parentWindow? "Yes":"No",
            this->_windowHandle? "Yes":"No",
            this->_windowInstance? "Yes":"No");
}

bool TGL::tglWindow::Show()
{
    if (this->_windowHandle)
    {
        return
        ShowWindow(this->_windowHandle,
                   SW_RESTORE);
    }
    return 0;
}

bool TGL::tglWindow::Hide()
{
    if (this->_windowHandle)
    {
        return
        ShowWindow(this->_windowHandle,
                   SW_HIDE);
    }
    return 0;
}

bool TGL::tglWindow::Update(HWND insertAfterWindow, UINT windowFlags)
{
    return
    SetWindowPos(this->_windowHandle,
                 insertAfterWindow,
                 this->_xPosition,
                 this->_yPosition,
                 this->_width,
                 this->_height,
                 windowFlags);
}

HWND TGL::tglWindow::Create()
{
    return
    this->Create(this->_extendedStyle,
                 this->_className,
                 this->_windowName,
                 this->_style,
                 this->_xPosition,
                 this->_yPosition,
                 this->_width,
                 this->_height,
                 this->_parentWindow,
                 this->_menuHandle,
                 this->_windowInstance);
}

HWND TGL::tglWindow::Create(DWORD newExtendedStyle,
                            const char *newClassName,
                            const char *newWindowName,
                            DWORD newStyle,
                            int newXPosition,
                            int newYPosition,
                            size_t newWidth,
                            size_t newHeight,
                            HWND newParentWindow,
                            HMENU newMenuHandle,
                            HINSTANCE newWindowInstance)
{
    this->_windowClass.hbrBackground=(HBRUSH)GetStockObject(this->_backgroundColor);
    this->_windowClass.hCursor=LoadCursor(NULL, IDC_ARROW);
    this->_windowClass.lpfnWndProc=this->_windowProcedure;
    this->_windowClass.lpszClassName=this->_className;

    if (!RegisterClass(&this->_windowClass))
    {
        new TGL::tglError(stdout,
                          "Failed call to RegisterClass(WNDCLASS*). Class could not be registered.",
                          "HWND TGL::tglWindow::Create()",
                          "TGL::tglWindow::_windowClass",
                          &this->_windowClass);

        return NULL;
    }

    this->_windowHandle=
    CreateWindowEx(newExtendedStyle,
                   newClassName,
                   newWindowName,
                   newStyle,
                   newXPosition,
                   newYPosition,
                   newWidth,
                   newHeight,
                   newParentWindow,
                   newMenuHandle,
                   newWindowInstance,
                   NULL);

    if (!this->_windowHandle)
    {
        new TGL::tglError(stdout,
                          "Failed call to CreateWindowEx(...). Window could not be created.",
                          "HWND TGL::tglWindow::Create()",
                          "TGL::tglWindow::_windowHandle",
                          &this->_windowHandle);

        return NULL;
    }

    return this->_windowHandle;
}



HMENU &TGL::tglWindow::menuHandle()
{
    return this->_menuHandle;
}

HMENU TGL::tglWindow::menuHandle() const
{
    return this->_menuHandle;
}

DWORD &TGL::tglWindow::style()
{
    return this->_style;
}

const DWORD &TGL::tglWindow::style() const
{
    return this->_style;
}

DWORD &TGL::tglWindow::extendedStyle()
{
    return this->_extendedStyle;
}

const DWORD &TGL::tglWindow::extendedStyle() const
{
    return this->_extendedStyle;
}

const char *&TGL::tglWindow::windowName()
{
    return this->_windowName;
}

const char *TGL::tglWindow::windowName() const
{
    return this->_windowName;
}

const char *&TGL::tglWindow::className()
{
    return this->_className;
}

const char *TGL::tglWindow::className() const
{
    return this->_className;
}

HWND &TGL::tglWindow::parentWindow()
{
    return this->_parentWindow;
}

HWND TGL::tglWindow::parentWindow() const
{
    return this->_parentWindow;
}

HWND TGL::tglWindow::windowHandle() const
{
    return this->_windowHandle;
}

WNDPROC &TGL::tglWindow::windowProcedure()
{
    return this->_windowProcedure;
}

const WNDPROC TGL::tglWindow::windowProcedure() const
{
    return this->_windowProcedure;
}

HINSTANCE &TGL::tglWindow::windowInstance()
{
    return this->_windowInstance;
}

const HINSTANCE TGL::tglWindow::windowInstance() const
{
    return this->_windowInstance;
}

int &TGL::tglWindow::backgroundColor()
{
    return this->_backgroundColor;
}

const int &TGL::tglWindow::backgroundColor() const
{
    return this->_backgroundColor;
}

int &TGL::tglWindow::xPosition()
{
    return this->_xPosition;
}

const int &TGL::tglWindow::xPosition() const
{
    return this->_xPosition;
}

int &TGL::tglWindow::yPosition()
{
    return this->_yPosition;
}

const int &TGL::tglWindow::yPosition() const
{
    return this->_yPosition;
}

size_t &TGL::tglWindow::width()
{
    return this->_width;
}

const size_t &TGL::tglWindow::width() const
{
    return this->_width;
}

size_t &TGL::tglWindow::height()
{
    return this->_height;
}

const size_t &TGL::tglWindow::height() const
{
    return this->_height;
}

const size_t &TGL::tglWindow::tglObjectID() const
{
    return this->_tglObjectID;
}

//}TGL::tglWindow



#include"tglWindow Functions.h"



#endif // TGL_WINDOW_H






































