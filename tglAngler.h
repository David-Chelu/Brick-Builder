#ifndef TGL_ANGLER_H
    #define TGL_ANGLER_H



//{class TGL::tglAngler

class TGL::tglAngler
{
public:
    tglAngler();
    tglAngler(const TGL::tglAngler &targetAngler);
    ~tglAngler();



    TGL::tglAngler
        &operator =(const TGL::tglAngler &targetAngler),
        &operator =(int newSelectedAngle),
        &operator ()(int newSelectedAngle),
        &operator +=(const TGL::tglAngler &targetAngler),
        &operator -=(const TGL::tglAngler &targetAngler),
        &operator ++(int),
        &operator --(int),
        &operator ++(),
        &operator --();



    void
        AllocateValues(size_t newDegreeCount=256),
        DeallocateValues(),
        Clear(),
        DisplayValues(FILE *outputStream=stdout);

    int
        NormalizeAngle(int rawValue);

    double
        Sin(),
        Sin(int newSelectedAngle),
        Cos(),
        Cos(int newSelectedAngle),
        Tan(),
        Tan(int newSelectedAngle),
        Cot(),
        Cot(int newSelectedAngle),
        Sec(),
        Sec(int newSelectedAngle),
        Csc(),
        Csc(int newSelectedAngle);

    const size_t
        &degreeCount() const,
        &tglObjectID() const;

    int
        &selectedAngle();

    const int
        &selectedAngle() const;

    const double
        *sinValue() const,
        *cosValue() const;

private:
    void
        Initialize(),
        Monitor();

    int
        _selectedAngle;

    double
        *_sinValue,
        *_cosValue;

    size_t
        _degreeCount,
        _tglObjectID;
};

//}class TGL::tglAngler



//{TGL::tglAngler

TGL::tglAngler::tglAngler()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglAngler::tglAngler(const TGL::tglAngler &targetAngler)
{
    this->Initialize();
    (*this=targetAngler).Monitor();
}

TGL::tglAngler::~tglAngler()
{
    this->Clear();

    TGL::anglerActive[this->_tglObjectID]=0;
}

void TGL::tglAngler::Initialize()
{
    this->_selectedAngle=0;

    this->_sinValue=
    this->_cosValue=NULL;

    this->_degreeCount=0;
}

