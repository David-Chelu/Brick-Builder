#ifndef TGL_VECTOR_FUNCTIONS_H
    #define TGL_VECTOR_FUNCTIONS_H



//{TGL::tglVector functions

bool TGL::operator ==(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand)
{
    if (leftOperand.xValue()==rightOperand.xValue() &&
        leftOperand.yValue()==rightOperand.yValue() &&
        leftOperand.zValue()==rightOperand.zValue() &&
        leftOperand.wValue()==rightOperand.wValue() &&
        leftOperand.tValue()==rightOperand.tValue() &&
        leftOperand.infinite()==rightOperand.infinite())
    {
        return 1;
    }
    return 0;
}

bool TGL::operator !=(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand)
{
    if (leftOperand.xValue()!=rightOperand.xValue() ||
        leftOperand.yValue()!=rightOperand.yValue() ||
        leftOperand.zValue()!=rightOperand.zValue() ||
        leftOperand.wValue()!=rightOperand.wValue() ||
        leftOperand.tValue()!=rightOperand.tValue() ||
        leftOperand.infinite()!=rightOperand.infinite())
    {
        return 1;
    }
    return 0;
}

TGL::tglVector TGL::operator +(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand.xValue()+rightOperand.xValue(),
                     leftOperand.yValue()+rightOperand.yValue(),
                     leftOperand.zValue()+rightOperand.zValue(),
                     leftOperand.wValue()+rightOperand.wValue(),
                     leftOperand.tValue()+rightOperand.tValue());

    resultVector.infinite()=leftOperand.infinite()|rightOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator +(const TGL::tglVector &leftOperand, int rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand.xValue()+rightOperand,
                     leftOperand.yValue()+rightOperand,
                     leftOperand.zValue()+rightOperand,
                     leftOperand.wValue()+rightOperand,
                     leftOperand.tValue()+rightOperand);

    resultVector.infinite()=leftOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator +(int leftOperand, const TGL::tglVector &rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand+rightOperand.xValue(),
                     leftOperand+rightOperand.yValue(),
                     leftOperand+rightOperand.zValue(),
                     leftOperand+rightOperand.wValue(),
                     leftOperand+rightOperand.tValue());

    resultVector.infinite()=rightOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator -(const TGL::tglVector &leftOperand, const TGL::tglVector &rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand.xValue()-rightOperand.xValue(),
                     leftOperand.yValue()-rightOperand.yValue(),
                     leftOperand.zValue()-rightOperand.zValue(),
                     leftOperand.wValue()-rightOperand.wValue(),
                     leftOperand.tValue()-rightOperand.tValue());

    resultVector.infinite()=leftOperand.infinite()-rightOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator -(const TGL::tglVector &leftOperand, int rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand.xValue()-rightOperand,
                     leftOperand.yValue()-rightOperand,
                     leftOperand.zValue()-rightOperand,
                     leftOperand.wValue()-rightOperand,
                     leftOperand.tValue()-rightOperand);

    resultVector.infinite()=leftOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator -(int leftOperand, const TGL::tglVector &rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand-rightOperand.xValue(),
                     leftOperand-rightOperand.yValue(),
                     leftOperand-rightOperand.zValue(),
                     leftOperand-rightOperand.wValue(),
                     leftOperand-rightOperand.tValue());

    resultVector.infinite()=rightOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator *(const TGL::tglVector &leftOperand, int rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand.xValue()*rightOperand,
                     leftOperand.yValue()*rightOperand,
                     leftOperand.zValue()*rightOperand,
                     leftOperand.wValue()*rightOperand,
                     leftOperand.tValue()*rightOperand);

    resultVector.infinite()=leftOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator *(int leftOperand, const TGL::tglVector &rightOperand)
{
    TGL::tglVector
        resultVector(leftOperand*rightOperand.xValue(),
                     leftOperand*rightOperand.yValue(),
                     leftOperand*rightOperand.zValue(),
                     leftOperand*rightOperand.wValue(),
                     leftOperand*rightOperand.tValue());

    resultVector.infinite()=rightOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator /(const TGL::tglVector &leftOperand, int rightOperand)
{
    if (rightOperand==0)
    {
        new TGL::tglError(stdout,
                          "Attempted to divide by 0.",
                          "TGL::tglVector operator /(const TGL::tglVector &leftOperand, int rightOperand)",
                          "rightOperand",
                          NULL);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::divideBy0);
        }
    }

    TGL::tglVector
        resultVector(leftOperand.xValue()/rightOperand,
                     leftOperand.yValue()/rightOperand,
                     leftOperand.zValue()/rightOperand,
                     leftOperand.wValue()/rightOperand,
                     leftOperand.tValue()/rightOperand);

    resultVector.infinite()=leftOperand.infinite();

    return resultVector;
}

TGL::tglVector TGL::operator /(int leftOperand, const TGL::tglVector &rightOperand)
{
    if (rightOperand.xValue()==0 ||
        rightOperand.yValue()==0 ||
        rightOperand.zValue()==0 ||
        rightOperand.wValue()==0 ||
        rightOperand.tValue()==0)
    {
        new TGL::tglError(stdout,
                          "Attempted to divide by 0.",
                          "TGL::tglVector operator /(const TGL::tglVector &leftOperand, int rightOperand)",
                          "rightOperand",
                          NULL);

        if (TGL::HandleError)
        {
            TGL::HandleError(TGL::divideBy0);
        }
    }

    if (rightOperand.infinite())
    {
        TGL::tglVector
            resultVector(0,
                         0,
                         0,
                         0,
                         0);

        resultVector.infinite()=rightOperand.infinite();

        return resultVector;
    }
    else
    {
        TGL::tglVector
            resultVector(leftOperand/rightOperand.xValue(),
                         leftOperand/rightOperand.yValue(),
                         leftOperand/rightOperand.zValue(),
                         leftOperand/rightOperand.wValue(),
                         leftOperand/rightOperand.tValue());

        resultVector.infinite()=rightOperand.infinite();

        return resultVector;
    }
}

//}TGL::tglVector functions



#endif // TGL_VECTOR_FUNCTIONS_H






































