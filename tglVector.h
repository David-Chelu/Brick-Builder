#ifndef TGL_VECTOR_H
    #define TGL_vector_H



//{class TGL::tglVector

class TGL::tglVector
{
public:
    tglVector(int newXValue=0, int newYValue=0, int newZValue=0, int newWValue=0, int newTValue=0);
    tglVector(const TGL::tglVector &targetVector);
    tglVector(TGL::tglVector *newChangeRate);
    ~tglVector();

    TGL::tglVector
        &operator =(const TGL::tglVector &targetVector),
        &operator =(TGL::tglVector *newChangeRate),
        &operator +=(const TGL::tglVector &targetVector),
        &operator +=(int value),
        &operator -=(const TGL::tglVector &targetVector),
        &operator -=(int value),
        &operator *=(int value),
        &operator /=(int value);

    void
        Swap(TGL::tglVector &targetVector),
        DisplayValues(FILE *outputStream=stdout);

    bool
        Update();

    int
        &xValue(),   &yValue(),   &zValue(),   &wValue(),   &tValue(),
        &xMinimum(), &yMinimum(), &zMinimum(), &wMinimum(), &tMinimum(),
        &xMaximum(), &yMaximum(), &zMaximum(), &wMaximum(), &tMaximum();

    const int
        &xValue()   const, &yValue()   const, &zValue()   const, &wValue()   const, &tValue()   const,
        &xMinimum() const, &yMinimum() const, &zMinimum() const, &wMinimum() const, &tMinimum() const,
        &xMaximum() const, &yMaximum() const, &zMaximum() const, &wMaximum() const, &tMaximum() const;

    bool
        &infinite();

    const bool
        &infinite() const;

    TGL::tglVector
        *&changeRate();

    size_t
        tglObjectID() const;

private:
    void
        Initialize(),
        Monitor();

    int
        _xValue,   _yValue,   _zValue,   _wValue,   _tValue,
        _xMinimum, _yMinimum, _zMinimum, _wMinimum, _tMinimum,
        _xMaximum, _yMaximum, _zMaximum, _wMaximum, _tMaximum;

    bool
        _infinite;

    TGL::tglVector
        *_changeRate;

    size_t
        _tglObjectID;
};

namespace TGL
{
    TGL::tglVector
        defaultCamera;
}

//}class TGL::tglVector



//{TGL::tglVector

TGL::tglVector::tglVector(int newXValue, int newYValue, int newZValue, int newWValue, int newTValue)
{
    this->Initialize();

    this->_xValue=newXValue;
    this->_yValue=newYValue;
    this->_zValue=newZValue;
    this->_wValue=newWValue;
    this->_tValue=newTValue;

    this->Monitor();
}

TGL::tglVector::tglVector(const TGL::tglVector &targetVector)
{
    this->Initialize();
    (*this=targetVector).Monitor();
}

TGL::tglVector::tglVector(TGL::tglVector *newChangeRate)
{
    this->Initialize();
    this->_changeRate=newChangeRate;
    this->Monitor();
}

TGL::tglVector::~tglVector()
{
    TGL::vectorActive[this->_tglObjectID]=0;
}

void TGL::tglVector::Initialize()
{
    this->_xValue=   this->_yValue=   this->_zValue=   this->_wValue=   this->_tValue=0;
    this->_xMinimum= this->_yMinimum= this->_zMinimum= this->_wMinimum= this->_tMinimum=-10;
    this->_xMaximum= this->_yMaximum= this->_zMaximum= this->_wMaximum= this->_tMaximum=10;

    this->_infinite=false;

    this->_changeRate=NULL;
}

