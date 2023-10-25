#ifndef TGL_FUNCTIONS_H
    #define TGL_FUNCTIONS_H



//{TGL functions

void TGL::ClearTGL()
{
    size_t
        index;

    for (index=0; index<TGL::errorCount; index++)
    {
        if (TGL::errorActive[index])
        {
            delete TGL::errorArray[index];
        }
    }
    delete []TGL::errorArray;
    delete []TGL::errorActive;



    for (index=0; index<TGL::stringCount; index++)
    {
        if (TGL::stringActive[index])
        {
            delete TGL::stringArray[index];
        }
    }
    delete []TGL::stringArray;
    delete []TGL::stringActive;



    for (index=0; index<TGL::textureCount; index++)
    {
        if (TGL::textureActive[index])
        {
            delete TGL::textureArray[index];
        }
    }
    delete []TGL::textureArray;
    delete []TGL::textureActive;



    for (index=0; index<TGL::displayCount; index++)
    {
        if (TGL::displayActive[index])
        {
            delete TGL::displayArray[index];
        }
    }
    delete []TGL::displayArray;
    delete []TGL::displayActive;



    for (index=0; index<TGL::windowCount; index++)
    {
        if (TGL::windowActive[index])
        {
            delete TGL::windowArray[index];
        }
    }
    delete []TGL::windowArray;
    delete []TGL::windowActive;



    for (index=0; index<TGL::vectorCount; index++)
    {
        if (TGL::vectorActive[index])
        {
            delete TGL::vectorArray[index];
        }
    }
    delete []TGL::vectorArray;
    delete []TGL::vectorActive;



    for (index=0; index<TGL::anglerCount; index++)
    {
        if (TGL::anglerActive[index])
        {
            delete TGL::anglerArray[index];
        }
    }
    delete []TGL::anglerArray;
    delete []TGL::anglerActive;



    for (index=0; index<TGL::audioCount; index++)
    {
        if (TGL::audioActive[index])
        {
            delete TGL::audioArray[index];
        }
    }
    delete []TGL::audioArray;
    delete []TGL::audioActive;



    operator delete [](TGL::NO_REPLACE);
}

template<class parameterDataType> parameterDataType TGL::Min(parameterDataType firstOperand, parameterDataType secondOperand)
{
    return firstOperand<secondOperand? firstOperand:secondOperand;
}

template<class parameterDataType> parameterDataType TGL::Max(parameterDataType firstOperand, parameterDataType secondOperand)
{
    return firstOperand>secondOperand? firstOperand:secondOperand;
}

template<class parameterDataType> parameterDataType TGL::Module(parameterDataType value)
{
    return value<0? -value:value;
}

COLORREF TGL::PixelRGB(unsigned char red, unsigned char green, unsigned char blue)
{
    static COLORREF
        resultPixel;

    return resultPixel=blue|(green<<8)|(red<<16);
}

COLORREF TGL::PixelRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    static COLORREF
        resultPixel;

    return resultPixel=blue|(green<<8)|(red<<16)|(alpha<<24);
}

template<class parameterDataType> void SwitchEndian(parameterDataType &value)
{
    size_t
        byteCount=sizeof(value),
        lastBit=byteCount*8-1,
        currentBit;

    parameterDataType
        switchedValue=0;

    for (currentBit=0; currentBit<=lastBit; currentBit++)
    {
        if (value&(1<<currentBit))
        {
            switchedValue|=(1<<lastBit-currentBit);
        }
    }

    value=switchedValue;
}

//}TGL functions



#endif // TGL_FUNCTIONS_H






































