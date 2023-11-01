#ifndef TGL_ERROR_H
    #define TGL_ERROR_H



//{class TGL::tglError

class TGL::tglError
{
public:
    tglError();
    tglError(FILE *outputStream, const char *newErrorMessage, const char *newFunctionName, const char *newVariableName, const void *newVariableAddress);
    ~tglError();

    TGL::tglError
        &operator ()(const void *newErrorMessage=TGL::NO_REPLACE, const void *newFunctionName=TGL::NO_REPLACE, const void *newVariableName=TGL::NO_REPLACE, const void *newVariableAddress=TGL::NO_REPLACE);

    void
        DisplayError(FILE *outputStream=stdout, const void *newErrorMessage=TGL::NO_REPLACE, const void *newFunctionName=TGL::NO_REPLACE, const void *newVariableName=TGL::NO_REPLACE, const void *newVariableAddress=TGL::NO_REPLACE),
        DisplayValues(FILE *outputStream=stdout),
        ExportToFile(const char *directory);

    const char
        *&functionName(),
         *functionName() const,
        *&variableName(),
         *variableName() const,
        *&errorMessage(),
         *errorMessage() const;

    const void
        *&variableAddress(),
         *variableAddress() const;

    const size_t
        tglObjectID() const;

private:
    void
        Initialize(),
        Monitor();

    const char
        *_functionName,
        *_variableName,
        *_errorMessage;

    const void
        *_variableAddress;

    size_t
        _tglObjectID;
};

//}class TGL::tglError



//{TGL::tglError

TGL::tglError::tglError()
{
    this->Initialize();
    this->Monitor();
}

TGL::tglError::tglError(FILE *outputStream, const char *newErrorMessage, const char *newFunctionName=NULL, const char *newVariableName=NULL, const void *newVariableAddress=NULL)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    this->Monitor();
    this->DisplayError(outputStream,
                       this->_errorMessage=newErrorMessage,
                       this->_functionName=newFunctionName,
                       this->_variableName=newVariableName,
                       this->_variableAddress=newVariableAddress);
}

TGL::tglError::~tglError()
{
    TGL::errorActive[this->_tglObjectID]=0;
}

void TGL::tglError::Initialize()
{
    this->_functionName=NULL;
    this->_variableName=NULL;
    this->_errorMessage=TGL::defaultErrorMessage;
    this->_variableAddress=NULL;
}

void TGL::tglError::Monitor()
{
    TGL::errorActive[this->_tglObjectID=TGL::errorCount]=1;
    TGL::errorArray[TGL::errorCount++]=this;
    if (TGL::errorCount==TGL::errorCapacity)
    {
        {
            TGL::tglError
                **arrayHandle=TGL::errorArray;

            TGL::errorArray=new TGL::tglError*[TGL::errorCapacity+=TGL::STANDARD_ALLOCATION];
            memcpy(TGL::errorArray, arrayHandle, sizeof(*arrayHandle)*TGL::errorCount);
            delete []arrayHandle;
        }
        {
            bool
                *arrayHandle=TGL::errorActive;

            TGL::errorActive=new bool[TGL::errorCount];
            memcpy(TGL::errorActive, arrayHandle, sizeof(*arrayHandle)*TGL::errorCount);
            delete []arrayHandle;
        }
    }
}



TGL::tglError &TGL::tglError::operator ()(const void *newErrorMessage, const void *newFunctionName, const void *newVariableName, const void *newVariableAddress)
{
    newErrorMessage   !=TGL::NO_REPLACE? this->_errorMessage   =(const char*)newErrorMessage   :NULL;
    newFunctionName   !=TGL::NO_REPLACE? this->_functionName   =(const char*)newFunctionName   :NULL;
    newVariableName   !=TGL::NO_REPLACE? this->_variableName   =(const char*)newVariableName   :NULL;
    newVariableAddress!=TGL::NO_REPLACE? this->_variableAddress=             newVariableAddress:NULL;

    return *this;
}



void TGL::tglError::DisplayError(FILE *outputStream, const void *newErrorMessage, const void *newFunctionName, const void *newVariableName, const void *newVariableAddress)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    if (newErrorMessage!=TGL::NO_REPLACE)
    {
        this->_errorMessage=(const char*)newErrorMessage;
    }
    if (newFunctionName!=TGL::NO_REPLACE)
    {
        this->_functionName=(const char*)newFunctionName;
    }
    if (newVariableName!=TGL::NO_REPLACE)
    {
        this->_variableName=(const char*)newVariableName;
    }
    if (newVariableAddress!=TGL::NO_REPLACE)
    {
        this->_variableAddress=newVariableAddress;
    }

    size_t
        parameterCombination=0;

    this->_functionName?    parameterCombination|=(1<<2):0;
    this->_variableName?    parameterCombination|=(1<<1):0;
    this->_variableAddress? parameterCombination|=(1<<0):0;
    !this->_errorMessage?   this->_errorMessage=TGL::defaultErrorMessage:NULL;

    printf("\n");
    TGL::DisplayErrorCombination[parameterCombination](this->_tglObjectID, outputStream);
    printf("\n");
}

void TGL::tglError::DisplayValues(FILE *outputStream)
{
    if (!outputStream)
    {
        outputStream=stdout;
    }

    fprintf(outputStream,
            "\n\n\n   TGL::tglError Object #%u:",
            this->_tglObjectID);

    this->DisplayError(outputStream);
}

void TGL::tglError::ExportToFile(const char *directory)
{
    if (!directory)
    {
        printf("\n\n\nError in function TGL::tglError::ExportToFile(const char *directory):\nParameter \"directory\" is NULL.\nThe function ends without taking further action.");
        return;
    }

    FILE
        *exportFileHandle=fopen(directory, "w+");

    if (!exportFileHandle)
    {
        printf("\n\n\nError in function TGL::tglError::ExportToFile(const char *directory):\nFile %s could not be opened.\nCheck the spelling and/or directory of the file.\nThe function ends without taking further action.");
        return;
    }

    this->DisplayError(exportFileHandle);

    fclose(exportFileHandle);
}



const char *&TGL::tglError::functionName()
{
    return this->_functionName;
}

const char *TGL::tglError::functionName() const
{
    return this->_functionName;
}

const char *&TGL::tglError::variableName()
{
    return this->_variableName;
}

const char *TGL::tglError::variableName() const
{
    return this->_variableName;
}

const char *&TGL::tglError::errorMessage()
{
    return this->_errorMessage;
}

const char *TGL::tglError::errorMessage() const
{
    return this->_errorMessage;
}

const void *&TGL::tglError::variableAddress()
{
    return this->_variableAddress;
}

const void *TGL::tglError::variableAddress() const
{
    return this->_variableAddress;
}

const size_t TGL::tglError::tglObjectID() const
{
    return this->_tglObjectID;
}

//}TGL::tglError



#include"tglError Functions.h"



#endif // TGL_ERROR_H






