void TGL::tglVector::Monitor()
{
    TGL::vectorActive[this->_tglObjectID=TGL::vectorCount]=1;
    TGL::vectorArray[TGL::vectorCount++]=this;
    if (TGL::vectorCount==TGL::vectorCapacity)
    {
        {
            TGL::tglVector
                **arrayHandle=TGL::vectorArray;

            TGL::vectorArray=new TGL::tglVector*[TGL::vectorCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::vectorArray, arrayHandle, sizeof(*arrayHandle)*TGL::vectorCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::vectorActive;

            TGL::vectorActive=new bool[TGL::vectorCount];
            memcpy(TGL::vectorActive, arrayHandle, sizeof(*arrayHandle)*TGL::vectorCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglVector &TGL::tglVector::operator =(const TGL::tglVector &targetVector)
{
    this->_xValue=targetVector._xValue;
    this->_yValue=targetVector._yValue;
    this->_zValue=targetVector._zValue;
    this->_wValue=targetVector._wValue;
    this->_tValue=targetVector._tValue;

    this->_xMinimum=targetVector._xMinimum;
    this->_yMinimum=targetVector._yMinimum;
    this->_zMinimum=targetVector._zMinimum;
    this->_wMinimum=targetVector._wMinimum;
    this->_tMinimum=targetVector._tMinimum;

    this->_xMaximum=targetVector._xMaximum;
    this->_yMaximum=targetVector._yMaximum;
    this->_zMaximum=targetVector._zMaximum;
    this->_wMaximum=targetVector._wMaximum;
    this->_tMaximum=targetVector._tMaximum;

    this->_infinite=targetVector._infinite;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator =(TGL::tglVector *newChangeRate)
{
    this->_changeRate=newChangeRate;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator +=(const TGL::tglVector &targetVector)
{
    this->_xValue+=targetVector._xValue;
    this->_yValue+=targetVector._yValue;
    this->_zValue+=targetVector._zValue;
    this->_wValue+=targetVector._wValue;
    this->_tValue+=targetVector._tValue;

    this->_infinite|=targetVector._infinite;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator +=(int value)
{
    this->_xValue+=value;
    this->_yValue+=value;
    this->_zValue+=value;
    this->_wValue+=value;
    this->_tValue+=value;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator -=(const TGL::tglVector &targetVector)
{
    this->_xValue-=targetVector._xValue;
    this->_yValue-=targetVector._yValue;
    this->_zValue-=targetVector._zValue;
    this->_wValue-=targetVector._wValue;
    this->_tValue-=targetVector._tValue;

    this->_infinite-=targetVector._infinite;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator -=(int value)
{
    this->_xValue-=value;
    this->_yValue-=value;
    this->_zValue-=value;
    this->_wValue-=value;
    this->_tValue-=value;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator *=(int value)
{
    this->_xValue*=value;
    this->_yValue*=value;
    this->_zValue*=value;
    this->_wValue*=value;
    this->_tValue*=value;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator /=(int value)
{
    if (value==0)
    {
        new TGL::tglError(stdout,
                          "Attempted to divide by 0.",
                          "TGL::tglVector::operator /=(int value)",
                          "value",
                          this);

        if (HandleError)
        {
            HandleError(TGL::divideBy0);
        }
    }

    this->_xValue/=value;
    this->_yValue/=value;
    this->_zValue/=value;
    this->_wValue/=value;
    this->_tValue/=value;

    return *this;
}



void TGL::tglVector::Swap(TGL::tglVector &targetVector)
{
    {
        int
            handle;

        handle=this->_xValue;   this->_xValue  =targetVector._xValue;   targetVector._xValue  =handle;
        handle=this->_yValue;   this->_yValue  =targetVector._yValue;   targetVector._yValue  =handle;
        handle=this->_zValue;   this->_zValue  =targetVector._zValue;   targetVector._zValue  =handle;
        handle=this->_wValue;   this->_wValue  =targetVector._wValue;   targetVector._wValue  =handle;
        handle=this->_tValue;   this->_tValue  =targetVector._tValue;   targetVector._tValue  =handle;

        handle=this->_xMinimum; this->_xMinimum=targetVector._xMinimum; targetVector._xMinimum=handle;
        handle=this->_yMinimum; this->_yMinimum=targetVector._yMinimum; targetVector._yMinimum=handle;
        handle=this->_zMinimum; this->_zMinimum=targetVector._zMinimum; targetVector._zMinimum=handle;
        handle=this->_wMinimum; this->_wMinimum=targetVector._wMinimum; targetVector._wMinimum=handle;
        handle=this->_tMinimum; this->_tMinimum=targetVector._tMinimum; targetVector._tMinimum=handle;

        handle=this->_xMaximum; this->_xMaximum=targetVector._xMaximum; targetVector._xMaximum=handle;
        handle=this->_yMaximum; this->_yMaximum=targetVector._yMaximum; targetVector._yMaximum=handle;
        handle=this->_zMaximum; this->_zMaximum=targetVector._zMaximum; targetVector._zMaximum=handle;
        handle=this->_wMaximum; this->_wMaximum=targetVector._wMaximum; targetVector._wMaximum=handle;
        handle=this->_tMaximum; this->_tMaximum=targetVector._tMaximum; targetVector._tMaximum=handle;
    }

    {
        bool
            handle;

        handle=this->_infinite;
        this->_infinite=targetVector._infinite;
        targetVector._infinite=handle;
    }

    {
        void
            *handle;

        handle=this->_changeRate;
        this->_changeRate=targetVector._changeRate;
        targetVector._changeRate=(TGL::tglVector*)handle;
    }
}

void TGL::tglVector::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglVector Object #%u:\nxValue: %d\nyValue: %d\nzValue: %d\nwValue: %d\ntValue: %d\nxMinimum: %d\nyMinimum: %d\nzMinimum: %d\nwMinimum: %d\ntMinimum: %d\nxMaximum: %d\nyMaximum: %d\nzMaximum: %d\nwMaximum: %d\ntMaximum: %d\nInfinite: %s\n",
            this->_tglObjectID,

            this->_xValue,
            this->_yValue,
            this->_zValue,
            this->_wValue,
            this->_tValue,

            this->_xMinimum,
            this->_yMinimum,
            this->_zMinimum,
            this->_wMinimum,
            this->_tMinimum,

            this->_xMaximum,
            this->_yMaximum,
            this->_zMaximum,
            this->_wMaximum,
            this->_tMaximum,

            this->_infinite? "Yes":"No");

}

bool TGL::tglVector::Update()
{
    if (this->_changeRate)
    {
        this->_xValue=TGL::Max<int>(TGL::Min<int>(this->_xValue+this->_changeRate->_xValue, this->_xMaximum), this->_xMinimum);
        this->_yValue=TGL::Max<int>(TGL::Min<int>(this->_yValue+this->_changeRate->_yValue, this->_yMaximum), this->_yMinimum);
        this->_zValue=TGL::Max<int>(TGL::Min<int>(this->_zValue+this->_changeRate->_zValue, this->_zMaximum), this->_zMinimum);
        this->_wValue=TGL::Max<int>(TGL::Min<int>(this->_wValue+this->_changeRate->_wValue, this->_wMaximum), this->_wMinimum);
        this->_tValue=TGL::Max<int>(TGL::Min<int>(this->_tValue+this->_changeRate->_tValue, this->_tMaximum), this->_tMinimum);

        this->_infinite|=this->_changeRate->_infinite;

        this->_changeRate->Update();

        return 1;
    }

    return 0;
}



int &TGL::tglVector::xValue()
{
	return this->_xValue;
}

const int &TGL::tglVector::xValue() const
{
	return this->_xValue;
}

int &TGL::tglVector::yValue()
{
	return this->_yValue;
}

const int &TGL::tglVector::yValue() const
{
	return this->_yValue;
}

int &TGL::tglVector::zValue()
{
	return this->_zValue;
}

const int &TGL::tglVector::zValue() const
{
	return this->_zValue;
}

int &TGL::tglVector::wValue()
{
	return this->_wValue;
}

const int &TGL::tglVector::wValue() const
{
	return this->_wValue;
}

int &TGL::tglVector::tValue()
{
	return this->_tValue;
}

const int &TGL::tglVector::tValue() const
{
	return this->_tValue;
}

int &TGL::tglVector::xMinimum()
{
	return this->_xMinimum;
}

const int &TGL::tglVector::xMinimum() const
{
	return this->_xMinimum;
}

int &TGL::tglVector::yMinimum()
{
	return this->_yMinimum;
}

const int &TGL::tglVector::yMinimum() const
{
	return this->_yMinimum;
}

int &TGL::tglVector::zMinimum()
{
	return this->_zMinimum;
}

const int &TGL::tglVector::zMinimum() const
{
	return this->_zMinimum;
}

int &TGL::tglVector::wMinimum()
{
	return this->_wMinimum;
}

const int &TGL::tglVector::wMinimum() const
{
	return this->_wMinimum;
}

int &TGL::tglVector::tMinimum()
{
	return this->_tMinimum;
}

const int &TGL::tglVector::tMinimum() const
{
	return this->_tMinimum;
}

int &TGL::tglVector::xMaximum()
{
	return this->_xMaximum;
}

const int &TGL::tglVector::xMaximum() const
{
	return this->_xMaximum;
}

int &TGL::tglVector::yMaximum()
{
	return this->_yMaximum;
}

const int &TGL::tglVector::yMaximum() const
{
	return this->_yMaximum;
}

int &TGL::tglVector::zMaximum()
{
	return this->_zMaximum;
}

const int &TGL::tglVector::zMaximum() const
{
	return this->_zMaximum;
}

int &TGL::tglVector::wMaximum()
{
	return this->_wMaximum;
}

const int &TGL::tglVector::wMaximum() const
{
	return this->_wMaximum;
}

int &TGL::tglVector::tMaximum()
{
	return this->_tMaximum;
}

const int &TGL::tglVector::tMaximum() const
{
	return this->_tMaximum;
}

bool &TGL::tglVector::infinite()
{
	return this->_infinite;
}

const bool &TGL::tglVector::infinite() const
{
	return this->_infinite;
}

TGL::tglVector *&TGL::tglVector::changeRate()
{
	return this->_changeRate;
}

size_t TGL::tglVector::tglObjectID() const
{
	return this->_tglObjectID;
}

//}TGL::tglVector



#include"tglVector Functions.h"



#endif // TGL_VECTOR_H






































