#ifndef TGL_STRING_FUNCTIONS_H
    #define TGL_STRING_FUNCTIONS_H



//{TGL::tglString functions

void TGL::Swap(TGL::tglString &targetString1, TGL::tglString &targetString2)
{
    targetString1.Swap(targetString2);
}

TGL::tglString TGL::operator +(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    TGL::tglString
        resultString;

    resultString.Reserve(leftOperand.length()+rightOperand.length());
    resultString.Append(leftOperand).Append(rightOperand);

    return resultString;
}

TGL::tglString TGL::operator +(const TGL::tglString &leftOperand, const char *rightOperand)
{
    TGL::tglString
        resultString;

    resultString.Assign(leftOperand).Append(rightOperand);

    return resultString;
}

TGL::tglString TGL::operator +(const char *leftOperand, const TGL::tglString &rightOperand)
{
    TGL::tglString
        resultString;

    resultString.Assign(leftOperand).Append(rightOperand);

    return resultString;
}

TGL::tglString TGL::operator +(const TGL::tglString &leftOperand, char rightOperand)
{
    TGL::tglString
        resultString;

    resultString.Reserve(leftOperand.length()+1);
    resultString.Append(leftOperand).Append(rightOperand);

    return resultString;
}

TGL::tglString TGL::operator +(char leftOperand, const TGL::tglString &rightOperand)
{
    TGL::tglString
        resultString;

    resultString.Reserve(rightOperand.length()+1);
    resultString.Append(leftOperand).Append(rightOperand);

    return resultString;
}



bool TGL::operator ==(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())? 0:1;
}

bool TGL::operator ==(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)? 0:1;
}

bool TGL::operator ==(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())? 0:1;
}

bool TGL::operator !=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())? 1:0;
}

bool TGL::operator !=(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)? 1:0;
}

bool TGL::operator !=(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())? 1:0;
}

bool TGL::operator  <(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())<0? 1:0;
}

bool TGL::operator  <(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)<0? 1:0;
}

bool TGL::operator  <(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())<0? 1:0;
}

bool TGL::operator <=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())<=0? 1:0;
}

bool TGL::operator <=(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)<=0? 1:0;
}

bool TGL::operator <=(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())<=0? 1:0;
}

bool TGL::operator  >(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())>0? 1:0;
}

bool TGL::operator  >(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)>0? 1:0;
}

bool TGL::operator  >(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())>0? 1:0;
}

bool TGL::operator >=(const TGL::tglString &leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand.characterArray())>=0? 1:0;
}

bool TGL::operator >=(const TGL::tglString &leftOperand, const char *rightOperand)
{
    return strcmp(leftOperand.characterArray(), rightOperand)>=0? 1:0;
}

bool TGL::operator >=(const char *leftOperand, const TGL::tglString &rightOperand)
{
    return strcmp(leftOperand, rightOperand.characterArray())>=0? 1:0;
}

//}TGL::tglString functions



#endif // TGL_STRING_FUNCTIONS_H






