void TGL::tglAngler::Monitor()
{
    TGL::anglerActive[this->_tglObjectID=TGL::anglerCount]=1;
    TGL::anglerArray[TGL::anglerCount++]=this;
    if (TGL::anglerCount==TGL::anglerCapacity)
    {
        {
            TGL::tglAngler
                **arrayHandle=TGL::anglerArray;

            TGL::anglerArray=new TGL::tglAngler*[TGL::anglerCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::anglerArray, arrayHandle, sizeof(*arrayHandle)*TGL::anglerCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::anglerActive;

            TGL::anglerActive=new bool[TGL::anglerCount];
            memcpy(TGL::anglerActive, arrayHandle, sizeof(*arrayHandle)*TGL::anglerCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglAngler &TGL::tglAngler::operator =(const TGL::tglAngler &targetAngler)
{
    this->_selectedAngle=targetAngler._selectedAngle;

    if (this->_degreeCount!=targetAngler._degreeCount)
    {
        this->_degreeCount=targetAngler._degreeCount;

        this->AllocateValues();
    }

    memcpy(this->_sinValue,
           targetAngler._sinValue,
           sizeof(*this->_sinValue)*this->_degreeCount);

    memcpy(this->_cosValue,
           targetAngler._cosValue,
           sizeof(*this->_cosValue)*this->_degreeCount);

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator =(int newSelectedAngle)
{
    this->_selectedAngle=newSelectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator ()(int newSelectedAngle)
{
    this->_selectedAngle=newSelectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator +=(const TGL::tglAngler &targetAngler)
{
    this->_selectedAngle+=targetAngler._selectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator -=(const TGL::tglAngler &targetAngler)
{
    this->_selectedAngle-=targetAngler._selectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator ++(int)
{
    ++this->_selectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator --(int)
{
    --this->_selectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator ++()
{
    ++this->_selectedAngle;

    return *this;
}

TGL::tglAngler &TGL::tglAngler::operator --()
{
    --this->_selectedAngle;

    return *this;
}



void TGL::tglAngler::AllocateValues(size_t newDegreeCount)
{
    this->DeallocateValues();

    if (!newDegreeCount)
    {
        this->_sinValue=new double[this->_degreeCount];
        this->_cosValue=new double[this->_degreeCount];
    }
    else
    {
        this->_sinValue=new double[this->_degreeCount=newDegreeCount];
        this->_cosValue=new double[this->_degreeCount];
    }

    for (size_t index=0; index<this->_degreeCount; index++)
    {
        this->_sinValue[index]=sin(2*TGL::pi*double(index)/double(this->_degreeCount));
        this->_cosValue[index]=cos(2*TGL::pi*double(index)/double(this->_degreeCount));
    }
}

void TGL::tglAngler::DeallocateValues()
{
    if (this->_degreeCount)
    {
        delete []this->_sinValue;
        delete []this->_cosValue;
    }
}

void TGL::tglAngler::Clear()
{
    this->DeallocateValues();
}

void TGL::tglAngler::DisplayValues(FILE *outputStream)
{

    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglAngler Object #%u:\ndegreeCount: %u\nselectedAngle: %d\nsinValue: %s\ncosValue: %s",
            this->_tglObjectID,
            this->_degreeCount,
            this->_selectedAngle,
            this->_sinValue? "Yes":"No",
            this->_cosValue? "Yes":"No");
}

int TGL::tglAngler::NormalizeAngle(int rawValue)
{
    if ((rawValue%=this->_degreeCount)<0)
    {
        rawValue+=this->_degreeCount;
    }

    return rawValue;
}

double TGL::tglAngler::Sin()
{
    return this->Sin(this->_selectedAngle);
}

double TGL::tglAngler::Sin(int newSelectedAngle)
{
    return this->_sinValue[this->NormalizeAngle(newSelectedAngle)];
}

double TGL::tglAngler::Cos()
{
    return this->Cos(this->_selectedAngle);
}

double TGL::tglAngler::Cos(int newSelectedAngle)
{
    return this->_cosValue[this->NormalizeAngle(newSelectedAngle)];
}

double TGL::tglAngler::Tan()
{
    return this->Tan(this->_selectedAngle);
}

double TGL::tglAngler::Tan(int newSelectedAngle)
{
    return this->Sin(newSelectedAngle)/this->Cos(newSelectedAngle);
}

double TGL::tglAngler::Cot()
{
    return this->Cot(this->_selectedAngle);
}

double TGL::tglAngler::Cot(int newSelectedAngle)
{
    return
        this->Cos(newSelectedAngle)/
        this->Sin(newSelectedAngle);
}

double TGL::tglAngler::Sec()
{
    return this->Sec(this->_selectedAngle);
}

double TGL::tglAngler::Sec(int newSelectedAngle)
{
    return 1./this->Cos(newSelectedAngle);
}

double TGL::tglAngler::Csc()
{
    return this->Csc(this->_selectedAngle);
}

double TGL::tglAngler::Csc(int newSelectedAngle)
{
    return 1./this->Sin(newSelectedAngle);
}



const size_t &TGL::tglAngler::degreeCount() const
{
    return this->_degreeCount;
}

const size_t &TGL::tglAngler::tglObjectID() const
{
    return this->_tglObjectID;
}

int &TGL::tglAngler::selectedAngle()
{
    return this->_selectedAngle;
}

const int &TGL::tglAngler::selectedAngle() const
{
    return this->_selectedAngle;
}

const double *TGL::tglAngler::sinValue() const
{
    return this->_sinValue;
}

const double *TGL::tglAngler::cosValue() const
{
    return this->_cosValue;
}

//}TGL::tglAngler



#include"tglAngler Functions.h"



#endif // TGL_ANGLER_H





































